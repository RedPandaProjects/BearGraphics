#include "BearGraphics.hpp"
BearPipelineGraphicsDescription::BearPipelineGraphicsDescription()
{
	TopologyType = TT_TRIANGLE_LIST;
}

BearPipelineGraphicsDescription::BearPipelineGraphicsDescription(const BearPipelineGraphicsDescription& Right)
{
	TopologyType = TT_TRIANGLE_LIST;
	Copy(Right);
}

BearPipelineGraphicsDescription::BearPipelineGraphicsDescription(BearPipelineGraphicsDescription&& Right)
{
	TopologyType = TT_TRIANGLE_LIST;
	Swap(Right);
}


void BearPipelineGraphicsDescription::Copy(const BearPipelineGraphicsDescription& Right)
{
	for (bsize i = 0; i < 16; i++)
		InputLayout.Elements[i] = Right.InputLayout.Elements[i];
	RenderPass = Right.RenderPass;

	Shaders.Vertex = Right.Shaders.Vertex;
	Shaders.Hull = Right.Shaders.Hull;
	Shaders.Domain = Right.Shaders.Domain;
	Shaders.Geometry = Right.Shaders.Geometry;
	Shaders.Pixel = Right.Shaders.Pixel;

	TopologyType = Right.TopologyType;

	memcpy(&BlendState, &Right.BlendState,sizeof(BlendStateDescription));
	memcpy(&DepthStencilState, &Right.DepthStencilState, sizeof(DepthStencilStateDescription));
	memcpy(&RasterizerState, &Right.RasterizerState, sizeof(RasterizerStateDescription));

}

void BearPipelineGraphicsDescription::Swap(BearPipelineGraphicsDescription& Right)
{
	for (bsize i = 0; i < 16; i++)
		std::swap(InputLayout.Elements[i], Right.InputLayout.Elements[i]);
	RenderPass.swap(Right.RenderPass);


	Shaders.Vertex.swap(Right.Shaders.Vertex);
	Shaders.Hull.swap(Right.Shaders.Hull);
	Shaders.Domain.swap(Right.Shaders.Domain);
	Shaders.Geometry.swap(Right.Shaders.Geometry);
	Shaders.Pixel.swap(Right.Shaders.Pixel);

	std::swap(TopologyType, Right.TopologyType);
	std::swap(BlendState, Right.BlendState);
	std::swap(DepthStencilState, Right.DepthStencilState);
	std::swap(RasterizerState, Right.RasterizerState);
}



bool BearPipelineGraphicsDescription::operator==(const BearPipelineGraphicsDescription& Right)const
{
	if (RenderPass != Right.RenderPass)
		return false;

	if (Shaders.Vertex != Right.Shaders.Vertex)
		return false;
	if (Shaders.Hull != Right.Shaders.Hull)
		return false;
	if (Shaders.Domain != Right.Shaders.Domain)
		return false;
	if (Shaders.Geometry != Right.Shaders.Geometry)
		return false;
	if (Shaders.Pixel != Right.Shaders.Pixel)
		return false;


	if (TopologyType != Right.TopologyType)
		return false;
	for (bsize i = 0; i < 16; i++)
	{
		if (InputLayout.Elements[i].Type == VF_NONE && Right.InputLayout.Elements[i].Type == VF_NONE)
			break;
		if (InputLayout.Elements[i]!=Right.InputLayout.Elements[i])
			return false;
	}
	if (memcmp(&BlendState, &Right.BlendState, sizeof(BlendStateDescription) ) != 0)
		return false;
	if (memcmp(&DepthStencilState, &Right.DepthStencilState, sizeof(DepthStencilStateDescription)) != 0)
		return false;

	if (memcmp(&DepthStencilState, &Right.DepthStencilState, sizeof(DepthStencilStateDescription)) != 0)
		return false;
	
	return true;
}
#pragma optimize( "", off )
bool BearPipelineGraphicsDescription::operator<(const BearPipelineGraphicsDescription& Right) const
{
	if (RenderPass != Right.RenderPass)
		return RenderPass < Right.RenderPass;


	if (Shaders.Vertex != Right.Shaders.Vertex)
		return Shaders.Vertex < Right.Shaders.Vertex;
	if (Shaders.Hull != Right.Shaders.Hull)
		return Shaders.Hull < Right.Shaders.Hull;
	if (Shaders.Domain != Right.Shaders.Domain)
		return Shaders.Domain < Right.Shaders.Domain;
	if (Shaders.Geometry != Right.Shaders.Geometry)
		return Shaders.Geometry < Right.Shaders.Geometry;
	if (Shaders.Pixel != Right.Shaders.Pixel)
		return Shaders.Pixel < Right.Shaders.Pixel;

	if (TopologyType != Right.TopologyType)
		return TopologyType < Right.TopologyType;
	int result = 0;
	for (bsize i = 0; i < 16; i++)
	{
		if (InputLayout.Elements[i].Type == VF_NONE && Right.InputLayout.Elements[i].Type == VF_NONE)
			break;
		result = InputLayout.Elements[i] < Right.InputLayout.Elements[i];
		if (result != 0)
			return result < 0;
	}
	if (result != 0)
		return result<0;
	result = memcmp(&BlendState, &Right.BlendState, sizeof(BlendStateDescription));
	if (result != 0)
		return result < 0;
	result = memcmp(&DepthStencilState, &Right.DepthStencilState, sizeof(DepthStencilStateDescription));
	if (result != 0)
		return result<0;
	return memcmp(&DepthStencilState, &Right.DepthStencilState, sizeof(DepthStencilStateDescription))<0;
}
#pragma optimize( "s", on )