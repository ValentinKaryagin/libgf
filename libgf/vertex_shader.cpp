#include "vertex_shader.h"

vertex_shader::vertex_shader(const TCHAR *path, const char *entry)
	: shader(path, entry)
{}

vertex_shader::~vertex_shader()
{
	destroy();
}

void vertex_shader::destroy()
{
	D3D_SAFE_RELEASE(handle);
}
