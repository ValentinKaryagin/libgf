#pragma once

#include "object.h"

class component
	: public object
{
public:
	component(const TCHAR *name = TEXT("component"));
	virtual ~component();

public:

};
