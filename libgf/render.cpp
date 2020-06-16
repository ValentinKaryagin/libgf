#include "render.h"

#include "window.h"
#include "vertex_shader.h"
#include "pixel_shader.h"
#include "render_component.h"
#include "draw_component.h"
#include "draw_instanced_component.h"

const float clear_color[] = { 0.0f, 0.0f, 0.0f, 1.0f };

render::render() {}

render::~render() {}

int render::init(BOOL fullscreen, BOOL vsync)
{
	HWND window = window::get_handle();

	RECT rect{};
	GetWindowRect(window, &rect);

	DXGI_MODE_DESC md{};
	md.Width = (UINT)rect.right;
	md.Height = (UINT)rect.bottom;
	md.RefreshRate.Numerator = 60;
	md.RefreshRate.Denominator = 1;
	md.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	md.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	md.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	DXGI_SWAP_CHAIN_DESC scd{};
	scd.BufferDesc = md;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 1;
	scd.OutputWindow = window;
	scd.Windowed = fullscreen ? FALSE : TRUE;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	//scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;	// todo: why DXGI_SWAP_EFFECT_DISCARD is legacy?
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

#ifdef _DEBUG
	UINT flags = (UINT)D3D11_CREATE_DEVICE_DEBUG;
#else
	UINT flags = 0;
#endif

	if (FAILED(D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		0,
		flags,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&scd,
		&swap_chain,
		&device,
		NULL,
		&device_context)))
	{
		return 1;
	}

	ID3D11Texture2D *bb = NULL;
	if (FAILED(swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void **>(&bb))))
	{
		return 2;
	}

	if (FAILED(device->CreateRenderTargetView(bb, NULL, &rtv)))
	{
		return 3;
	}

	bb->Release();

	device_context->OMSetRenderTargets(1, &rtv, NULL);

	D3D11_TEXTURE2D_DESC dstd{};
	dstd.Width = (UINT)rect.right;
	dstd.Height = (UINT)rect.bottom;
	dstd.MipLevels = 1;
	dstd.ArraySize = 1;
	dstd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dstd.SampleDesc.Count = 1;
	dstd.SampleDesc.Quality = 0;
	dstd.Usage = D3D11_USAGE_DEFAULT;
	dstd.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	dstd.CPUAccessFlags = 0;
	dstd.MiscFlags = 0;

	if (FAILED(device->CreateTexture2D(&dstd, NULL, &ds_buffer)))
	{
		return 4;
	}

	if (FAILED(device->CreateDepthStencilView(ds_buffer, NULL, &dsv)))
	{
		return 5;
	}

	device_context->OMSetRenderTargets(1, &rtv, dsv);

	D3D11_VIEWPORT vp{};
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = (FLOAT)rect.right;
	vp.Height = (FLOAT)rect.bottom;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	device_context->RSSetViewports(1, &vp);

	device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	is_vsync = vsync;

	D3D11_RASTERIZER_DESC slrs{};
	slrs.FillMode = D3D11_FILL_SOLID;
	slrs.CullMode = D3D11_CULL_BACK;
	slrs.MultisampleEnable = FALSE;
	slrs.AntialiasedLineEnable = FALSE;
	slrs.DepthClipEnable = TRUE;
	if (FAILED(device->CreateRasterizerState(&slrs, &solid_rs)))
	{
		return 6;
	}

	D3D11_RASTERIZER_DESC wfrs{};
	wfrs.FillMode = D3D11_FILL_WIREFRAME;
	wfrs.CullMode = D3D11_CULL_NONE;
	wfrs.MultisampleEnable = FALSE;
	wfrs.AntialiasedLineEnable = FALSE;
	wfrs.DepthClipEnable = TRUE;
	if (FAILED(device->CreateRasterizerState(&wfrs, &wireframe_rs)))
	{
		return 7;
	}

	device_context->RSSetState(solid_rs);

	CD3D11_DEFAULT sampler_default;
	CD3D11_SAMPLER_DESC sampler_desc = CD3D11_SAMPLER_DESC(sampler_default);
	D3D11_SAMPLER_DESC sd = sampler_desc;
	if (FAILED(device->CreateSamplerState(&sd, &sampler_state)))
	{
		return 8;
	}

	device_context->PSSetSamplers(0, 1, &sampler_state);

	/*sprite_batch = new(std::nothrow) DirectX::SpriteBatch(device_context);
	if (!sprite_batch)
	{
		return 9;
	}*/

	return 0;
}

void render::terminate()
{
	D3D_SAFE_RELEASE(sampler_state);
	D3D_SAFE_RELEASE(wireframe_rs);
	D3D_SAFE_RELEASE(solid_rs);
	D3D_SAFE_RELEASE(dsv);
	D3D_SAFE_RELEASE(ds_buffer);
	D3D_SAFE_RELEASE(layout);
	D3D_SAFE_RELEASE(rtv);
	D3D_SAFE_RELEASE(swap_chain);
	D3D_SAFE_RELEASE(device_context);
	D3D_SAFE_RELEASE(device);
}

int render::create_shader(vertex_shader *ptr)
{
	int err_lvl = 0;

	if (FAILED(device->CreateVertexShader(ptr->buffer->GetBufferPointer(), ptr->buffer->GetBufferSize(), NULL, &ptr->handle)))
	{
		err_lvl = 1;
	}

	return err_lvl;
}

int render::create_shader(pixel_shader *ptr)
{
	int err_lvl = 0;

	if (FAILED(device->CreatePixelShader(ptr->buffer->GetBufferPointer(), ptr->buffer->GetBufferSize(), NULL, &ptr->handle)))
	{
		err_lvl = 1;
	}

	return err_lvl;
}

void render::set_vertex_shader(vertex_shader *ptr)
{
	device_context->VSSetShader(ptr->handle, NULL, 0);

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	D3D_SAFE_RELEASE(layout);

	if (FAILED(device->CreateInputLayout(ied, sizeof(ied) / sizeof(D3D11_INPUT_ELEMENT_DESC), ptr->buffer->GetBufferPointer(), ptr->buffer->GetBufferSize(), &layout)))
	{
		// err
	}

	device_context->IASetInputLayout(layout);
}

void render::set_pixel_shader(pixel_shader *ptr)
{
	device_context->PSSetShader(ptr->handle, NULL, 0);
}

void render::insert_component(render_component *ptr)
{

}

void render::remove_component(render_component *ptr)
{

}

int render::draw()
{
	int err_lvl = 0;

	device_context->ClearRenderTargetView(rtv, clear_color);
	device_context->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//device_context->Draw(0, 0);

	if (FAILED(swap_chain->Present(is_vsync ? 1 : 0, 0)))
	{
		err_lvl = 1;
	}

	return err_lvl;
}
