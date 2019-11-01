#include "BearGraphics.hpp"

void BearGraphics::BearRenderDescriptorHeapDescription::Copy(const BearRenderDescriptorHeapDescription & Right)
{
	for (bsize i = 0; i < 16; i++)
	{
		UniformBuffers[i].Buffer.copy(Right.UniformBuffers[i].Buffer);\
	}
}

void BearGraphics::BearRenderDescriptorHeapDescription::Swap(BearRenderDescriptorHeapDescription & Right)
{
	for (bsize i = 0; i < 16; i++)
	{
		UniformBuffers[i].Buffer.swap(Right.UniformBuffers[i].Buffer);
	}
}
