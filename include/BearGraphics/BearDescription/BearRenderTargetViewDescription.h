#pragma once 
namespace BearGraphics
{
	struct BearRenderTargetViewDescription
	{
		BearRenderTargetViewDescription():Width(1024), Height(768),Format(RTF_R8G8B8A8){}
		bsize Width;
		bsize Height;
		BearRenderTargetFormat Format;
	};
}
