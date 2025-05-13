// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GP3_TEAM10 : ModuleRules
{
	public GP3_TEAM10(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
				{ 
					"Core",
					"CoreUObject", 
					"Engine", 
					"InputCore", 
					"EnhancedInput",
					"NavigationSystem",
					"AIModule",
                    "GameplayTasks"
                });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        PublicIncludePaths.AddRange(new string[]
        {
            "GP3_TEAM10/Public/AI",
            "GP3_TEAM10/Public/AI/Tasks",
            "GP3_TEAM10/Public/AI/Services",
            "GP3_TEAM10/Public/AI/Components"
        });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
