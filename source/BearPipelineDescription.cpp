#include "BearGraphics.hpp"
BearPipelineDescription::BearPipelineDescription()
{
	TopologyType = TT_TRIANGLE_LIST;
	bear_fill(RenderTargets.Formats, 8, 0);
	RenderTargets.Formats[0] = RTF_R8G8B8A8;
}

BearPipelineDescription::BearPipelineDescription(const BearPipelineDescription& Right)
{
	TopologyType = TT_TRIANGLE_LIST;
	bear_fill(RenderTargets.Formats, 8, 0);
	RenderTargets.Formats[0] = RTF_R8G8B8A8;
	Copy(Right);
}

BearPipelineDescription::BearPipelineDescription(BearPipelineDescription&& Right)
{
	TopologyType = TT_TRIANGLE_LIST;
	bear_fill(RenderTargets.Formats, 8, 0);
	RenderTargets.Formats[0] = RTF_R8G8B8A8;
	Swap(Right);
}


void BearPipelineDescription::Copy(const BearPipelineDescription& Right)
{
	for (bsize i = 0; i < 16; i++)
		InputLayout.Elements[16] = Right.InputLayout.Elements[16];
	bear_copy(RenderTargets.Formats, Right.RenderTargets.Formats, 8);
	Shaders.Pixel = Right.Shaders.Pixel;
	Shaders.Vertex = Right.Shaders.Vertex;
	TopologyType = Right.TopologyType;
}

void BearPipelineDescription::Swap(BearPipelineDescription& Right)
{
	for (bsize i = 0; i < 16; i++)
		bear_swap(InputLayout.Elements[16], Right.InputLayout.Elements[16]);
	bear_swap(RenderTargets.Formats, Right.RenderTargets.Formats, 8);
	Shaders.Pixel.swap(Right.Shaders.Pixel);
	Shaders.Pixel.swap(Right.Shaders.Vertex);
	bear_swap(TopologyType, Right.TopologyType);
}