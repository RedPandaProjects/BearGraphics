#pragma once 

namespace BearGraphics
{
	class BEARGRAPHICS_API BearViewPortRef
	{
	public:
		friend class BearRenderInterface;
		BearViewPortRef();
		~BearViewPortRef();
		void create(BearCore::BearWindow&window,bool vsync);
		void create(bptr win, bsize wigth, bsize height, bool fullscreen, bool vsync);
		void close();
		void resize(bsize wigth, bsize height);
		void setFullScreen(bool fullscreen);
		void setVsync(bool vsync);
		void swap();
		void clearColor(const BearCore::BearColor&color);

		bool empty()const;
		void copy(const BearViewPortRef&viewport);
		void swap(BearViewPortRef&viewport);
		BearViewPortRef(const BearViewPortRef&viewport);
		BearViewPortRef&operator=(const BearViewPortRef&viewport);
	private:
		struct data
		{
			data();
			~data();
			BearRHI::BearRHIViewPort*viewport;
		};
		BearCore::BearMemoryMultiRef<data> m_data;

	};
}