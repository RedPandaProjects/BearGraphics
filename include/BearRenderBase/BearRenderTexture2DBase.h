#pragma once 
namespace BearRenderBase
{
	class BEARGRAPHICS_API BearRenderTexture2DBase :public BearRenderShaderResourceBase
	{
		BEAR_CLASS_NO_COPY(BearRenderTexture2DBase)
	public:
		BearRenderTexture2DBase() {}
		virtual void Create(bsize width, bsize height, bsize mips, bsize depth, BearGraphics::BearTexturePixelFormat format, void*data, bool dynamic = false) = 0;
		virtual void* Lock(bsize mip=0, bsize depth=0)  =0;
		virtual void  Unlock() = 0;
		virtual void  Clear() = 0;
		virtual ~BearRenderTexture2DBase() = 0;
		virtual void*GetHandle() = 0;
	};
}