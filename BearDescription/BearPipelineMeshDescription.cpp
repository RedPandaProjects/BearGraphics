#include "BearGraphics.hpp"
BearPipelineMeshDescription::BearPipelineMeshDescription()
{
}

BearPipelineMeshDescription::BearPipelineMeshDescription(const BearPipelineMeshDescription& Right)
{
	Copy(Right);
}

BearPipelineMeshDescription::BearPipelineMeshDescription(BearPipelineMeshDescription&& Right)
{
	Swap(Right);
}


void BearPipelineMeshDescription::Copy(const BearPipelineMeshDescription& Right)
{
	RenderPass = Right.RenderPass;

	Shaders.Mesh = Right.Shaders.Mesh;
	Shaders.Amplification = Right.Shaders.Amplification;
	Shaders.Pixel = Right.Shaders.Pixel;

	memcpy(&BlendState, &Right.BlendState,sizeof(BlendStateDescription));
	memcpy(&DepthStencilState, &Right.DepthStencilState, sizeof(DepthStencilStateDescription));
	memcpy(&RasterizerState, &Right.RasterizerState, sizeof(RasterizerStateDescription));

}

void BearPipelineMeshDescription::Swap(BearPipelineMeshDescription& Right)
{
	RenderPass.swap(Right.RenderPass);


	Shaders.Mesh.swap(Right.Shaders.Mesh);
	Shaders.Amplification.swap(Right.Shaders.Amplification);
	Shaders.Pixel.swap(Right.Shaders.Pixel);

	std::swap(BlendState, Right.BlendState);
	std::swap(DepthStencilState, Right.DepthStencilState);
	std::swap(RasterizerState, Right.RasterizerState);
}



bool BearPipelineMeshDescription::operator==(const BearPipelineMeshDescription& Right)const
{
	if (RenderPass != Right.RenderPass)
		return false;

	if (Shaders.Mesh != Right.Shaders.Mesh)
		return false;
	if (Shaders.Amplification != Right.Shaders.Amplification)
		return false;
	if (Shaders.Pixel != Right.Shaders.Pixel)
		return false;


	if (memcmp(&BlendState, &Right.BlendState, sizeof(BlendStateDescription) ) != 0)
		return false;
	if (memcmp(&DepthStencilState, &Right.DepthStencilState, sizeof(DepthStencilStateDescription)) != 0)
		return false;

	if (memcmp(&DepthStencilState, &Right.DepthStencilState, sizeof(DepthStencilStateDescription)) != 0)
		return false;
	
	return true;
}
#pragma optimize( "", off )
bool BearPipelineMeshDescription::operator<(const BearPipelineMeshDescription& Right) const
{
	if (RenderPass != Right.RenderPass)
		return RenderPass < Right.RenderPass;


	if (Shaders.Mesh != Right.Shaders.Mesh)
		return Shaders.Mesh < Right.Shaders.Mesh;
	if (Shaders.Amplification != Right.Shaders.Amplification)
		return Shaders.Amplification < Right.Shaders.Amplification;
	if (Shaders.Pixel != Right.Shaders.Pixel)
		return Shaders.Pixel < Right.Shaders.Pixel;

	int result = 0;
	result = memcmp(&BlendState, &Right.BlendState, sizeof(BlendStateDescription));
	if (result != 0)
		return result < 0;
	result = memcmp(&DepthStencilState, &Right.DepthStencilState, sizeof(DepthStencilStateDescription));
	if (result != 0)
		return result<0;
	return memcmp(&DepthStencilState, &Right.DepthStencilState, sizeof(DepthStencilStateDescription))<0;
}
#pragma optimize( "s", on )