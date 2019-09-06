#pragma once
namespace BearRenderBase
{
	class BearRenderContextBase
	{
		BEAR_CLASS_NO_COPY(BearRenderContextBase);
	public:
		BearRenderContextBase() {}
		virtual void ClearColor(BearGraphics::BearFactoryPointer<BearRenderTargetViewBase> RenderTarget, const BearCore::BearColor Color) = 0;
		virtual void Flush(bool wait) = 0;
		virtual void Wait() = 0;
		virtual void AttachViewport(BearGraphics::BearFactoryPointer<BearRenderViewportBase> Viewport) = 0;
		virtual void DetachViewport() = 0;
	};
}