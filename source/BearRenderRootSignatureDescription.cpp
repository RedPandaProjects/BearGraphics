#include "BearGraphics.hpp"

BearGraphics::BearRenderRootSignatureDescription::BearRenderRootSignatureDescription()
{
}

BearGraphics::BearRenderRootSignatureDescription::BearRenderRootSignatureDescription(const BearRenderRootSignatureDescription & Right)
{
}

BearGraphics::BearRenderRootSignatureDescription::BearRenderRootSignatureDescription(BearRenderRootSignatureDescription && Right)
{
}

void BearGraphics::BearRenderRootSignatureDescription::Copy(const BearRenderRootSignatureDescription & Right)
{
	for (bsize i = 0; i < 16; i++)
	{
		UniformBuffers[i].Buffer.copy(Right.UniformBuffers[i].Buffer);
		UniformBuffers[i].Shader = Right.UniformBuffers[i].Shader;
	}
}

void BearGraphics::BearRenderRootSignatureDescription::Swap(BearRenderRootSignatureDescription & Right)
{
	for (bsize i = 0; i < 16; i++)
	{
		UniformBuffers[i].Buffer.swap(Right.UniformBuffers[i].Buffer);
		BearCore::bear_swap(UniformBuffers[i].Shader, Right.UniformBuffers[i].Shader);
	}
}
