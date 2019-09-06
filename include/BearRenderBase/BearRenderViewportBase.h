#pragma once
namespace BearRenderBase
{
	class BearRenderViewportBase:public BearRenderTargetViewBase
	{
		BEAR_CLASS_NO_COPY(BearRenderViewportBase);
	public:
		BearRenderViewportBase() {}
		virtual void SetVSync(bool Sync) = 0;
		virtual void SetFullScreen(bool FullScreen) = 0;
	};
}