#pragma once 

namespace BearGraphics
{
	class BEARGRAPHICS_API BearViewport
	{
		BEAR_CLASS_NO_COPY(BearViewport);
	public:
		friend class BearRenderInterface;
		virtual void Resize(bsize width, bsize height);
		virtual void SetFullScreen(bool fullscreen);
		virtual void SetVsync(bool vsync);
		void Swap();
		void ClearColor(const BearCore::BearColor&color);
		virtual bool Empty()const;
	protected:
		void Create(void* win, bsize width, bsize height, bool fullscreen, bool vsync);
		BearViewport();
		~BearViewport();
	private:
		BearRHI::BearRHIViewport*viewport;

	};
}