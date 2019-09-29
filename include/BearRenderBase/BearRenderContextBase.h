#pragma once
namespace BearRenderBase
{
	class BEARGRAPHICS_API BearRenderContextBase
	{
		BEAR_CLASS_NO_COPY(BearRenderContextBase);
	public:
		BearRenderContextBase() {}
		virtual void Flush() = 0;
		virtual void AttachViewportAsFrameBuffer(BearGraphics::BearFactoryPointer<BearRenderViewportBase> Viewport) = 0;
		virtual void DetachFrameBuffer() = 0;
		virtual void ClearFrameBuffer() = 0;
		virtual ~BearRenderContextBase() = 0;
	};
}