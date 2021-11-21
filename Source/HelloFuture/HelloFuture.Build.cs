// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HelloFuture : ModuleRules
{
	public HelloFuture(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "AIModule", "NavigationSystem", "UMG", "Networking", "Sockets", "WebBrowser", "SlateCore", "ImageWrapper", "RenderCore", "MediaAssets", "DatabaseSupport", "SQLiteCore", "SQLiteSupport" });
        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		//PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay",  });
	}
}
