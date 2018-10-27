#pragma once 
namespace BearRHI
{
	class BearRHITexture2D:public BearRHITextureUtils
	{
	public:
		virtual void* lock(bsize mipId)=0;
		virtual void unlock() = 0;
		virtual void generateMipmap() = 0;
	};
}