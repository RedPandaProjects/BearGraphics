#pragma once 
namespace BearRenderBase
{
	class BearRenderTargetViewBase:public BearRenderTexture2DBase
	{
		BEAR_CLASS_NO_COPY(BearRenderTargetViewBase)
	public:
		BearRenderTargetViewBase() {}
		virtual void Resize(bsize Width, bsize Height) = 0;
		virtual void*GetHandle()=0;
	};
}