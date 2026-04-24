// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ActionRL : ModuleRules
{
	public ActionRL(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.Add("ActionRL");
		
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
		
		/* Add modules here */
		PrivateDependencyModuleNames.AddRange(new string[] { "EnhancedInput", "Niagara", "AIModule", "GameplayTags" } );

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
