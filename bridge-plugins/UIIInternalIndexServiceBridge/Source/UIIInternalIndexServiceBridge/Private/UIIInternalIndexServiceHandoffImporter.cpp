/* Copyright (c) 2025-2026 Your Company or Name
 * License-Identifier: LicenseRef-Fab-Standard-EULA
 *
 * This file is part of the "UII Internal Index Service Bridge" Unreal Engine plugin.
 * Use of this software is governed by the Fab Standard End User License Agreement
 * (EULA) applicable to this product, available at:
 * https://www.fab.com/eula
 *
 * Except as expressly permitted by the Fab Standard EULA, any reproduction,
 * distribution, modification, or use of this software, in whole or in part,
 * is strictly prohibited.
 *
 * This software is provided on an "AS IS" basis, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied, including but not
 * limited to warranties of merchantability, fitness for a particular purpose,
 * and non-infringement.
 * available at: https://www.fab.com/eula.  */

#include "UIIInternalIndexServiceHandoffImporter.h"

#include "IISAgentAccessService.h"
#include "IISChunkCatalog.h"
#include "IISContextPackTypes.h"
#include "IISEmbeddingJobQueue.h"
#include "IISImportTypes.h"
#include "IISLocalIndexService.h"
#include "IISPreparedChunkImporter.h"
#include "IISUsageGraphImporter.h"
#include "IISSearchTypes.h"
#include "IISStoragePaths.h"
#include "Dom/JsonObject.h"
#include "HAL/FileManager.h"
#include "Misc/DateTime.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Policies/PrettyJsonPrintPolicy.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace
{
	// Menu actions use a small bounded execution count so a docking smoke test
	// cannot accidentally process a large project-wide embedding backlog.
	constexpr int32 DefaultMaxEmbeddingJobs = 10;

	FString NormalizePath(const FString& Path)
	{
		if (Path.IsEmpty())
		{
			return FString();
		}

		FString Normalized = FPaths::ConvertRelativePathToFull(Path);
		FPaths::NormalizeFilename(Normalized);
		return Normalized;
	}

	FString UIIOutputRoot()
	{
		// This is the one UII path convention the bridge knows. IIS itself stays
		// independent from UII and only receives resolved local file paths.
		return NormalizePath(FPaths::ProjectSavedDir() / TEXT("UnrealIntegrationIntelligence"));
	}

	bool LoadJsonFile(const FString& FilePath, TSharedPtr<FJsonObject>& OutObject, FString& OutError)
	{
		FString JsonText;
		if (!FFileHelper::LoadFileToString(JsonText, *FilePath))
		{
			OutError = FString::Printf(TEXT("JSON file could not be read: %s"), *FilePath);
			return false;
		}

		const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonText);
		if (!FJsonSerializer::Deserialize(Reader, OutObject) || !OutObject.IsValid())
		{
			OutError = FString::Printf(TEXT("JSON parse failed: %s"), *FilePath);
			return false;
		}
		return true;
	}

	bool SaveJsonObject(const TSharedPtr<FJsonObject>& Object, const FString& TargetPath)
	{
		const FString NormalizedPath = NormalizePath(TargetPath);
		IFileManager::Get().MakeDirectory(*FPaths::GetPath(NormalizedPath), true);

		FString Output;
		TSharedRef<TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>> Writer =
			TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(&Output);
		if (!FJsonSerializer::Serialize(Object.ToSharedRef(), Writer))
		{
			return false;
		}
		return FFileHelper::SaveStringToFile(Output, *NormalizedPath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
	}

	FString GetStringField(const TSharedPtr<FJsonObject>& Object, const FString& FieldName)
	{
		FString Value;
		if (Object.IsValid())
		{
			Object->TryGetStringField(FieldName, Value);
		}
		return Value;
	}

	int32 GetIntField(const TSharedPtr<FJsonObject>& Object, const FString& FieldName)
	{
		double Value = 0.0;
		if (Object.IsValid() && Object->TryGetNumberField(FieldName, Value))
		{
			return static_cast<int32>(Value);
		}
		return 0;
	}

	TSharedPtr<FJsonObject> GetObjectField(const TSharedPtr<FJsonObject>& Object, const FString& FieldName)
	{
		const TSharedPtr<FJsonObject>* Child = nullptr;
		if (Object.IsValid() && Object->TryGetObjectField(FieldName, Child) && Child)
		{
			return *Child;
		}
		return nullptr;
	}

	TArray<FString> GetStringArrayField(const TSharedPtr<FJsonObject>& Object, const FString& FieldName)
	{
		TArray<FString> Values;
		const TArray<TSharedPtr<FJsonValue>>* JsonValues = nullptr;
		if (!Object.IsValid() || !Object->TryGetArrayField(FieldName, JsonValues))
		{
			return Values;
		}

		for (const TSharedPtr<FJsonValue>& JsonValue : *JsonValues)
		{
			FString Value;
			if (JsonValue.IsValid() && JsonValue->TryGetString(Value))
			{
				Values.Add(Value);
			}
		}
		Values.Sort();
		return Values;
	}

	TArray<TSharedPtr<FJsonValue>> MakeStringArray(const TArray<FString>& Values)
	{
		TArray<TSharedPtr<FJsonValue>> JsonValues;
		for (const FString& Value : Values)
		{
			JsonValues.Add(MakeShared<FJsonValueString>(Value));
		}
		return JsonValues;
	}

	FString SearchStatusToString(const EIISSearchStatus Status)
	{
		switch (Status)
		{
		case EIISSearchStatus::Ready: return TEXT("Ready");
		case EIISSearchStatus::Empty: return TEXT("Empty");
		case EIISSearchStatus::Warning: return TEXT("Warning");
		case EIISSearchStatus::Error: return TEXT("Error");
		default: return TEXT("Unknown");
		}
	}

	FString ContextPackStatusToString(const EIISContextPackStatus Status)
	{
		switch (Status)
		{
		case EIISContextPackStatus::Ready: return TEXT("Ready");
		case EIISContextPackStatus::Empty: return TEXT("Empty");
		case EIISContextPackStatus::Warning: return TEXT("Warning");
		case EIISContextPackStatus::Error: return TEXT("Error");
		default: return TEXT("Unknown");
		}
	}

	TArray<FString> DockingGuardrails()
	{
		return {
			TEXT("This workflow imports evidence only."),
			TEXT("It does not authorize migration, placement, patching, copying, or project mutation."),
			TEXT("IIS may index and retrieve evidence, but it does not change Unreal project assets or source files.")
		};
	}

	FString ResolveContractPathValue(const FString& PathValue, const FString& ContractDirectory)
	{
		if (PathValue.IsEmpty())
		{
			return FString();
		}
		return FPaths::IsRelative(PathValue)
			? NormalizePath(FPaths::Combine(ContractDirectory, PathValue))
			: NormalizePath(PathValue);
	}

	FString ResolveInputFileRefPath(const TSharedPtr<FJsonObject>& ContractObject, const FString& LogicalName)
	{
		// Newer contracts may store files in an input_files array instead of flat
		// path fields. Resolve those entries relative to the UII output root.
		const TArray<TSharedPtr<FJsonValue>>* InputFiles = nullptr;
		if (!ContractObject.IsValid() || !ContractObject->TryGetArrayField(TEXT("input_files"), InputFiles))
		{
			return FString();
		}

		for (const TSharedPtr<FJsonValue>& InputValue : *InputFiles)
		{
			const TSharedPtr<FJsonObject> InputObject = InputValue.IsValid() ? InputValue->AsObject() : nullptr;
			if (!InputObject.IsValid() || GetStringField(InputObject, TEXT("logical_name")) != LogicalName)
			{
				continue;
			}

			const FString RelativePath = GetStringField(InputObject, TEXT("relative_path"));
			return RelativePath.IsEmpty()
				? FString()
				: NormalizePath(FPaths::Combine(UIIOutputRoot(), RelativePath));
		}

		return FString();
	}

	struct FResolvedHandoffContract
	{
		// Normalized contract state used by the pipeline after both old flat
		// fields and newer input_files entries have been resolved.
		FString ContractPath;
		FString SourceId;
		FString SourceRunId;
		FString DestinationRunId;
		FIISImportInputFiles InputFiles;
		FString RagExportPackagePath;
		FString RagConsumerContractPath;
		FString LangGraphHandoffEnvelopePath;
		TArray<FString> Guardrails;
		TArray<FString> ForbiddenActions;
	};

	FString GetFlatOrInputFilePath(
		const TSharedPtr<FJsonObject>& ContractObject,
		const FString& ContractDirectory,
		const FString& FlatFieldName,
		const FString& InputLogicalName)
	{
		// Prefer explicit flat contract fields for backward compatibility. Fall
		// back to input_files so the bridge can consume newer handoff manifests.
		const FString FlatPath = ResolveContractPathValue(GetStringField(ContractObject, FlatFieldName), ContractDirectory);
		return FlatPath.IsEmpty() ? ResolveInputFileRefPath(ContractObject, InputLogicalName) : FlatPath;
	}

	bool ResolveHandoffContract(
		const FString& ContractPath,
		FResolvedHandoffContract& OutContract,
		TArray<FString>& OutWarnings,
		TArray<FString>& OutErrors)
	{
		// Contract resolution is validation-only. No IIS import or indexing work
		// starts until all required UII evidence files are known and readable.
		OutContract = FResolvedHandoffContract();
		OutContract.ContractPath = NormalizePath(ContractPath);
		if (OutContract.ContractPath.IsEmpty() || !FPaths::FileExists(OutContract.ContractPath))
		{
			OutErrors.Add(FString::Printf(TEXT("UII IIS handoff contract is missing: %s"), *OutContract.ContractPath));
			return false;
		}

		TSharedPtr<FJsonObject> ContractObject;
		FString Error;
		if (!LoadJsonFile(OutContract.ContractPath, ContractObject, Error))
		{
			OutErrors.Add(Error);
			return false;
		}

		const FString ContractDirectory = FPaths::GetPath(OutContract.ContractPath);
		OutContract.SourceId = GetStringField(ContractObject, TEXT("source_id"));
		OutContract.SourceRunId = GetStringField(ContractObject, TEXT("source_run_id"));
		OutContract.DestinationRunId = GetStringField(ContractObject, TEXT("destination_run_id"));
		OutContract.InputFiles.PreparedChunksJsonlPath = GetFlatOrInputFilePath(
			ContractObject, ContractDirectory, TEXT("prepared_chunks_jsonl_path"), TEXT("prepared_chunks_jsonl"));
		OutContract.InputFiles.PreparedChunksManifestPath = GetFlatOrInputFilePath(
			ContractObject, ContractDirectory, TEXT("prepared_chunks_manifest_path"), TEXT("prepared_chunks_manifest"));
		OutContract.InputFiles.RetrievalLabelsPath = GetFlatOrInputFilePath(
			ContractObject, ContractDirectory, TEXT("retrieval_labels_path"), TEXT("retrieval_labels"));
		OutContract.InputFiles.RetrievalGroupsPath = GetFlatOrInputFilePath(
			ContractObject, ContractDirectory, TEXT("retrieval_groups_path"), TEXT("retrieval_groups"));
		OutContract.RagExportPackagePath = GetFlatOrInputFilePath(
			ContractObject, ContractDirectory, TEXT("rag_export_package_path"), TEXT("rag_export_package"));
		OutContract.RagConsumerContractPath = GetFlatOrInputFilePath(
			ContractObject, ContractDirectory, TEXT("rag_consumer_contract_path"), TEXT("rag_consumer_contract"));
		OutContract.LangGraphHandoffEnvelopePath = GetFlatOrInputFilePath(
			ContractObject, ContractDirectory, TEXT("langgraph_handoff_envelope_path"), TEXT("langgraph_handoff_envelope"));
		OutContract.Guardrails = GetStringArrayField(ContractObject, TEXT("guardrails"));
		OutContract.ForbiddenActions = GetStringArrayField(ContractObject, TEXT("forbidden_actions"));
		if (OutContract.Guardrails.Num() == 0)
		{
			OutContract.Guardrails = DockingGuardrails();
		}

		auto ValidateRequired = [&OutErrors](const FString& LogicalName, const FString& Path)
		{
			if (Path.IsEmpty() || !FPaths::FileExists(Path))
			{
				OutErrors.Add(FString::Printf(TEXT("Required UII handoff file is missing: %s (%s)"), *LogicalName, *Path));
			}
		};
		auto ValidateOptional = [&OutWarnings](const FString& LogicalName, const FString& Path)
		{
			if (!Path.IsEmpty() && !FPaths::FileExists(Path))
			{
				OutWarnings.Add(FString::Printf(TEXT("Optional UII handoff file is not present: %s (%s)"), *LogicalName, *Path));
			}
		};

		ValidateRequired(TEXT("prepared_chunks_jsonl_path"), OutContract.InputFiles.PreparedChunksJsonlPath);
		ValidateRequired(TEXT("prepared_chunks_manifest_path"), OutContract.InputFiles.PreparedChunksManifestPath);
		ValidateRequired(TEXT("retrieval_labels_path"), OutContract.InputFiles.RetrievalLabelsPath);
		ValidateRequired(TEXT("retrieval_groups_path"), OutContract.InputFiles.RetrievalGroupsPath);
		ValidateOptional(TEXT("rag_export_package_path"), OutContract.RagExportPackagePath);
		ValidateOptional(TEXT("rag_consumer_contract_path"), OutContract.RagConsumerContractPath);
		ValidateOptional(TEXT("langgraph_handoff_envelope_path"), OutContract.LangGraphHandoffEnvelopePath);

		return OutErrors.Num() == 0;
	}

	void ReadImportReportSummary(
		const FString& ReportPath,
		FString& OutStatus,
		int32& OutImportedChunks,
		int32& OutDuplicateChunks)
	{
		TSharedPtr<FJsonObject> ReportObject;
		FString Error;
		if (!LoadJsonFile(ReportPath, ReportObject, Error))
		{
			return;
		}
		OutStatus = GetStringField(ReportObject, TEXT("status"));
		const TSharedPtr<FJsonObject> SummaryObject = GetObjectField(ReportObject, TEXT("summary"));
		OutImportedChunks = GetIntField(SummaryObject, TEXT("imported_chunk_count"));
		OutDuplicateChunks = GetIntField(SummaryObject, TEXT("duplicate_chunk_count"));
	}

	void ReadCatalogReportSummary(
		const FString& ReportPath,
		FString& OutStatus,
		int32& OutCatalogChunks)
	{
		TSharedPtr<FJsonObject> ReportObject;
		FString Error;
		if (!LoadJsonFile(ReportPath, ReportObject, Error))
		{
			return;
		}
		const TSharedPtr<FJsonObject> SummaryObject = GetObjectField(ReportObject, TEXT("summary"));
		OutStatus = GetStringField(SummaryObject, TEXT("status"));
		OutCatalogChunks = GetIntField(SummaryObject, TEXT("catalog_chunk_count"));
	}

	void ReadEmbeddingReportSummary(
		const FString& ReportPath,
		int32& OutJobs,
		int32& OutCompleted,
		int32& OutVectors)
	{
		TSharedPtr<FJsonObject> ReportObject;
		FString Error;
		if (!LoadJsonFile(ReportPath, ReportObject, Error))
		{
			return;
		}
		const TSharedPtr<FJsonObject> SummaryObject = GetObjectField(ReportObject, TEXT("summary"));
		OutJobs = GetIntField(SummaryObject, TEXT("job_count"));
		OutCompleted = GetIntField(SummaryObject, TEXT("completed_count"));
		OutVectors = GetIntField(SummaryObject, TEXT("vector_count"));
	}

	void ReadVectorManifest(
		int32& OutVectorCount,
		int32& OutDimensions,
		TArray<FString>& OutProviderIds,
		TArray<FString>& OutModelIds)
	{
		TSharedPtr<FJsonObject> ManifestObject;
		FString Error;
		const FString ManifestPath = FIISStoragePaths::GetVectorsDir() / TEXT("vector_store_manifest.json");
		if (!LoadJsonFile(ManifestPath, ManifestObject, Error))
		{
			return;
		}
		OutVectorCount = GetIntField(ManifestObject, TEXT("vector_count"));
		OutDimensions = GetIntField(ManifestObject, TEXT("dimensions"));
		OutProviderIds = GetStringArrayField(ManifestObject, TEXT("provider_ids"));
		OutModelIds = GetStringArrayField(ManifestObject, TEXT("model_ids"));
	}

	bool WriteDockingReportMarkdown(
		const TSharedPtr<FJsonObject>& ReportObject,
		const FString& TargetPath)
	{
		TArray<FString> Lines;
		Lines.Add(TEXT("# UII IIS Docking Report"));
		Lines.Add(TEXT(""));
		Lines.Add(FString::Printf(TEXT("- OverallStatus: %s"), *GetStringField(ReportObject, TEXT("overall_status"))));
		Lines.Add(FString::Printf(TEXT("- ContractReadable: %s"), ReportObject->GetBoolField(TEXT("uii_contract_readable")) ? TEXT("true") : TEXT("false")));
		Lines.Add(FString::Printf(TEXT("- PreparedChunksReadable: %s"), ReportObject->GetBoolField(TEXT("prepared_chunks_readable")) ? TEXT("true") : TEXT("false")));
		Lines.Add(FString::Printf(TEXT("- ImportStatus: %s"), *GetStringField(ReportObject, TEXT("import_status"))));
		Lines.Add(FString::Printf(TEXT("- CatalogStatus: %s"), *GetStringField(ReportObject, TEXT("catalog_status"))));
		Lines.Add(FString::Printf(TEXT("- EmbeddingStatus: %s"), *GetStringField(ReportObject, TEXT("embedding_status"))));
		Lines.Add(FString::Printf(TEXT("- VectorStatus: %s"), *GetStringField(ReportObject, TEXT("vector_status"))));
		Lines.Add(FString::Printf(TEXT("- HybridSearchStatus: %s"), *GetStringField(ReportObject, TEXT("hybrid_search_status"))));
		Lines.Add(FString::Printf(TEXT("- ContextPackStatus: %s"), *GetStringField(ReportObject, TEXT("context_pack_status"))));
		Lines.Add(FString::Printf(TEXT("- AgentContractStatus: %s"), *GetStringField(ReportObject, TEXT("agent_contract_status"))));
		Lines.Add(TEXT(""));
		Lines.Add(TEXT("## Outputs"));
		Lines.Add(FString::Printf(TEXT("- ImportReport: %s"), *GetStringField(ReportObject, TEXT("import_report_path"))));
		Lines.Add(FString::Printf(TEXT("- CatalogReport: %s"), *GetStringField(ReportObject, TEXT("catalog_report_path"))));
		Lines.Add(FString::Printf(TEXT("- EmbeddingReport: %s"), *GetStringField(ReportObject, TEXT("embedding_report_path"))));
		Lines.Add(FString::Printf(TEXT("- SearchReport: %s"), *GetStringField(ReportObject, TEXT("search_report_path"))));
		Lines.Add(FString::Printf(TEXT("- ContextPackReport: %s"), *GetStringField(ReportObject, TEXT("context_pack_report_path"))));
		Lines.Add(FString::Printf(TEXT("- AgentContracts: %s"), *GetStringField(ReportObject, TEXT("agent_contracts_path"))));
		Lines.Add(TEXT(""));
		Lines.Add(TEXT("## Guardrails"));
		for (const FString& Guardrail : GetStringArrayField(ReportObject, TEXT("guardrails")))
		{
			Lines.Add(FString::Printf(TEXT("- %s"), *Guardrail));
		}
		Lines.Add(TEXT(""));
		Lines.Add(TEXT("## Warnings"));
		for (const FString& Warning : GetStringArrayField(ReportObject, TEXT("warnings")))
		{
			Lines.Add(FString::Printf(TEXT("- %s"), *Warning));
		}
		Lines.Add(TEXT(""));
		Lines.Add(TEXT("## Errors"));
		for (const FString& ReportError : GetStringArrayField(ReportObject, TEXT("errors")))
		{
			Lines.Add(FString::Printf(TEXT("- %s"), *ReportError));
		}

		IFileManager::Get().MakeDirectory(*FPaths::GetPath(TargetPath), true);
		return FFileHelper::SaveStringArrayToFile(Lines, *TargetPath);
	}

	bool RunPipeline(
		const FString& ContractPath,
		const bool bBuildCatalog,
		const bool bBuildEmbeddings,
		const int32 MaxEmbeddingJobs,
		FString& OutReportPath,
		TArray<FString>& OutWarnings)
	{
		FIISStoragePaths::EnsureDefaultFolders();
		OutReportPath.Reset();
		OutWarnings.Reset();

		TArray<FString> Warnings;
		TArray<FString> Errors;
		FResolvedHandoffContract HandoffContract;
		const bool bContractReadable = ResolveHandoffContract(ContractPath, HandoffContract, Warnings, Errors);
		const bool bPreparedChunksReadable = bContractReadable && FPaths::FileExists(HandoffContract.InputFiles.PreparedChunksJsonlPath);

		// Phase 1: import the prepared chunks referenced by the UII contract into
		// the IIS local chunk store. The bridge does not parse or mutate chunks.
		FString ImportReportPath;
		FString ImportStatus = TEXT("NotRun");
		int32 ImportedChunks = 0;
		int32 DuplicateChunks = 0;
		bool bImportOk = false;
		if (bContractReadable && bPreparedChunksReadable)
		{
			bImportOk = FIISPreparedChunkImporter::ImportPreparedChunks(HandoffContract.InputFiles, ImportReportPath, Warnings);
			ReadImportReportSummary(ImportReportPath, ImportStatus, ImportedChunks, DuplicateChunks);
		}

		FString CatalogReportPath;
		FString CatalogStatus = TEXT("NotRun");
		int32 CatalogChunkCount = 0;
		bool bCatalogOk = !bBuildCatalog;
		if (bBuildCatalog && bImportOk)
		{
			// Phase 2: rebuild IIS' local catalog and optional usage graph from
			// imported evidence. IIS owns schema and storage details.
			bCatalogOk = FIISChunkCatalog::BuildOrUpdateCatalogFromChunkStore(CatalogReportPath, Warnings);
			ReadCatalogReportSummary(CatalogReportPath, CatalogStatus, CatalogChunkCount);
			if (bCatalogOk && bContractReadable)
			{
				FIISUsageGraphImporter::ImportFromHandoff(HandoffContract.ContractPath, Warnings);
			}
		}

		FString EmbeddingReportPath;
		FString EmbeddingStatus = TEXT("NotRun");
		int32 EmbeddingJobCount = 0;
		int32 CompletedEmbeddingCount = 0;
		int32 ReportVectorCount = 0;
		bool bEmbeddingOk = !bBuildEmbeddings;
		if (bBuildEmbeddings && bCatalogOk)
		{
			// Phase 3: ask IIS to create and execute embedding jobs. Provider and
			// model selection remain delegated through IIS' embedding executor API.
			FString BuildJobsReportPath;
			FIISEmbeddingJobQueue::BuildEmbeddingJobsFromCatalog(BuildJobsReportPath, Warnings);
			bEmbeddingOk = FIISEmbeddingJobQueue::ExecutePendingEmbeddingJobs(
				MaxEmbeddingJobs > 0 ? MaxEmbeddingJobs : DefaultMaxEmbeddingJobs,
				EmbeddingReportPath,
				Warnings);
			ReadEmbeddingReportSummary(EmbeddingReportPath, EmbeddingJobCount, CompletedEmbeddingCount, ReportVectorCount);
			EmbeddingStatus = bEmbeddingOk ? TEXT("Completed") : TEXT("Warning");
		}

		int32 VectorCount = 0;
		int32 VectorDimensions = 0;
		TArray<FString> ProviderIds;
		TArray<FString> ModelIds;
		ReadVectorManifest(VectorCount, VectorDimensions, ProviderIds, ModelIds);
		const FString VectorStatus = VectorCount > 0 ? TEXT("Ready") : TEXT("NotReady");

		FString SearchReportPath;
		FString HybridSearchStatus = TEXT("NotRun");
		int32 HybridResultCount = 0;
		FString ContextPackReportPath;
		FString ContextPackStatus = TEXT("NotRun");
		int32 ContextPackItemCount = 0;
		if (bBuildCatalog && bCatalogOk)
		{
			// Phase 4: run a local smoke retrieval to prove the imported evidence
			// can be searched and packaged without generating AI answers.
			FIISLocalIndexService Service;
			FIISSearchQuery Query;
			Query.QueryText = TEXT("guardrail");
			Query.SearchMode = EIISSearchMode::Hybrid;
			Query.MaxResults = 10;

			FIISSearchResponse SearchResponse;
			Service.Search(Query, SearchResponse);
			HybridSearchStatus = SearchStatusToString(SearchResponse.Status);
			HybridResultCount = SearchResponse.Results.Num();

			FIISContextPack ContextPack;
			Service.BuildContextPack(Query, ContextPack);
			ContextPackStatus = ContextPackStatusToString(ContextPack.Status);
			ContextPackItemCount = ContextPack.Items.Num();
			FIISChunkCatalog::WriteSearchReport(Query, SearchResponse, &ContextPack, SearchReportPath);
			FIISChunkCatalog::WriteContextPackReport(ContextPack, ContextPackReportPath);
		}

		FString AgentContractsPath;
		FString AgentContractStatus = TEXT("NotRun");
		if (bBuildCatalog && bCatalogOk)
		{
			// Phase 5: export IIS agent tool contracts so local agents can discover
			// evidence-only tools after the handoff pipeline has run.
			const bool bAgentContractsOk = FIISAgentAccessService::WriteAgentToolContracts(AgentContractsPath);
			AgentContractStatus = bAgentContractsOk ? TEXT("Ready") : TEXT("Error");
			if (!bAgentContractsOk)
			{
				Warnings.Add(TEXT("IIS agent tool contracts could not be written."));
			}
		}

		const bool bPipelineOk = bContractReadable
			&& bPreparedChunksReadable
			&& bImportOk
			&& bCatalogOk
			&& bEmbeddingOk
			&& Errors.Num() == 0;
		const FString OverallStatus = bPipelineOk
			? (Warnings.Num() > 0 ? TEXT("Warning") : TEXT("Ready"))
			: TEXT("Error");

		TSharedPtr<FJsonObject> ReportObject = MakeShared<FJsonObject>();
		// The docking report is the single operator-facing summary for this
		// bridge run. It preserves guardrails and false mutation flags.
		ReportObject->SetStringField(TEXT("schema_version"), TEXT("0.1.0"));
		ReportObject->SetStringField(TEXT("tool_name"), TEXT("Internal Index Service"));
		ReportObject->SetStringField(TEXT("generated_at_utc"), FDateTime::UtcNow().ToIso8601());
		ReportObject->SetStringField(TEXT("overall_status"), OverallStatus);
		ReportObject->SetStringField(TEXT("uii_contract_path"), HandoffContract.ContractPath);
		ReportObject->SetStringField(TEXT("source_id"), HandoffContract.SourceId);
		ReportObject->SetStringField(TEXT("source_run_id"), HandoffContract.SourceRunId);
		ReportObject->SetStringField(TEXT("destination_run_id"), HandoffContract.DestinationRunId);
		ReportObject->SetStringField(TEXT("prepared_chunks_jsonl_path"), HandoffContract.InputFiles.PreparedChunksJsonlPath);
		ReportObject->SetStringField(TEXT("prepared_chunks_manifest_path"), HandoffContract.InputFiles.PreparedChunksManifestPath);
		ReportObject->SetStringField(TEXT("retrieval_labels_path"), HandoffContract.InputFiles.RetrievalLabelsPath);
		ReportObject->SetStringField(TEXT("retrieval_groups_path"), HandoffContract.InputFiles.RetrievalGroupsPath);
		ReportObject->SetStringField(TEXT("rag_export_package_path"), HandoffContract.RagExportPackagePath);
		ReportObject->SetStringField(TEXT("rag_consumer_contract_path"), HandoffContract.RagConsumerContractPath);
		ReportObject->SetStringField(TEXT("langgraph_handoff_envelope_path"), HandoffContract.LangGraphHandoffEnvelopePath);
		ReportObject->SetBoolField(TEXT("uii_contract_readable"), bContractReadable);
		ReportObject->SetBoolField(TEXT("prepared_chunks_readable"), bPreparedChunksReadable);
		ReportObject->SetStringField(TEXT("import_status"), ImportStatus);
		ReportObject->SetStringField(TEXT("import_report_path"), ImportReportPath);
		ReportObject->SetNumberField(TEXT("imported_chunks"), ImportedChunks);
		ReportObject->SetNumberField(TEXT("duplicate_chunks"), DuplicateChunks);
		ReportObject->SetStringField(TEXT("catalog_status"), CatalogStatus);
		ReportObject->SetStringField(TEXT("catalog_report_path"), CatalogReportPath);
		ReportObject->SetNumberField(TEXT("catalog_chunk_count"), CatalogChunkCount);
		ReportObject->SetStringField(TEXT("embedding_status"), EmbeddingStatus);
		ReportObject->SetStringField(TEXT("embedding_report_path"), EmbeddingReportPath);
		ReportObject->SetNumberField(TEXT("embedding_job_count"), EmbeddingJobCount);
		ReportObject->SetNumberField(TEXT("completed_embedding_count"), CompletedEmbeddingCount);
		ReportObject->SetStringField(TEXT("vector_status"), VectorStatus);
		ReportObject->SetStringField(TEXT("vector_store_path"), FIISStoragePaths::GetVectorsDir() / TEXT("chunk_vectors.jsonl"));
		ReportObject->SetNumberField(TEXT("vector_count"), VectorCount > 0 ? VectorCount : ReportVectorCount);
		ReportObject->SetNumberField(TEXT("vector_dimensions"), VectorDimensions);
		ReportObject->SetArrayField(TEXT("provider_ids"), MakeStringArray(ProviderIds));
		ReportObject->SetArrayField(TEXT("model_ids"), MakeStringArray(ModelIds));
		ReportObject->SetStringField(TEXT("hybrid_search_status"), HybridSearchStatus);
		ReportObject->SetStringField(TEXT("hybrid_smoke_query"), TEXT("guardrail"));
		ReportObject->SetStringField(TEXT("search_report_path"), SearchReportPath);
		ReportObject->SetNumberField(TEXT("hybrid_result_count"), HybridResultCount);
		ReportObject->SetStringField(TEXT("context_pack_status"), ContextPackStatus);
		ReportObject->SetStringField(TEXT("context_pack_report_path"), ContextPackReportPath);
		ReportObject->SetNumberField(TEXT("context_pack_item_count"), ContextPackItemCount);
		ReportObject->SetStringField(TEXT("agent_contract_status"), AgentContractStatus);
		ReportObject->SetStringField(TEXT("agent_contracts_path"), AgentContractsPath);
		ReportObject->SetArrayField(TEXT("guardrails"), MakeStringArray(HandoffContract.Guardrails.Num() > 0 ? HandoffContract.Guardrails : DockingGuardrails()));
		ReportObject->SetArrayField(TEXT("forbidden_actions"), MakeStringArray(HandoffContract.ForbiddenActions));
		ReportObject->SetBoolField(TEXT("allows_migration_decision"), false);
		ReportObject->SetBoolField(TEXT("allows_patch_generation"), false);
		ReportObject->SetBoolField(TEXT("allows_project_mutation"), false);
		ReportObject->SetArrayField(TEXT("warnings"), MakeStringArray(Warnings));
		ReportObject->SetArrayField(TEXT("errors"), MakeStringArray(Errors));

		OutReportPath = FIISStoragePaths::GetReportsDir() / TEXT("uii_iis_docking_report.json");
		const FString MarkdownReportPath = FIISStoragePaths::GetReportsDir() / TEXT("uii_iis_docking_report.md");
		const bool bJsonOk = SaveJsonObject(ReportObject, OutReportPath);
		const bool bMarkdownOk = WriteDockingReportMarkdown(ReportObject, MarkdownReportPath);

		OutWarnings.Append(Warnings);
		OutWarnings.Append(Errors);
		return bPipelineOk && bJsonOk && bMarkdownOk;
	}
}

bool FUIIInternalIndexServiceHandoffImporter::ImportUIIHandoffContract(
	const FString& ContractPath,
	FString& OutReportPath,
	TArray<FString>& OutWarnings)
{
	return RunPipeline(ContractPath, false, false, DefaultMaxEmbeddingJobs, OutReportPath, OutWarnings);
}

bool FUIIInternalIndexServiceHandoffImporter::ImportUIIHandoffAndBuildCatalog(
	const FString& ContractPath,
	FString& OutReportPath,
	TArray<FString>& OutWarnings)
{
	return RunPipeline(ContractPath, true, false, DefaultMaxEmbeddingJobs, OutReportPath, OutWarnings);
}

bool FUIIInternalIndexServiceHandoffImporter::ImportUIIHandoffBuildCatalogAndEmbeddings(
	const FString& ContractPath,
	const int32 MaxEmbeddingJobs,
	FString& OutReportPath,
	TArray<FString>& OutWarnings)
{
	return RunPipeline(ContractPath, true, true, MaxEmbeddingJobs, OutReportPath, OutWarnings);
}
