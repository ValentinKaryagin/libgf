#pragma once

#include "commons.h"
#include "vertex.h"

class static_mesh
{
public:
	const TCHAR		*path			= NULL;
	vertex			*vertices		= NULL;
	unsigned int	vertices_count	= 0;
	unsigned int	*indices		= NULL;
	unsigned int	indices_count	= 0;

public:
	static_mesh(const TCHAR *path);
	virtual ~static_mesh();

public:
	int load();
	void release();
};
