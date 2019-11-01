#include "BearGraphics.hpp"

BearGraphics::BearRenderPipelineDescription::BearRenderPipelineDescription()
{
	TopologyType = TT_POINT_LIST;
	BearCore::bear_fill(RenderTargets.Formats, 8, 0);
}

BearGraphics::BearRenderPipelineDescription::BearRenderPipelineDescription(const BearRenderPipelineDescription & Right)
{
	BearCore::bear_fill(RenderTargets.Formats, 8, 0);
	Copy(Right);
}

BearGraphics::BearRenderPipelineDescription::BearRenderPipelineDescription(BearRenderPipelineDescription && Right)
{
	BearCore::bear_fill(RenderTargets.Formats, 8, 0);
	Swap(Right);
}


void BearGraphics::BearRenderPipelineDescription::Copy(const BearRenderPipelineDescription & Right)
{
	for (bsize i = 0; i < 16; i++)
		InputLayout.Elements[16] = Right.InputLayout.Elements[16];
	BearCore::bear_copy(RenderTargets.Formats, Right.RenderTargets.Formats, 8);
	Shaders.Pixel = Right.Shaders.Pixel;
	Shaders.Vertex = Right.Shaders.Vertex;
	TopologyType = Right.TopologyType;
	RootSignature = Right.RootSignature;
}

void BearGraphics::BearRenderPipelineDescription::Swap(BearRenderPipelineDescription & Right)
{
	for (bsize i = 0; i < 16; i++)
		BearCore::bear_swap(InputLayout.Elements[16], Right.InputLayout.Elements[16]);
	BearCore::bear_swap(RenderTargets.Formats, Right.RenderTargets.Formats, 8);
	Shaders.Pixel.swap( Right.Shaders.Pixel);
	Shaders.Pixel.swap( Right.Shaders.Vertex);
	BearCore::bear_swap(TopologyType, Right.TopologyType);
	RootSignature .swap( Right.RootSignature);
}
