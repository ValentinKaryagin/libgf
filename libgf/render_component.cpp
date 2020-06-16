#include "render_component.h"

render_component::render_component(const TCHAR *name)
	: component(name)
{
	DirectX::XMStoreFloat4x4(&transform, DirectX::XMMatrixIdentity());
}

render_component::~render_component() {}
