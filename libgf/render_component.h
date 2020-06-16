#pragma once

#include "component.h"

class render_component
	: public component
{
public:
	DirectX::XMFLOAT4X4	*root		= NULL;
	DirectX::XMFLOAT4X4	transform;

public:
	render_component(const TCHAR *name = TEXT("render_component"));
	virtual ~render_component();

public:

};
