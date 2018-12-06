#pragma once 
namespace BearRHI
{
	class BearRHITexture2D:public BearRHITextureUtils
	{
	public:
		virtual void*Lock(bsize mipId)=0;
		virtual void Unlock() = 0;
		virtual void GenerateMipmap() = 0;
	};
}