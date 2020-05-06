#include <d3d9.h>
#include <d3dx9.h>
#include "dxgraphics.h"

LPDIRECT3D9 d3d = NULL;
LPDIRECT3DDEVICE9 d3ddev = NULL;
LPDIRECT3DSURFACE9 backbuffer = NULL;

int initD3D(HWND hWnd, int WIDTH, int HEIGHT, int fullScreen) {
	d3d = Direct3DCreate9(D3D_SDK_VERSION);   // create the Direct3D interface
	if (d3d == NULL) {
		MessageBox(hWnd, "Error in Initializing Direct3D", "Error", MB_OK);
	}
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = (!fullScreen);
	d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = WIDTH;
	d3dpp.BackBufferHeight = HEIGHT;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	if (d3ddev == NULL) {
		MessageBox(hWnd, "Error in Creating Device Window", "Error", MB_OK);
	}
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255,255,255), 1.0f, 0);
	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
	return 1;
}

LPDIRECT3DSURFACE9 LoadSurface(char* filename, D3DCOLOR transcolor) {
	LPDIRECT3DSURFACE9 image = NULL;
	D3DXIMAGE_INFO info;
	HRESULT result;
	result = D3DXGetImageInfoFromFile(filename, &info);
	if (result != D3D_OK)
		return NULL;
	result = d3ddev->CreateOffscreenPlainSurface(
		info.Width,
		info.Height,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&image,
		NULL);
	if (result != D3D_OK)
		return NULL;
	result = D3DXLoadSurfaceFromFile(
		image,
		NULL,
		NULL,
		filename,
		NULL,
		D3DX_DEFAULT,
		transcolor,
		NULL);
	if (result != D3D_OK)
		return NULL;
	return image;
}
