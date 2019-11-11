#include "BearGraphics.hpp"

void BearGraphics::BearRenderDescriptorHeapDescription::Copy(const BearRenderDescriptorHeapDescription & Right)
{
	for (bsize i = 0; i < 16; i++)
	{
		UniformBuffers[i].Buffer.copy(Right.UniformBuffers[i].Buffer);
	}

	for (bsize i = 0; i < 16; i++)
	{
		SRVResources[i].SRVResource.copy(Right.SRVResources[i].SRVResource);
	}
	for (bsize i = 0; i < 16; i++)
	{
		Samplers[i].Sampler.copy(Right.Samplers[i].Sampler);
	}
	CS = Right.CS;
}

void BearGraphics::BearRenderDescriptorHeapDescription::Swap(BearRenderDescriptorHeapDescription & Right)
{
	for (bsize i = 0; i < 16; i++)
	{
		UniformBuffers[i].Buffer.swap(Right.UniformBuffers[i].Buffer);
	}
	for (bsize i = 0; i < 16; i++)
	{
		SRVResources[i].SRVResource.copy(Right.SRVResources[i].SRVResource);
	}
	for (bsize i = 0; i < 16; i++)
	{
		Samplers[i].Sampler.copy(Right.Samplers[i].Sampler);
	}
}
