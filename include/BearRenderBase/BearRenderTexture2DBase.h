#pragma once 
namespace BearRenderBase
{
	class BEARGRAPHICS_API BearRenderTexture2DBase :public BearRenderObject
	{
		BEAR_CLASS_NO_COPY(BearRenderTexture2DBase)
	public:
		BearRenderTexture2DBase() {}
		virtual ~BearRenderTexture2DBase() = 0;
	};
}