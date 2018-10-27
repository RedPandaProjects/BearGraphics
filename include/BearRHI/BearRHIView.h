#pragma once 
namespace BearRHI
{
	class BearRHIRenderTargetView
	{
	public:
		virtual void reisze(bsize w,bsize h)=0;
		virtual void clearColor(const BearCore::BearColor&color)=0;
		virtual bptr getRenderTarget()=0;
		virtual void generateMips() = 0;
	};
	class BearRHIDepthStencilView
	{
	public:
		virtual void resize(bsize w, bsize h) = 0;
		virtual void clearDepth(float depth) = 0;
		virtual void clearStencil(uint8 mask )=0;
		virtual void  generateMips() = 0;
 	};
}