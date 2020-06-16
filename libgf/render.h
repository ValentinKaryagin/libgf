#pragma once

#include "commons.h"

class vertex_shader;
class pixel_shader;
class render_component;

class render
{
public:
	ID3D11Device			*device			= NULL;
	ID3D11DeviceContext		*device_context	= NULL;
	IDXGISwapChain			*swap_chain		= NULL;
	ID3D11RenderTargetView	*rtv			= NULL;
	ID3D11DepthStencilView	*dsv			= NULL;
	ID3D11Texture2D			*ds_buffer		= NULL;
	ID3D11InputLayout		*layout			= NULL;
	ID3D11RasterizerState	*solid_rs		= NULL;
	ID3D11RasterizerState	*wireframe_rs	= NULL;
	ID3D11SamplerState		*sampler_state	= NULL;
	BOOL					is_vsync		= FALSE;

protected:
	render();

public:
	virtual ~render();

public:
	int init(BOOL fullscreen, BOOL vsync);
	void terminate();
	int create_shader(vertex_shader *ptr);
	int create_shader(pixel_shader *ptr);
	void set_vertex_shader(vertex_shader *ptr);
	void set_pixel_shader(pixel_shader *ptr);
	void insert_component(render_component *ptr);
	void remove_component(render_component *ptr);
	int draw();

public:
	__forceinline static render *get()
	{
		static render render_instance;
		return &render_instance;
	}
};
