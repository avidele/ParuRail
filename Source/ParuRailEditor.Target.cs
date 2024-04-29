// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ParuRailEditorTarget : TargetRules
{
	public ParuRailEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
		ExtraModuleNames.Add("ParuRail");
	}
}