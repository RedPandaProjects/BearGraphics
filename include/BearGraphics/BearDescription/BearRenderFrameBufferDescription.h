#pragma once 
namespace BearGraphics
{

	
	class BEARGRAPHICS_API BearRenderFrameBufferDescription
	{
	public:
		BearRenderFrameBufferDescription() {}
		BearRenderFrameBufferDescription(const BearRenderFrameBufferDescription&Right) { Copy(Right); }
		BearRenderFrameBufferDescription(BearRenderFrameBufferDescription&&Right) { Swap(Right); }
		inline ~BearRenderFrameBufferDescription() {}
		void Copy(const BearRenderFrameBufferDescription&Right);
		void Swap(BearRenderFrameBufferDescription&Right);
		inline BearRenderFrameBufferDescription&operator=(const BearRenderFrameBufferDescription&Right) { Copy(Right); return*this; }
		inline BearRenderFrameBufferDescription&operator=(BearRenderFrameBufferDescription&&Right) { Swap(Right); return*this; }

		struct RenderTarget
		{
			RenderTarget() :NeedClear(false) {}
			BearCore::BearColor ClearColor;
			bool NeedClear;
			BearFactoryPointer<BearRenderBase::BearRenderTargetViewBase> RenderTargetBuffer;

		} RenderTargets[8];
	};
}
