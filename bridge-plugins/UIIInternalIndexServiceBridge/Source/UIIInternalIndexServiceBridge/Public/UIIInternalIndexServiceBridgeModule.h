/* Copyright (c) 2025-2026 Yves Tanas
 * License-Identifier: LicenseRef-Fab-Standard-EULA */

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/**
 * Runtime marker module for the optional UII -> IIS docking bridge.
 *
 * The bridge reads UII handoff files from disk and calls IIS public APIs. It
 * does not run UII extraction and does not mutate Unreal assets or source
 * files.
 */
class FUIIInternalIndexServiceBridgeModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
