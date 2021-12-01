// Copyright 2021, Athian Games. All Rights Reserved. 

using UnrealBuildTool;
using System.IO;

public class MySQL : ModuleRules
{

    private string LibrariesPath
    {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../Source/Libraries/")); }
    }


    public string GetBinariesPath
    {

        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../Binaries/Win64/")); }
    }


    public MySQL(ReadOnlyTargetRules Target) : base(Target)
    {

        PrivateIncludePaths.AddRange(new string[]
        {
            "MySQL/Private"

        });


        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        bEnableUndefinedIdentifierWarnings = false;
        bEnableExceptions = true;

        PublicDefinitions.Add("NTDDI_WIN7SP1");

        PublicDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject", "Engine", "RHI",
            "ImageWrapper", "RenderCore", "ImageWriteQueue", "InputCore" , "Projects" });
        PrivateDependencyModuleNames.AddRange(new[] { "XmlParser", "Core", "ImageWrapper", "Engine" });

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {


            PublicDelayLoadDLLs.Add(Path.Combine(GetBinariesPath, "FileBrowser.dll"));
            PublicDelayLoadDLLs.Add(Path.Combine(GetBinariesPath, "MySQLLibrary.dll"));
            PublicDelayLoadDLLs.Add(Path.Combine(GetBinariesPath, "mysqlcppconn-9-vs14.dll"));
       
            RuntimeDependencies.Add(Path.Combine(GetBinariesPath, "FileBrowser.dll"));
            RuntimeDependencies.Add(Path.Combine(GetBinariesPath, "MySQLLibrary.dll"));
            RuntimeDependencies.Add(Path.Combine(GetBinariesPath, "mysqlcppconn-9-vs14.dll"));
         }
      
    }
}