#pragma once 
namespace BearRHI
{
	class BearRHIRenderTargetView
	{
	public:
		virtual void Reisze(bsize w,bsize h)=0;
		virtual void ClearColor(const BearCore::BearColor&color)=0;
		virtual bptr GetRenderTarget()=0;
		virtual void GenerateMips() = 0;
	};
	class BearRHIDepthStencilView
	{
	public:
		virtual void Resize(bsize w, bsize h) = 0;
		virtual void ClearDepth(float depth) = 0;
		virtual void ClearStencil(uint8 mask )=0;
 	};
}