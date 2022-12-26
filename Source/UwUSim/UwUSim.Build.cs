// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UwUSim : ModuleRules
{
	public UwUSim(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "ROSIntegration" });
		PrivateDependencyModuleNames.AddRange(new string[] { "ROSIntegration" });

	}
}
