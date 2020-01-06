#include "BearGraphics.hpp"

void BearDescriptorHeapDescription::Copy(const BearDescriptorHeapDescription& Right)
{
	for (bsize i = 0; i < 16; i++)
	{
		UniformBuffers[i] = Right.UniformBuffers[i];
	}
}

void BearDescriptorHeapDescription::Swap(BearDescriptorHeapDescription& Right)
{
	for (bsize i = 0; i < 16; i++)
	{
		UniformBuffers[i].swap( Right.UniformBuffers[i]);
	}
}
