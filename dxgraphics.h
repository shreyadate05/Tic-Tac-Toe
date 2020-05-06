#ifndef _DXGRAPHICS_H
#define _DXGRAPHICS_H
#define KEY_DOWN(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

#include <d3d9.h>
#include <d3dx9.h>

extern LPDIRECT3D9 d3d;
extern LPDIRECT3DDEVICE9 d3ddev;
extern LPDIRECT3DSURFACE9 backbuffer;

int initD3D(HWND hWnd, int WIDTH, int HEIGHT, int);
LPDIRECT3DSURFACE9 LoadSurface(char* filename, D3DCOLOR);

#endif