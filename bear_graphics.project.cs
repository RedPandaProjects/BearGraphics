using BearBuildTool.Projects;
using System.IO;
using System;
public class bear_graphics : Project
{
	public bear_graphics(string ProjectPath)
	{
		PCHFile=Path.Combine(ProjectPath,"source", "BearGraphics.cpp");
		PCHIncludeFile= "BearGraphics.hpp";
		AddSourceFiles(Path.Combine(ProjectPath,"source"),true);
		Include.Public.Add(Path.Combine(ProjectPath,"include"));
        Projects.Private.Add("bear_core");
        Projects.Private.Add("stb_image");
        Projects.Private.Add("intelcompressor");
        Projects.Private.Add("nvtt");
		Projects.Private.Add("directx");
		IncludeAutonomousProjects.Add("bear_dx11");
		
    }
} 