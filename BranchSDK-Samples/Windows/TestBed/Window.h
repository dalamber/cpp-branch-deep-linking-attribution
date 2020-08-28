#pragma once

#include <Windows.h>

#include <string>

#include "ScopeLock.h"

class Window
{
public:
	Window(DWORD exStyle, LPCWSTR className, LPCWSTR windowName, DWORD style, int x, int y, int width, int height, HWND parent = nullptr);
	~Window();

	// Thread-safe getter
	HWND getWindowHandle() const { 
		ScopeLock l(m_lock);
		return m_self;
	}

	// Can use a Window anywhere you can use a HWND.
	operator HWND() const { return getWindowHandle(); }

	// assumes parent set in constructor
	HWND create();

	// overrides constructor. adds to specified parent
	HWND create(HWND parent);

	void destroy();

private:
	// prevent copying and assignment
	Window& operator=(const Window&) { return *this; }
	Window(const Window&) : m_exStyle(0), m_style(0), m_x(0), m_y(0), m_width(0), m_height(0), m_parent(nullptr), m_self(nullptr)
	{
		// Just to silence a warning
		InitializeCriticalSection(&m_lock);
	}

	DWORD m_exStyle;
	std::wstring m_className;
	std::wstring m_windowName;
	DWORD m_style;
	int m_x, m_y, m_width, m_height;
	HWND m_parent;
	HWND volatile m_self;
	CRITICAL_SECTION mutable m_lock;
};
