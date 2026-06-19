/* Copyright (c) 2025-2026 Yves Tanas
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

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UIIInternalIndexServiceBridgeBlueprintLibrary.generated.h"

/**
 * Blueprint access to the evidence-only UII -> IIS handoff pipeline.
 *
 * These nodes read local UII handoff contracts and delegate import/catalog/
 * embedding work to IIS public APIs. They do not run UII extraction and do not
 * mutate assets, Blueprints, source files, or project settings.
 */
UCLASS()
class UIIINTERNALINDEXSERVICEBRIDGE_API UUIIInternalIndexServiceBridgeBlueprintLibrary
	: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "UII|Internal Index Service Bridge",
		meta = (DisplayName = "Get Latest UII IIS Handoff Contract Path",
			ToolTip = "Returns the conventional latest UII -> IIS handoff contract path under Saved/UnrealIntegrationIntelligence/iis_handoff.",
			Keywords = "UII IIS Handoff Contract Path"))
	static FString GetLatestUIIHandoffContractPath();

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "UII|Internal Index Service Bridge",
		meta = (DisplayName = "Import UII Handoff Contract into IIS",
			ToolTip = "Imports prepared chunks referenced by a UII handoff contract into IIS and writes a docking report.",
			Keywords = "UII IIS Import Handoff Evidence"))
	static bool ImportUIIHandoffContract(
		const FString& ContractPath,
		FString& OutReportPath,
		TArray<FString>& OutWarnings);

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "UII|Internal Index Service Bridge",
		meta = (DisplayName = "Import Latest UII Handoff into IIS",
			ToolTip = "Imports the latest conventional UII handoff contract into IIS.",
			Keywords = "UII IIS Import Latest Handoff Evidence"))
	static bool ImportLatestUIIHandoffContract(
		FString& OutReportPath,
		TArray<FString>& OutWarnings);

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "UII|Internal Index Service Bridge",
		meta = (DisplayName = "Import UII Handoff and Build IIS Catalog",
			ToolTip = "Imports the UII handoff into IIS and rebuilds the IIS chunk catalog.",
			Keywords = "UII IIS Import Handoff Catalog"))
	static bool ImportUIIHandoffAndBuildCatalog(
		const FString& ContractPath,
		FString& OutReportPath,
		TArray<FString>& OutWarnings);

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "UII|Internal Index Service Bridge",
		meta = (DisplayName = "Import Latest UII Handoff and Build IIS Catalog",
			ToolTip = "Imports the latest conventional UII handoff into IIS and rebuilds the IIS chunk catalog.",
			Keywords = "UII IIS Import Latest Handoff Catalog"))
	static bool ImportLatestUIIHandoffAndBuildCatalog(
		FString& OutReportPath,
		TArray<FString>& OutWarnings);

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "UII|Internal Index Service Bridge",
		meta = (DisplayName = "Run Full UII IIS Handoff Pipeline",
			ToolTip = "Imports the UII handoff, builds the IIS catalog, executes a bounded number of IIS embedding jobs, runs smoke retrieval, and writes agent contracts.",
			Keywords = "UII IIS Full Handoff Pipeline Embeddings"))
	static bool ImportUIIHandoffBuildCatalogAndEmbeddings(
		const FString& ContractPath,
		int32 MaxEmbeddingJobs,
		FString& OutReportPath,
		TArray<FString>& OutWarnings);

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "UII|Internal Index Service Bridge",
		meta = (DisplayName = "Run Latest Full UII IIS Handoff Pipeline",
			ToolTip = "Runs the full bounded UII -> IIS pipeline for the latest conventional handoff contract.",
			Keywords = "UII IIS Latest Full Handoff Pipeline Embeddings"))
	static bool ImportLatestUIIHandoffBuildCatalogAndEmbeddings(
		int32 MaxEmbeddingJobs,
		FString& OutReportPath,
		TArray<FString>& OutWarnings);
};
