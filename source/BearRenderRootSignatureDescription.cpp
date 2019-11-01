#include "BearGraphics.hpp"

void BearGraphics::BearRenderRootSignatureDescription::Copy(const BearRenderRootSignatureDescription & Right)
{
	for (bsize i = 0; i < 16; i++)
	{
		UniformBuffers[i].Shader = Right.UniformBuffers[i].Shader;
	}
	for (bsize i = 0; i < 16; i++)
	{
		TextureBuffers[i].Shader = Right.TextureBuffers[i].Shader;
	}
	for (bsize i = 0; i < 16; i++)
	{
		SamplerStates[i].Shader = Right.SamplerStates[i].Shader;
	}
}

void BearGraphics::BearRenderRootSignatureDescription::Swap(BearRenderRootSignatureDescription & Right)
{
	for (bsize i = 0; i < 16; i++)
	{
		BearCore::bear_swap(UniformBuffers[i].Shader, Right.UniformBuffers[i].Shader);
	}
	for (bsize i = 0; i < 16; i++)
	{
		BearCore::bear_swap(TextureBuffers[i].Shader, Right.TextureBuffers[i].Shader);
	}
	for (bsize i = 0; i < 16; i++)
	{
		BearCore::bear_swap(SamplerStates[i].Shader, Right.SamplerStates[i].Shader);
	}
}
