#include "window.h"

LRESULT __stdcall wnd_proc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam);

window::window() {}

window::~window()
{
	destroy();
}

int window::create(LONG left, LONG top, LONG size_x, LONG size_y, const TCHAR *title, BOOL show, BOOL foreground)
{
	if (!instance)
	{
		return 1;
	}

	WNDCLASSEX wcex{};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = wnd_proc;
	wcex.hIcon = LoadIcon(instance, IDI_WINLOGO);
	wcex.hIconSm = LoadIcon(instance, IDI_WINLOGO);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hInstance = instance;
	wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wcex.lpszClassName = TEXT("wndclass");

	atom = RegisterClassEx(&wcex);
	if (!atom)
	{
		return 2;
	}

	RECT rect{};
	rect.left = left;
	rect.top = top;
	rect.right = rect.left + size_x;
	rect.bottom = rect.top + size_y;

	handle = CreateWindowEx(
		0,
		(TCHAR *)((SIZE_T)(atom)),
		title,
		WS_VISIBLE | WS_POPUP,
		rect.left,
		rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		instance,
		NULL);

	if (!handle)
	{
		return 3;
	}

	if (!ShowWindow(handle, show ? SW_SHOW : SW_HIDE))
	{
		return 4;
	}

	if (!UpdateWindow(handle))
	{
		return 5;
	}

	if (foreground)
	{
		if (!SetForegroundWindow(handle))
		{
			return 6;
		}
	}
	
	return 0;
}

int window::destroy()
{
	int err_lvl = 0;

	if (!DestroyWindow(handle))
	{
		return 1;
	}
	handle = 0;

	if (!UnregisterClass((TCHAR *)((SIZE_T)(atom)), instance))
	{
		return 2;
	}
	atom = 0;

	return 0;
}

int window::proc()
{
	MSG msg{};
	while (PeekMessage(&msg, handle, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			
		}
		else
		{
			if (!TranslateMessage(&msg))
			{
				
			}

			if (FAILED(DispatchMessage(&msg)))
			{
				return 1;
			}
		}
	}

	return 0;
}

LRESULT __stdcall wnd_proc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);		
		break;
	case WM_SIZE:		
		break;
	default:
		break;
	}

	return DefWindowProc(wnd, msg, wparam, lparam);
}
