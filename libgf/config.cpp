#include "config.h"

const TCHAR window_section[]	= TEXT("window");
const TCHAR render_section[]	= TEXT("render");

config::config(const TCHAR *path)
	: path(path)
{}

config::~config() {}

int config::read()
{
	int err_lvl = 0;

	window.left			= GetPrivateProfileIntW(window_section, TEXT("left"), 128, path);
	window.top			= GetPrivateProfileIntW(window_section, TEXT("top"), 128, path);
	window.size_x		= GetPrivateProfileIntW(window_section, TEXT("size_x"), 1280, path);
	window.size_y		= GetPrivateProfileIntW(window_section, TEXT("size_y"), 720, path);
	GetPrivateProfileStringW(window_section, TEXT("title"), TEXT("libgf"), window.title, MAX_PATH, path);
	window.show			= (BOOL)GetPrivateProfileIntW(window_section, TEXT("show"), 1, path);
	window.foreground	= (BOOL)GetPrivateProfileIntW(window_section, TEXT("foreground"), 1, path);

	render.fullscreen	= (BOOL)GetPrivateProfileIntW(render_section, TEXT("fullscreen"), 0, path);
	render.vsync		= (BOOL)GetPrivateProfileIntW(render_section, TEXT("vsync"), 1, path);

	return err_lvl;
}
