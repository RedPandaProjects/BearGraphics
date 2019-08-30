using BearBuildTool.Projects;
using System.IO;
using System;
public class bear_render_base : Project
{
	public bear_render_base(string ProjectPath)
	{
		Include.Public.Add(Path.Combine(ProjectPath,"include","BearRenderBase"));
		Include.Public.Add(Path.Combine(ProjectPath,"include","BearGraphics"));
        Projects.Public.Add("bear_core");
		Projects.Public.Add("bear_graphics");
    }
} 