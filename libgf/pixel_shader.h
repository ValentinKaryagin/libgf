#pragma once

#include "shader.h"

class pixel_shader
	: public shader
{
public:
	ID3D11PixelShader *handle = NULL;

public:
	pixel_shader(const TCHAR *path, const char *entry = "main");
	virtual ~pixel_shader();

public:
	void destroy();
};
