#pragma once

#include "commons.h"

class shader
{
public:
	const TCHAR	*path	= NULL;
	const char	*entry	= NULL;

public:
	ID3DBlob *buffer = NULL;

public:
	shader(const TCHAR *path, const char *entry = "main");
	virtual ~shader();

public:
	int load();
	void release();
};
