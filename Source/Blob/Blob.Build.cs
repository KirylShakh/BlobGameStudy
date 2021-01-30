// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Blob : ModuleRules
{
	public Blob(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
