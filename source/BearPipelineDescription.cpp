#include "BearGraphics.hpp"
BearPipelineDescription::BearPipelineDescription()
{
	TopologyType = TT_TRIANGLE_LIST;
}

BearPipelineDescription::BearPipelineDescription(const BearPipelineDescription& Right)
{
	TopologyType = TT_TRIANGLE_LIST;
	Copy(Right);
}

BearPipelineDescription::BearPipelineDescription(BearPipelineDescription&& Right)
{
	TopologyType = TT_TRIANGLE_LIST;
	Swap(Right);
}


void BearPipelineDescription::Copy(const BearPipelineDescription& Right)
{
	for (bsize i = 0; i < 16; i++)
		InputLayout.Elements[16] = Right.InputLayout.Elements[16];
	RenderPass = Right.RenderPass;
	Shaders.Pixel = Right.Shaders.Pixel;
	Shaders.Vertex = Right.Shaders.Vertex;
	TopologyType = Right.TopologyType;

	bear_copy(&BlendState, &Right.BlendState,1);
	bear_copy(&DepthStencilState, &Right.DepthStencilState, 1);
	bear_copy(&RasterizerState, &Right.RasterizerState, 1);

}

void BearPipelineDescription::Swap(BearPipelineDescription& Right)
{
	for (bsize i = 0; i < 16; i++)
		bear_swap(InputLayout.Elements[16], Right.InputLayout.Elements[16]);
	RenderPass.swap(Right.RenderPass);
	Shaders.Pixel.swap(Right.Shaders.Pixel);
	Shaders.Pixel.swap(Right.Shaders.Vertex);
	bear_swap(TopologyType, Right.TopologyType);
	bear_swap(&BlendState, &Right.BlendState, 1);
	bear_swap(&DepthStencilState, &Right.DepthStencilState, 1);
	bear_swap(&RasterizerState, &Right.RasterizerState, 1);
}