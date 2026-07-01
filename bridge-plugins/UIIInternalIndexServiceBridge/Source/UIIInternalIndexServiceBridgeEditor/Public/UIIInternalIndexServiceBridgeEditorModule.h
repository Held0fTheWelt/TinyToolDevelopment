/* Copyright (c) 2025-2026 Your Company or Name
 * License-Identifier: LicenseRef-Fab-Standard-EULA */

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FUIIInternalIndexServiceBridgeEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	// Adds lightweight Tools menu diagnostics without introducing a full control
	// panel dependency into the public bridge package.
	void RegisterMenus();

	// Menu command: import the latest UII handoff contract into IIS.
	void ImportUIIHandoff();

	// Menu command: import and rebuild the IIS catalog.
	void ImportUIIHandoffAndBuildCatalog();

	// Menu command: run the bounded local end-to-end evidence pipeline.
	void FullUIIHandoffPipeline();
};
