#pragma once

#include "render_component.h"

class draw_component
	: public render_component
{
public:
	draw_component(const TCHAR *name = TEXT("draw_component"));
	virtual ~draw_component();

public:

};
