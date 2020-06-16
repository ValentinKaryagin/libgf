#pragma once

#include "commons.h"

class window
{
public:
	HINSTANCE	instance	= GetModuleHandle(NULL);
	HWND		handle		= 0;
	ATOM		atom		= 0;

protected:
	window();

public:
	virtual ~window();

public:
	int create(LONG left, LONG top, LONG size_x, LONG size_y, const TCHAR *title, BOOL show, BOOL foreground);
	int destroy();

public:
	int proc();

public:
	__forceinline static window *get()
	{
		static window window_instance;
		return &window_instance;
	}
};
