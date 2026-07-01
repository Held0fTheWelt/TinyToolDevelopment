/* Copyright (c) 2025-2026 Your Company or Name
 * License-Identifier: LicenseRef-Fab-Standard-EULA */

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UIIInternalIndexServiceBridgePythonBridge.generated.h"

UCLASS()
class UIIINTERNALINDEXSERVICEBRIDGEEDITOR_API UUIIInternalIndexServiceBridgePythonBridge : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Returns the conventional latest UII handoff path. The file still has to
	// exist; callers receive a normal pipeline report if it is missing.
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "UII|Internal Index Service Bridge")
	static FString GetLatestUIIHandoffContractPath();

	// Python/Editor wrapper for the import-only pipeline.
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "UII|Internal Index Service Bridge")
	static bool ImportUIIHandoffContract(
		const FString& ContractPath,
		FString& OutReportPath);

	// Python/Editor wrapper for import plus IIS catalog rebuild.
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "UII|Internal Index Service Bridge")
	static bool ImportUIIHandoffAndBuildCatalog(
		const FString& ContractPath,
		FString& OutReportPath);

	// Python/Editor wrapper for the bounded full local handoff pipeline.
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "UII|Internal Index Service Bridge")
	static bool ImportUIIHandoffBuildCatalogAndEmbeddings(
		const FString& ContractPath,
		int32 MaxEmbeddingJobs,
		FString& OutReportPath);
};
