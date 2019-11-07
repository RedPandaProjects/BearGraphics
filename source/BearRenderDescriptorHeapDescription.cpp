#include "BearGraphics.hpp"

void BearGraphics::BearRenderDescriptorHeapDescription::Copy(const BearRenderDescriptorHeapDescription & Right)
{
	for (bsize i = 0; i < 16; i++)
	{
		UniformBuffers[i].Buffer.copy(Right.UniformBuffers[i].Buffer);
	}

	for (bsize i = 0; i < 16; i++)
	{
		Textures[i].Texture.copy(Right.Textures[i].Texture);
	}
	for (bsize i = 0; i < 16; i++)
	{
		Samplers[i].Sampler.copy(Right.Samplers[i].Sampler);
	}
}

void BearGraphics::BearRenderDescriptorHeapDescription::Swap(BearRenderDescriptorHeapDescription & Right)
{
	for (bsize i = 0; i < 16; i++)
	{
		UniformBuffers[i].Buffer.swap(Right.UniformBuffers[i].Buffer);
	}
	for (bsize i = 0; i < 16; i++)
	{
		Textures[i].Texture.copy(Right.Textures[i].Texture);
	}
	for (bsize i = 0; i < 16; i++)
	{
		Samplers[i].Sampler.copy(Right.Samplers[i].Sampler);
	}
}
