/* Copyright (c) 2025-2026 Your Company or Name
 * License-Identifier: LicenseRef-Fab-Standard-EULA */

using UnrealBuildTool;

public class UIIInternalIndexServiceBridgeEditor : ModuleRules
{
	public UIIInternalIndexServiceBridgeEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		CppStandard = CppStandardVersion.Cpp17;

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"Projects",
			"Slate",
			"SlateCore",
			"ToolMenus",
			"UnrealEd",
			"InternalIndexServiceInterface",
			"InternalIndexService",
			"UIIInternalIndexServiceBridge"
		});
	}
}
