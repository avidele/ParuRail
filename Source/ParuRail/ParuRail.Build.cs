// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ParuRail : ModuleRules
{
	public ParuRail(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"GameplayAbilities",
			"AIModule",
			"Niagara",
			"NiagaraCore",
			"GameplayTags",
			"GameplayTasks",
			"ModularGameplay",
			"ModularGameplayActors",
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"NavigationSystem"
		});
	}
}