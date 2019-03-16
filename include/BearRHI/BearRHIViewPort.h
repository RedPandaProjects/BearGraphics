#pragma once 
namespace BearRHI
{
	class BEARGRAPHICS_API BearRHIViewport:public BearRHIRenderTargetView,public BearRHIDepthStencilView
	{
	public:
		virtual void Swap()=0;
		virtual void SetFullScreen(bool fullscreen) = 0;
		virtual void SetVsync(bool vsync)=0;
		virtual void GenerateMips() override;
		virtual void Resize(bsize w, bsize h) = 0;
	};
};