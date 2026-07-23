/* Copyright (c) 2025-2026 Your Company or Name
 * License-Identifier: LicenseRef-Fab-Standard-EULA */

#include "UIIInternalIndexServiceBridgePythonBridge.h"

#include "UIIInternalIndexServiceBridgeBlueprintLibrary.h"

FString UUIIInternalIndexServiceBridgePythonBridge::GetLatestUIIHandoffContractPath()
{
	// Keep the default path construction in one callable wrapper so Python,
	// menu actions, and tests agree on the same handoff location.
	return UUIIInternalIndexServiceBridgeBlueprintLibrary::GetLatestUIIHandoffContractPath();
}

bool UUIIInternalIndexServiceBridgePythonBridge::ImportUIIHandoffContract(
	const FString& ContractPath,
	FString& OutReportPath)
{
	// Warnings are captured in the report written by the runtime importer; this
	// compact wrapper keeps the Python signature easy to call from automation.
	TArray<FString> Warnings;
	return UUIIInternalIndexServiceBridgeBlueprintLibrary::ImportUIIHandoffContract(
		ContractPath,
		OutReportPath,
		Warnings);
}

bool UUIIInternalIndexServiceBridgePythonBridge::ImportUIIHandoffAndBuildCatalog(
	const FString& ContractPath,
	FString& OutReportPath)
{
	// Catalog build remains an IIS operation. The bridge only passes the
	// contract path and returns the report location.
	TArray<FString> Warnings;
	return UUIIInternalIndexServiceBridgeBlueprintLibrary::ImportUIIHandoffAndBuildCatalog(
		ContractPath,
		OutReportPath,
		Warnings);
}

bool UUIIInternalIndexServiceBridgePythonBridge::ImportUIIHandoffBuildCatalogAndEmbeddings(
	const FString& ContractPath,
	const int32 MaxEmbeddingJobs,
	FString& OutReportPath)
{
	// The MaxEmbeddingJobs argument is intentionally exposed so callers can keep
	// editor diagnostics small while still testing the full route.
	TArray<FString> Warnings;
	return UUIIInternalIndexServiceBridgeBlueprintLibrary::ImportUIIHandoffBuildCatalogAndEmbeddings(
		ContractPath,
		MaxEmbeddingJobs,
		OutReportPath,
		Warnings);
}
