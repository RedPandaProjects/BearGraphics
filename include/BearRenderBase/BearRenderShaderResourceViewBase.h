#pragma once 
namespace BearRenderBase
{
	class BEARGRAPHICS_API BearRenderShaderResourceViewBase :public BearRenderObject
	{
		BEAR_CLASS_NO_COPY(BearRenderShaderResourceViewBase)
	public:
		BearRenderShaderResourceViewBase() {}
		virtual ~BearRenderShaderResourceViewBase() = 0;
		virtual void SetResource(void*) = 0;
	};
}