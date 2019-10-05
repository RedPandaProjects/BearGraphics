#pragma once
namespace BearGraphics
{


	struct BearEventWindows
	{
		BearEventWindows() { BearCore::bear_fill(*this); }
	
		BearWindowEventType Type;
		BearCore::BearInput::Key Key;
		union
		{
			float Change;
			struct
			{
				float x;
				float y;
			} Position;
			struct
			{
				float width;
				float height;
			} Size;
			bchar16 Char;
		};
		
	};

	class BEARGRAPHICS_API BearWindow
	{
		BEAR_CLASS_NO_COPY(BearWindow);

	
		
	public:
		enum TypeWindow
		{
			TW_POPUP = 1,
			TW_ONLY_CLOSED=4,
			TW_WIHTOUT_CLOSED = 2,
			
		};
		BearWindow(bsize width = 0x400,bsize height=0x300,bool fullscreen=false, BearCore::BearFlags<int32> flags=0);
		~BearWindow();
		void Resize(bsize width, bsize height);
		bool Update();
		void  ShowCursor(bool show);
		void SetFullscreen(bool fullscreen);
		BearCore::BearVector2<float> GetMousePosition();
		void SetMousePosition(const BearCore::BearVector2<float>&position);
		bool GetEvent(BearEventWindows&e);
		bool Empty()const;


		inline
#ifdef WINDOWS
			HWND
#elif LINUX
			void*
#endif
		GetWindowHandle() const
		{
			return m_window;
		}

		bool IsFullScreen()const
		{
			return m_fullscreen;
		}
		inline BearCore::BearFVector2 GetSizeFloat()const
		{
			return BearCore::BearVector2<float>(static_cast<float>(m_width), static_cast<float>(m_height));
		}

		inline BearCore::BearVector2<bsize> GetSize()const
		{
			return BearCore::BearVector2<bsize>(m_width, m_height);
		}
#ifndef BEAR_GRAPHICS_EXPORTS
	private:
#endif
#ifdef WINDOWS
		void OnEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
#endif

	private:
		
#ifdef WINDOWS
		DWORD m_Style;
		bool m_MouseShow;
		HWND
#elif LINUX
		void*
#endif
		m_window;


		BearCore::BearVector<BearEventWindows>  m_events;
		BearCore::BearVector<BearEventWindows>::iterator  m_events_item;
		bsize m_width, m_height;
		bool m_fullscreen;
		bool m_mouse_enter;


	};
}