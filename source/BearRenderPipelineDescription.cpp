#include "BearGraphics.hpp"

BearGraphics::BearRenderPipelineDescription::BearRenderPipelineDescription()
{
	BearCore::bear_fill(RenderTargets.Formats, 16, 0);
}

BearGraphics::BearRenderPipelineDescription::BearRenderPipelineDescription(const BearRenderPipelineDescription & Right)
{
	BearCore::bear_fill(RenderTargets.Formats, 16, 0);
	Copy(Right);
}

BearGraphics::BearRenderPipelineDescription::BearRenderPipelineDescription(BearRenderPipelineDescription && Right)
{
	BearCore::bear_fill(RenderTargets.Formats, 16, 0);
	Swap(Right);
}

void BearGraphics::BearRenderPipelineDescription::Copy(const BearRenderPipelineDescription & Right)
{
	for (bsize i = 0; i < 16; i++)
		VertexState.Elements[16] = Right.VertexState.Elements[16];
	BearCore::bear_copy(RenderTargets.Formats, Right.RenderTargets.Formats, 16);
	Shaders.Pixel = Right.Shaders.Pixel;
	Shaders.Vertex = Right.Shaders.Vertex;
}

void BearGraphics::BearRenderPipelineDescription::Swap(BearRenderPipelineDescription & Right)
{
	for (bsize i = 0; i < 16; i++)
		BearCore::bear_swap(VertexState.Elements[16], Right.VertexState.Elements[16]);
	BearCore::bear_swap(RenderTargets.Formats, Right.RenderTargets.Formats, 16);
	Shaders.Pixel.swap( Right.Shaders.Pixel);
	Shaders.Pixel.swap( Right.Shaders.Vertex);
}
