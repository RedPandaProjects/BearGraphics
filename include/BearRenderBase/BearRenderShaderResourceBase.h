#pragma once 
namespace BearRenderBase
{
	class BEARGRAPHICS_API BearRenderShaderResourceBase :public BearRenderObject
	{
		BEAR_CLASS_NO_COPY(BearRenderShaderResourceBase)
	public:
		BearRenderShaderResourceBase() {}
		virtual ~BearRenderShaderResourceBase() = 0;
		virtual void*GetHandle() = 0;
	};
}