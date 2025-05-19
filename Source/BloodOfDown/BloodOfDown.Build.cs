// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BloodOfDown : ModuleRules
{
	public BloodOfDown(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
		{	"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"GameplayTasks",
			"NavigationSystem",
			"UMG",
			"Slate",
			"SlateCore"});
	}
}
