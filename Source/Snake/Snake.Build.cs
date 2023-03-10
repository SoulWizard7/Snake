// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Snake : ModuleRules
{
	public Snake(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "Paper2D", "UMG" });
	}
}
