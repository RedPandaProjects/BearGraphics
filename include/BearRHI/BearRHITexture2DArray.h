#pragma once 
namespace BearRHI
{
	class BearRHITexture2DArray:public BearRHITextureUtils
	{
	public:
		virtual void*Lock(bsize depth,bsize mipId)=0;
		virtual void Unlock() = 0;
		virtual void GenerateMipmap() = 0;
	};
}