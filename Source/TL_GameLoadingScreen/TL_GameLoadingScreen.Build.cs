using UnrealBuildTool;

// This module must be loaded "PreLoadingScreen" in the .uproject file, otherwise it will not hook in time!

public class TL_GameLoadingScreen : ModuleRules
{
    public TL_GameLoadingScreen(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivatePCHHeaderFile = "Public/TL_GameLoadingScreen.h";

		PCHUsage = PCHUsageMode.UseSharedPCHs;

        PrivateDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"CoreUObject",
				"MoviePlayer",
				"Slate",
				"SlateCore",
				"InputCore"
			}
		);
	}
} 
