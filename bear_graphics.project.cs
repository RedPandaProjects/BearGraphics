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
       // Projects.Private.Add("stb_image");
      //  Projects.Private.Add("intelcompressor");
       // Projects.Private.Add("nvtt");
	//	Projects.Private.Add("directx");
		IncludeAutonomousProjects.Add("bear_render_null");
		//IncludeAutonomousProjects.Add("bear_render_dx12");
		//IncludeAutonomousProjects.Add("bear_render_vulkan");
    }
} 