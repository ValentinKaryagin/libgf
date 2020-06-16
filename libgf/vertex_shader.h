#pragma once

#include "shader.h"

class vertex_shader
	: public shader
{
public:
	ID3D11VertexShader *handle = NULL;

public:
	vertex_shader(const TCHAR *path, const char *entry = "main");
	virtual ~vertex_shader();

public:
	void destroy();
};
