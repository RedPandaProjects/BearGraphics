#include "BearGraphics.hpp"

void BearGraphics::BearRenderFrameBufferDescription::Copy(const BearRenderFrameBufferDescription & Right)
{
	for (bsize i = 0; i < 8; i++)
	{
		RenderTargets[i].ClearColor.Copy(Right.RenderTargets[i].ClearColor);
		RenderTargets[i].RenderTargetBuffer.copy(Right.RenderTargets[i].RenderTargetBuffer);
		RenderTargets[i].NeedClear =Right.RenderTargets[i].NeedClear;
	}
}

void BearGraphics::BearRenderFrameBufferDescription::Swap(BearRenderFrameBufferDescription & Right)
{
	for (bsize i = 0; i < 8; i++)
	{
		RenderTargets[i].ClearColor.Swap(Right.RenderTargets[i].ClearColor);
		RenderTargets[i].RenderTargetBuffer.swap(Right.RenderTargets[i].RenderTargetBuffer);
		BearCore::bear_swap(RenderTargets[i].NeedClear, Right.RenderTargets[i].NeedClear);
	}
}
