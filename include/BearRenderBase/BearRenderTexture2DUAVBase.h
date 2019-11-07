#pragma once 

namespace BearRenderBase
{
	class BEARGRAPHICS_API BearRenderTexture2DUAVBase :public BearRenderUnorderedAccessViewBase
	{
		BEAR_CLASS_NO_COPY(BearRenderTexture2DUAVBase)
	public:
		BearRenderTexture2DUAVBase() {}
		virtual void Create(bsize width, bsize height, bsize depth, BearGraphics::BearTextureUAVPixelFormat format) = 0;
		virtual void  Clear() = 0;
		virtual ~BearRenderTexture2DUAVBase() = 0;

	};
}