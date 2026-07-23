/* Copyright (c) 2025-2026 Your Company or Name
 * License-Identifier: LicenseRef-Fab-Standard-EULA */

#include "UIIInternalIndexServiceBridgeModule.h"

#include "Logging/LogMacros.h"

DEFINE_LOG_CATEGORY_STATIC(LogUIIIISBridge, Log, All);

void FUIIInternalIndexServiceBridgeModule::StartupModule()
{
	// Runtime work is explicit through FUIIInternalIndexServiceHandoffImporter.
	// Startup only announces availability of the optional bridge.
	UE_LOG(LogUIIIISBridge, Log, TEXT("UIIInternalIndexServiceBridge started."));
}

void FUIIInternalIndexServiceBridgeModule::ShutdownModule()
{
	UE_LOG(LogUIIIISBridge, Log, TEXT("UIIInternalIndexServiceBridge shut down."));
}

IMPLEMENT_MODULE(FUIIInternalIndexServiceBridgeModule, UIIInternalIndexServiceBridge)
