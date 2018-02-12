// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class CHCVoxelProcGenCPP : ModuleRules
{
    private string ModulePath
    {
        get { return ModuleDirectory; }
    }

    // The path to our Third Party code assets; e.g. ProjectFolder/ThirdParty/
    private string ThirdPartyPath
    {
        get { return Path.Combine(ModulePath, "../../ThirdParty/"); }
    }

    public CHCVoxelProcGenCPP(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
        // The path to our game module; e.g.ProjectFolder / Source / ModuleName /

        ////////////////////// Custom Voxel Terrain Stuff Starts Here //////////////////////////////////////
        // You will need to compile and add additional libraries if you want to use this on platforms not listed below!
        switch (Target.Platform)
        {
            // 64-bit Windows
            case UnrealTargetPlatform.Win64:
                PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "accidental-noise-library", "build", "ANL", "x64", "ANL.lib"));
                break;

            // 32-bit Windows
            case UnrealTargetPlatform.Win32:
                PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "accidental-noise-library", "build", "ANL", "x86", "ANL.lib"));
                break;

            // Mac
            case UnrealTargetPlatform.Mac:
                PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "accidental-noise-library", "build", "ANL", "Universal", "libANL.a"));
                break;

            // Linux
            case UnrealTargetPlatform.Linux:
                PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "accidental-noise-library", "build", "ANL", "x64", "libANL.a"));
                break;

            default:
                break;
        }

        // Include the headers for PolyVox and ANL so we can access them later.
        PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "polyvox/include"));
        PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "accidental-noise-library"));
        ////////////////////// End Voxel Terrain Stuff //////////////////////////////////////////////////////
    }
}
