#pragma once

#include "component.h"

class physics_component
	: public component
{
public:
	btDefaultMotionState bt_motion_state;

public:
	physics_component(const TCHAR *name = TEXT("physics_component"));
	virtual ~physics_component();

public:

};
