#pragma once 
namespace BearRenderBase
{
	class BEARGRAPHICS_API BearRenderTargetViewBase:public BearRenderShaderResourceBase
	{
		BEAR_CLASS_NO_COPY(BearRenderTargetViewBase)
	public:
		BearRenderTargetViewBase() {}
		virtual ~BearRenderTargetViewBase() = 0;
		virtual void Resize(bsize Width, bsize Height) = 0;
		virtual void*GetHandle()=0;
	};
}