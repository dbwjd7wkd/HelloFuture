// Multiplayer Master Server Plugin Copyright (C) 2020 MeoPlay <contact@meoplay.com> All Rights Reserved.

using UnrealBuildTool;

public class MultiplayerMasterServerList : ModuleRules
{
	public MultiplayerMasterServerList(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
                "Sockets", "Networking"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
	

    }
}
