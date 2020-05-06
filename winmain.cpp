//  Copyright Shreya Date 2016

#include <Windows.h>
#include <WindowsX.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include <stdio.h>
#include "game.h"
#include "dxgraphics.h"
#pragma comment(lib, "d3d9.lib")

HWND hWnd = NULL;
int endGame = 0;
int pos = 0;

LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		int x, y;
		RECT r;
		int pos = FindGrid(x,y);
		switch (msg) {
		case WM_CLOSE:
			if (MessageBox(hWnd, "Really Quit?", "My application", MB_OKCANCEL) == IDOK)
				DestroyWindow(hWnd);
			PostQuitMessage(0);
			return 0;
			break;
	
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
			break;
	
		case WM_CHAR:
			switch (wParam) {
			case VK_ESCAPE:
				PostQuitMessage(0);
				return 0;
				break;
			}
		case WM_INITDIALOG:
			return 0;
			break;
	
		case WM_SIZE:
			break;
	
		case WM_COMMAND:
			if( LOWORD(wParam) == IDCLOSE) // close button click
				EndDialog(hWnd,0);
			return 0;
			break;
	
		case WM_SHOWWINDOW:			
			break;

		case WM_LBUTTONDOWN:
			x = GET_X_LPARAM(lParam);
			y = GET_Y_LPARAM(lParam);
			pos = FindGrid(x,y);
			endGame = Calculate(hWnd,x,y);
			Game_Run(hWnd);
			if (endGame == 1) {
				MessageBox(hWnd, "YOU WON!", "GAME OVER", MB_OK);
				PostQuitMessage(0);
			}
			if (endGame == 2) {
				MessageBox(hWnd, "YOU LOST!", "GAME OVER", MB_OK);
				PostQuitMessage(0);
			}
			break;

		case WM_RBUTTONDOWN:
			if (MessageBox(hWnd, "Really Quit?", "My application", MB_OKCANCEL) == IDOK)
				DestroyWindow(hWnd);
			break;

		case WM_MBUTTONDOWN:
			if (MessageBox(hWnd, "Really Quit?", "My application", MB_OKCANCEL) == IDOK)
				DestroyWindow(hWnd);
			break;
		}
		return DefWindowProc (hWnd, msg, wParam, lParam);
}

 ATOM InitMainWindow(HINSTANCE hInstance, int nCmdShow) {
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = WinProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = APPTITLE;
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	return RegisterClassEx(&wc);
}

void MsgLoop() {
	MSG msg;
	int success = 0;
	while (!success) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (WM_QUIT == msg.message)
				success = 1;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			Game_Run(hWnd);
		}
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {	
		DWORD style;
		InitMainWindow(hInstance, nCmdShow);
		if (FULLSCREEN)
			style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
		else
			style = WS_OVERLAPPED;

		hWnd = CreateWindow(APPTITLE,
			APPTITLE,
			style,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			(HWND)NULL,
			(HMENU)NULL,
			hInstance,
			NULL);
		if (!hWnd)
			return false;
		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);
		if (!initD3D(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREEN))
			return 0;
		if (!Game_Init(hWnd))
			return 0;
		MsgLoop();
		return 0;
}
