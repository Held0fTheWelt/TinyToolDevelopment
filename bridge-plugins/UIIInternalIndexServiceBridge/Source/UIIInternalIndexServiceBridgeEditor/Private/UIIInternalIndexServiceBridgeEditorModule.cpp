/* Copyright (c) 2025-2026 Your Company or Name
 * License-Identifier: LicenseRef-Fab-Standard-EULA */

#include "UIIInternalIndexServiceBridgeEditorModule.h"

#include "UIIInternalIndexServiceBridgePythonBridge.h"
#include "Logging/LogMacros.h"
#include "ToolMenus.h"

DEFINE_LOG_CATEGORY_STATIC(LogUIIIISBridgeEditor, Log, All);

#define LOCTEXT_NAMESPACE "FUIIInternalIndexServiceBridgeEditorModule"

void FUIIInternalIndexServiceBridgeEditorModule::StartupModule()
{
	UE_LOG(LogUIIIISBridgeEditor, Log, TEXT("UIIInternalIndexServiceBridgeEditor started."));

	if (UToolMenus::IsToolMenuUIEnabled())
	{
		RegisterMenus();
	}
	else
	{
		UToolMenus::RegisterStartupCallback(
			FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FUIIInternalIndexServiceBridgeEditorModule::RegisterMenus));
	}
}

void FUIIInternalIndexServiceBridgeEditorModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);
	if (UToolMenus::IsToolMenuUIEnabled())
	{
		UToolMenus::UnregisterOwner(this);
	}

	UE_LOG(LogUIIIISBridgeEditor, Log, TEXT("UIIInternalIndexServiceBridgeEditor shut down."));
}

void FUIIInternalIndexServiceBridgeEditorModule::RegisterMenus()
{
	// The editor menu intentionally calls the same Python/Blueprint wrappers
	// exposed to automation, keeping diagnostics and scripted workflows aligned.
	UToolMenus* ToolMenus = UToolMenus::Get();
	if (!ToolMenus)
	{
		return;
	}

	FToolMenuOwnerScoped OwnerScoped(this);
	UToolMenu* Menu = ToolMenus->ExtendMenu(TEXT("LevelEditor.MainMenu.Tools"));
	if (!Menu)
	{
		return;
	}

	FToolMenuSection& Section = Menu->FindOrAddSection(TEXT("InternalIndexService"));
	Section.AddSubMenu(
		TEXT("UIIInternalIndexServiceBridge"),
		LOCTEXT("UIIIISBridgeMenuLabel", "UII -> Internal Index Service"),
		LOCTEXT("UIIIISBridgeMenuTooltip", "Import UII handoff contracts through the optional IIS bridge."),
		FNewToolMenuDelegate::CreateLambda([this](UToolMenu* SubMenu)
		{
			if (!SubMenu)
			{
				return;
			}

			FToolMenuSection& BridgeSection = SubMenu->FindOrAddSection(TEXT("UIIIISBridgeActions"));
			BridgeSection.AddMenuEntry(
				TEXT("ImportUIIHandoff"),
				LOCTEXT("ImportUIIHandoffLabel", "Import UII Handoff"),
				LOCTEXT("ImportUIIHandoffTooltip", "Import the latest UII IIS handoff contract as local IIS evidence."),
				FSlateIcon(),
				FUIAction(FExecuteAction::CreateRaw(this, &FUIIInternalIndexServiceBridgeEditorModule::ImportUIIHandoff)));

			BridgeSection.AddMenuEntry(
				TEXT("ImportUIIHandoffAndBuildCatalog"),
				LOCTEXT("ImportUIIHandoffAndBuildCatalogLabel", "Import UII Handoff + Build Catalog"),
				LOCTEXT("ImportUIIHandoffAndBuildCatalogTooltip", "Import the latest UII IIS handoff contract and rebuild the local IIS catalog."),
				FSlateIcon(),
				FUIAction(FExecuteAction::CreateRaw(this, &FUIIInternalIndexServiceBridgeEditorModule::ImportUIIHandoffAndBuildCatalog)));

			BridgeSection.AddMenuEntry(
				TEXT("FullUIIHandoffPipeline"),
				LOCTEXT("FullUIIHandoffPipelineLabel", "Full UII Handoff Pipeline"),
				LOCTEXT("FullUIIHandoffPipelineTooltip", "Run import, catalog, embedding jobs, hybrid smoke search, and agent contract export for the latest UII handoff."),
				FSlateIcon(),
				FUIAction(FExecuteAction::CreateRaw(this, &FUIIInternalIndexServiceBridgeEditorModule::FullUIIHandoffPipeline)));
		}));
}

void FUIIInternalIndexServiceBridgeEditorModule::ImportUIIHandoff()
{
	// Import-only is the safest docking action and is useful when operators want
	// to review the IIS import report before building indexes.
	FString ReportPath;
	const bool bSuccess = UUIIInternalIndexServiceBridgePythonBridge::ImportUIIHandoffContract(
		UUIIInternalIndexServiceBridgePythonBridge::GetLatestUIIHandoffContractPath(),
		ReportPath);
	UE_LOG(
		LogUIIIISBridgeEditor,
		Log,
		TEXT("UII -> IIS handoff import %s. Report: %s"),
		bSuccess ? TEXT("succeeded") : TEXT("failed"),
		*ReportPath);
}

void FUIIInternalIndexServiceBridgeEditorModule::ImportUIIHandoffAndBuildCatalog()
{
	// Build the local IIS catalog after import so lexical/hybrid diagnostics can
	// run from the imported evidence.
	FString ReportPath;
	const bool bSuccess = UUIIInternalIndexServiceBridgePythonBridge::ImportUIIHandoffAndBuildCatalog(
		UUIIInternalIndexServiceBridgePythonBridge::GetLatestUIIHandoffContractPath(),
		ReportPath);
	UE_LOG(
		LogUIIIISBridgeEditor,
		Log,
		TEXT("UII -> IIS handoff import + catalog %s. Report: %s"),
		bSuccess ? TEXT("succeeded") : TEXT("failed"),
		*ReportPath);
}

void FUIIInternalIndexServiceBridgeEditorModule::FullUIIHandoffPipeline()
{
	// The full menu path uses a small job cap. Larger embedding runs should be
	// launched explicitly through scripts or IIS tooling.
	FString ReportPath;
	const bool bSuccess = UUIIInternalIndexServiceBridgePythonBridge::ImportUIIHandoffBuildCatalogAndEmbeddings(
		UUIIInternalIndexServiceBridgePythonBridge::GetLatestUIIHandoffContractPath(),
		10,
		ReportPath);
	UE_LOG(
		LogUIIIISBridgeEditor,
		Log,
		TEXT("UII -> IIS full handoff pipeline %s. Report: %s"),
		bSuccess ? TEXT("succeeded") : TEXT("failed"),
		*ReportPath);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUIIInternalIndexServiceBridgeEditorModule, UIIInternalIndexServiceBridgeEditor)
