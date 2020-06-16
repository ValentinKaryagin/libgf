#pragma once

#include "commons.h"

class config
{
public:
	const TCHAR *path = NULL;

public:
	struct window
	{
		LONG	left;
		LONG	top;
		LONG	size_x;
		LONG	size_y;
		TCHAR	title[MAX_PATH];
		BOOL	show;
		BOOL	foreground;
	} window{};

public:
	struct render
	{
		BOOL fullscreen;
		BOOL vsync;
	} render{};

public:
	config(const TCHAR *path = TEXT(".\\config.ini"));
	virtual ~config();

public:
	int read();
};
