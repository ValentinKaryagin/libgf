#include "pixel_shader.h"

pixel_shader::pixel_shader(const TCHAR *path, const char *entry)
	: shader(path, entry)
{}

pixel_shader::~pixel_shader()
{
	destroy();
}

void pixel_shader::destroy()
{
	D3D_SAFE_RELEASE(handle);
}
