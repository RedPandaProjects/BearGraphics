#pragma once
namespace BearRenderBase
{
	class BEARGRAPHICS_API BearRenderSamplerStateBase :public BearRenderObject
	{
		BEAR_CLASS_NO_COPY(BearRenderSamplerStateBase)
	public:
		BearRenderSamplerStateBase() {}
		virtual ~BearRenderSamplerStateBase() = 0;
	};
}