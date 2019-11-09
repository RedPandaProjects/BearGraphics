#include "BearGraphics.hpp"



void BearGraphics::BearRenderRTXPipelineDescription::Copy(const BearRenderRTXPipelineDescription & Right)
{
	Shaders.RayGeneration.copy(Right.Shaders.RayGeneration);
	Shaders.Hit.copy(Right.Shaders.Hit);
	Shaders.Miss.copy(Right.Shaders.Miss);
	RootSignature.Global.copy(Right.RootSignature.Global);
	RootSignature.Local.copy(Right.RootSignature.Local);
}

void BearGraphics::BearRenderRTXPipelineDescription::Swap(BearRenderRTXPipelineDescription & Right)
{
	Shaders.RayGeneration.swap(Right.Shaders.RayGeneration);
	Shaders.Hit.swap(Right.Shaders.Hit);
	Shaders.Miss.swap(Right.Shaders.Miss);
	RootSignature.Global.swap(Right.RootSignature.Global);
	RootSignature.Local.swap(Right.RootSignature.Local);
}
