#pragma once

#include "commons.h"

class object
{
public:
	GUID	guid{};
	TCHAR	name[MAX_PATH]{};

public:
	object(const TCHAR *name = TEXT("object"));
	virtual ~object();

public:

};
