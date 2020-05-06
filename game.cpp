#include <vector>
#include <algorithm>
#include <iterator>
#include "game.h"
using namespace std;
//using namespace System;

vector<int> excludeList;
vector<int> crosses;
vector<int> nuts;
SPRITE kitty[9];
LPDIRECT3DSURFACE9 kitty_image[9];
long start = GetTickCount();
LPDIRECT3DSURFACE9 surf;
int location[9];
vector<int> oldList;

int Game_Init(HWND hWnd) {
	char s[25];
	int n;
	srand(time(NULL));

	for (n=0; n<9; n++) {
		location[n] = 0;
		sprintf_s(s, "cat%d.bmp", n+1);
		kitty_image[n] = LoadSurface("start.bmp", D3DCOLOR_XRGB(255,0,255));
		if (kitty_image[n] == NULL) {
			MessageBox(hWnd, "d3ddev not initialized", "Error", MB_OK);
		}
		kitty[n].width = 150;
		kitty[n].height = 150;
		oldList.push_back(n);
	}

	kitty[0].x = 10;
	kitty[0].y = 10;

	kitty[1].x = 170;
	kitty[1].y = 10;

	kitty[2].x = 330;
	kitty[2].y = 10;

	kitty[3].x = 10;
	kitty[3].y = 170;

	kitty[4].x = 170;
	kitty[4].y = 170;

	kitty[5].x = 330;
	kitty[5].y = 170;

	kitty[6].x = 10;
	kitty[6].y = 330;

	kitty[7].x = 170;
	kitty[7].y = 330;

	kitty[8].x = 330;
	kitty[8].y = 330;

	return 1;
}

void Game_Run(HWND hWnd) {
	
	RECT rect[9];

	if (d3ddev->BeginScene()) {
		d3ddev->ColorFill(backbuffer, NULL, D3DCOLOR_XRGB(0,0,0));
		for (int i=0; i<9; i++) {
			rect[i].left = kitty[i].x;
			rect[i].top = kitty[i].y;
			rect[i].right = kitty[i].x + kitty[i].width;
			rect[i].bottom = kitty[i].y + kitty[i].height;
			d3ddev->StretchRect(kitty_image[i], NULL, backbuffer, &rect[i], D3DTEXF_NONE);
		}
		d3ddev->EndScene();
	}

	d3ddev->Present(NULL, NULL, NULL, NULL);
	if (KEY_DOWN(VK_ESCAPE))
		PostQuitMessage(0);
}

void Game_End(HWND hWnd) {
	int n;
	for (n=0; n<9; n++)
		kitty_image[n]->Release();
}

int Calculate(HWND hWnd, int x, int y) {
	RECT rect;
	vector<int> difference;
	srand(time(NULL));
	int number = 8;
	int n = 9;
	int found = 1;
	int num;
	int done = 0;
	static int count = 0;
	int move = FindGrid(x, y);
	excludeList.push_back(move);
	crosses.push_back(move);
	location[move] = 1;
	kitty_image[move] = LoadSurface("cross.bmp", D3DCOLOR_XRGB(255,0,255));
	Sleep(100);
	done = checkWinner(hWnd);
	if (done == 0) {
		sort(excludeList.begin(), excludeList.end());
		sort(oldList.begin(), oldList.end());
		set_difference(oldList.begin(), oldList.end(), excludeList.begin(), excludeList.end(), back_inserter(difference));
		if (!difference.empty()) {
			random_shuffle(difference.begin(), difference.end());
			num = difference[difference.size()-1];
			excludeList.push_back(num);
			nuts.push_back(num);
			location[num] = 1;
			kitty_image[num] = LoadSurface("nut.bmp", D3DCOLOR_XRGB(255,0,255));
			count++;
			done = checkWinner(hWnd);
			if (done == 2) {
				return 2;
			}
		}
	} else if (done == 1) {
		return 1;
	} else if (done == 2) {
		return 2;
	} 
	return 0;
}

int checkWinner(HWND hWnd) {
	if (checkVertical() == 1 || checkHorizontal() == 1 || checkDiagonal() == 1) {
		return 1;
	}
	if (checkVertical() == 2 || checkHorizontal() == 2 || checkDiagonal() == 2) {
		return 2;
	}
	return 0;
}

int checkVertical() {
	if (location[0] == 1 && location[3] == 1 && location[6] == 1) {
		if ((find(crosses.begin(), crosses.end(), 0) != crosses.end()) &&
			(find(crosses.begin(), crosses.end(), 3) != crosses.end()) &&
			(find(crosses.begin(), crosses.end(), 6) != crosses.end())
		   ) {
		   return 1;
		}
		if ((find(nuts.begin(), nuts.end(), 0) != nuts.end()) &&
			(find(nuts.begin(), nuts.end(), 3) != nuts.end()) &&
			(find(nuts.begin(), nuts.end(), 6) != nuts.end())
			) {
			return 2;
		}
	}
	if (location[1] == 1 && location[4] == 1 && location[7] == 1) {
		if ((find(crosses.begin(), crosses.end(), 1) != crosses.end()) &&
			(find(crosses.begin(), crosses.end(), 4) != crosses.end()) &&
			(find(crosses.begin(), crosses.end(), 7) != crosses.end())
			) {
				return 1;
		}
		if ((find(nuts.begin(), nuts.end(), 1) != nuts.end()) &&
			(find(nuts.begin(), nuts.end(), 4) != nuts.end()) &&
			(find(nuts.begin(), nuts.end(), 7) != nuts.end())
			) {
				return 2;
		}
	}
	if (location[2] == 1 && location[5] == 1 && location[8] == 1) {
		if ((find(crosses.begin(), crosses.end(), 2) != crosses.end()) &&
			(find(crosses.begin(), crosses.end(), 5) != crosses.end()) &&
			(find(crosses.begin(), crosses.end(), 8) != crosses.end())
			) {
				return 1;
		}
		if ((find(nuts.begin(), nuts.end(), 2) != nuts.end()) &&
			(find(nuts.begin(), nuts.end(), 5) != nuts.end()) &&
			(find(nuts.begin(), nuts.end(), 8) != nuts.end())
			) {
				return 2;
		}
	}
	return 0;
}

int checkHorizontal() {
	if (location[0] == 1 && location[1] == 1 && location[2] == 1) {
		if ((find(crosses.begin(), crosses.end(), 0) != crosses.end()) &&
			(find(crosses.begin(), crosses.end(), 1) != crosses.end()) &&
			(find(crosses.begin(), crosses.end(), 2) != crosses.end())
			) {
				return 1;
		}
		if ((find(nuts.begin(), nuts.end(), 0) != nuts.end()) &&
			(find(nuts.begin(), nuts.end(), 1) != nuts.end()) &&
			(find(nuts.begin(), nuts.end(), 2) != nuts.end())
			) {
				return 2;
		}
	}
	if (location[3] == 1 && location[4] == 1 && location[5] == 1) {
		if ((find(crosses.begin(), crosses.end(), 3) != crosses.end()) &&
			(find(crosses.begin(), crosses.end(), 4) != crosses.end()) &&
			(find(crosses.begin(), crosses.end(), 5) != crosses.end())
			) {
				return 1;
		}
		if ((find(nuts.begin(), nuts.end(), 3) != nuts.end()) &&
			(find(nuts.begin(), nuts.end(), 4) != nuts.end()) &&
			(find(nuts.begin(), nuts.end(), 5) != nuts.end())
			) {
				return 2;
		}
	}
	if (location[6] == 1 && location[7] == 1 && location[8] == 1) {
		if ((find(crosses.begin(), crosses.end(), 6) != crosses.end()) &&
			(find(crosses.begin(), crosses.end(), 7) != crosses.end()) &&
			(find(crosses.begin(), crosses.end(), 8) != crosses.end())
			) {
				return 1;
		}
		if ((find(nuts.begin(), nuts.end(), 6) != nuts.end()) &&
			(find(nuts.begin(), nuts.end(), 7) != nuts.end()) &&
			(find(nuts.begin(), nuts.end(), 8) != nuts.end())
			) {
				return 2;
		}
	}
	return 0;
}

int checkDiagonal() {
	if (location[0] == 1 && location[4] == 1 && location[8] == 1) {
		if ((find(crosses.begin(), crosses.end(), 0) != crosses.end()) &&
			(find(crosses.begin(), crosses.end(), 4) != crosses.end()) &&
			(find(crosses.begin(), crosses.end(), 8) != crosses.end())
			) {
				return 1;
		}
		if ((find(nuts.begin(), nuts.end(), 0) != nuts.end()) &&
			(find(nuts.begin(), nuts.end(), 4) != nuts.end()) &&
			(find(nuts.begin(), nuts.end(), 8) != nuts.end())
			) {
				return 2;
		}
	}
	if (location[2] == 1 && location[4] == 1 && location[6] == 1) {
		if ((find(crosses.begin(), crosses.end(), 2) != crosses.end()) &&
			(find(crosses.begin(), crosses.end(), 4) != crosses.end()) &&
			(find(crosses.begin(), crosses.end(), 6) != crosses.end())
			) {
				return 1;
		}
		if ((find(nuts.begin(), nuts.end(), 2) != nuts.end()) &&
			(find(nuts.begin(), nuts.end(), 4) != nuts.end()) &&
			(find(nuts.begin(), nuts.end(), 6) != nuts.end())
			) {
				return 2;
		}
	}	
	return 0;
}

int FindGrid(int x, int y) {
	if (x>10 && x<150 && y>10 && y<150 && location[0] != 1) {
		return 0;
	}
	if (x>170 && x<320 && y>10 && y<150 && location[1] != 1) {
		return 1;
	}
	if (x>330 && x<480 && y>10 && y<150 && location[2] != 1) {
		return 2;
	}
	if (x>10 && x<150 && y>170 && y<320 && location[3] != 1) {
		return 3;
	}
	if (x>170 && x<320 && y>170 && y<320 && location[4] != 1) {
		return 4;
	}
	if (x>330 && x<480 && y>170 && y<320 && location[5] != 1) {
		return 5;
	}
	if (x>10 && x<150 && y>330 && y<480 && location[6] != 1) {
		return 6;
	}
	if (x>170 && x<320 && y>330 && y<480 && location[7] != 1) {
		return 7;
	}
	if (x>330 && x<480 && y>330 && y<480 && location[8] != 1) {
		return 8;
	}
	return -1;
}
