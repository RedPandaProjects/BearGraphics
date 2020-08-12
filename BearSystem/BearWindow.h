#pragma once

struct BearEventWindows
{
	BearEventWindows() { Type = BearWindowEventType::None; }

	BearWindowEventType Type;
	BearInput::Key Key;
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
	BEAR_CLASS_WITHOUT_COPY(BearWindow);
public:
	BearWindow(bsize width = 0x400, bsize height = 0x300, bool fullscreen = false, BearFlags<int32> flags = 0);
	~BearWindow();
	void Resize(bsize width, bsize height);
	bool Update();
	void  ShowCursor(bool show);
	void SetFullscreen(bool fullscreen);
	BearVector2<float> GetMousePosition();
	void SetMousePosition(const BearVector2<float>& position);
	bool GetEvent(BearEventWindows& e);
	bool Empty()const;


	inline
#ifdef WINDOWS
		HWND
#elif LINUX
		void*
#endif
		GetWindowHandle() const
	{
		return m_WindowHandle;
	}

	inline bool IsFullScreen()const
	{
		return m_Fullscreen;
	}
	inline BearFVector2 GetSizeFloat()const
	{
		return BearVector2<float>(static_cast<float>(m_Width), static_cast<float>(m_Height));
	}

	inline BearVector2<bsize> GetSize()const
	{
		return BearVector2<bsize>(m_Width, m_Height);
	}
#ifndef BEARGRAPHICS_EXPORTS
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
	m_WindowHandle;
	BearVector<BearEventWindows>  m_Events;
	BearVector<BearEventWindows>::iterator  m_EventPtr;
	bsize m_Width, m_Height;
	bool m_Fullscreen;
	bool m_MouseEnter;
};