#pragma once
namespace BearRenderBase
{
	class BEARGRAPHICS_API BearRenderContextBase
	{
		BEAR_CLASS_NO_COPY(BearRenderContextBase);
	public:
		BearRenderContextBase() {}
		virtual void ClearColor(BearGraphics::BearFactoryPointer<BearRenderTargetViewBase> RenderTarget, const BearCore::BearColor Color) = 0;
		virtual void Flush() = 0;
		virtual void AttachViewport(BearGraphics::BearFactoryPointer<BearRenderViewportBase> Viewport) = 0;
		virtual void DetachViewport() = 0;
		virtual ~BearRenderContextBase() = 0;
	};
}