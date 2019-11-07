#pragma once 
namespace BearRenderBase
{
	class BEARGRAPHICS_API BearRenderUnorderedAccessViewBase :public BearRenderShaderResourceViewBase
	{
		BEAR_CLASS_NO_COPY(BearRenderUnorderedAccessViewBase)
	public:
		BearRenderUnorderedAccessViewBase() {}
		virtual ~BearRenderUnorderedAccessViewBase() = 0;
		virtual void SetUnorderedAccess(void*) = 0;
	};
}