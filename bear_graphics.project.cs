using BearBuildTool.Projects;
using System.IO;
using System;
public class bear_graphics : Project
{
	public bear_graphics(string ProjectPath)
	{
		PCHFile=Path.Combine(ProjectPath,"source", "BearGraphics.PCH.cpp");
		PCHIncludeFile= "BearGraphics.hpp";
		AddSourceFiles(Path.Combine(ProjectPath,"source"),true);
		Include.Public.Add(Path.Combine(ProjectPath,"include","BearGraphics"));
        Projects.Public.Add("bear_core");
       
		 
		Projects.Private.Add("stb_image");
        if (BearBuildTool.Config.Global.DevVersion)
        {
			Projects.Private.Add("intelcompressor");
			Projects.Private.Add("nvtt");
		}
	//	Projects.Private.Add("directx");
		IncludeAutonomousProjects.Add("bear_render_null");
		if (BearBuildTool.Config.Global.Platform == BearBuildTool.Config.Platform.Win64|| BearBuildTool.Config.Global.Platform == BearBuildTool.Config.Platform.Win32)
		{
			IncludeAutonomousProjects.Add("bear_render_dx12");
			IncludeAutonomousProjects.Add("bear_render_dx11");
			IncludeAutonomousProjects.Add("bear_render_dx12_1");
		}	
		IncludeAutonomousProjects.Add("bear_render_vulkan1_0");
		IncludeAutonomousProjects.Add("bear_render_vulkan1_1");
    }
} 