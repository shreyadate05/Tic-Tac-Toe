#ifndef _GAME_H
#define _GAME_H

#include <d3d9.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "dxgraphics.h"

#define APPTITLE "Anim_Sprite"
#define FULLSCREEN 0
#define SCREEN_WIDTH 490
#define SCREEN_HEIGHT 490
#define KEY_DOWN(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

int Game_Init(HWND);
void Game_Run(HWND);
void Game_End(HWND);
int Calculate(HWND, int, int);
int FindGrid(int, int);
int checkWinner(HWND);
int checkVertical();
int checkHorizontal();
int checkDiagonal();

class SPRITE {
public:
	int x,y;
	int width, height;
	int movex, movey;
	int currframe, lasteframe;
	int animdelay, animcount;
};

#endif