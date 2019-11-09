#include "BearGraphics.hpp"

void BearGraphics::BearRenderRootSignatureDescription::Copy(const BearRenderRootSignatureDescription & Right)
{
	for (bsize i = 0; i < 16; i++)
	{
		UniformBuffers[i].Shader = Right.UniformBuffers[i].Shader;
	}
	for (bsize i = 0; i < 16; i++)
	{
		SRVResources[i].Shader = Right.SRVResources[i].Shader;
	}
	for (bsize i = 0; i < 16; i++)
	{
		Samplers[i].Shader = Right.Samplers[i].Shader;
	}
	Local = Right.Local;
}

void BearGraphics::BearRenderRootSignatureDescription::Swap(BearRenderRootSignatureDescription & Right)
{
	for (bsize i = 0; i < 16; i++)
	{
		BearCore::bear_swap(UniformBuffers[i].Shader, Right.UniformBuffers[i].Shader);
	}
	for (bsize i = 0; i < 16; i++)
	{
		BearCore::bear_swap(SRVResources[i].Shader, Right.SRVResources[i].Shader);
	}
	for (bsize i = 0; i < 16; i++)
	{
		BearCore::bear_swap(Samplers[i].Shader, Right.Samplers[i].Shader);
	}
	BearCore::bear_swap(Local ,Right.Local);
}
