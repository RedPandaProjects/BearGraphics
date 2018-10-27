#pragma once 
namespace BearRHI
{
	class BEARGRAPHICS_API BearRHIViewPort:public BearRHIRenderTargetView
	{
	public:
		virtual void swap()=0;
		virtual void setFullScreen(bool fullscreen) = 0;
		virtual void setVsync(bool vsync)=0;
		virtual void generateMips() override;
	};
};