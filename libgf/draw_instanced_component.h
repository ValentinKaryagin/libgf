#pragma once

#include "render_component.h"

#include <vector>

class draw_instanced_component
	: public render_component
{
public:
	std::vector<DirectX::XMMATRIX> transforms;

public:
	draw_instanced_component(const TCHAR *name = TEXT("draw_instanced_component"));
	virtual ~draw_instanced_component();

public:

};
