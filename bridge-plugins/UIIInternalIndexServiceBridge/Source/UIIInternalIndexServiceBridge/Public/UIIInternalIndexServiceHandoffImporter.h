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

#pragma once

#include "CoreMinimal.h"

/**
 * Evidence-only facade for importing UII handoff contracts into IIS.
 *
 * The methods expose three pipeline levels so tools can choose how much work
 * to run: import only, import plus catalog, or full local retrieval readiness
 * with IIS embedding jobs. All work is delegated to IIS public services.
 */
class UIIINTERNALINDEXSERVICEBRIDGE_API FUIIInternalIndexServiceHandoffImporter
{
public:
	// Import prepared chunks referenced by the UII handoff contract into IIS.
	static bool ImportUIIHandoffContract(
		const FString& ContractPath,
		FString& OutReportPath,
		TArray<FString>& OutWarnings);

	// Import the handoff and rebuild the local IIS chunk catalog.
	static bool ImportUIIHandoffAndBuildCatalog(
		const FString& ContractPath,
		FString& OutReportPath,
		TArray<FString>& OutWarnings);

	// Import, build the catalog, create IIS embedding jobs, and execute a bounded
	// number of jobs through the IIS/LLM-Store bridge when it is available.
	static bool ImportUIIHandoffBuildCatalogAndEmbeddings(
		const FString& ContractPath,
		int32 MaxEmbeddingJobs,
		FString& OutReportPath,
		TArray<FString>& OutWarnings);
};
