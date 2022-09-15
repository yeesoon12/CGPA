#pragma once
#ifndef MAINMENU_H
#define MAINMENU_H
#include "Header.h"
#include "Game.h"

class MainMenu : public Game
{
private:
	// Font Type
	LPD3DXFONT font;
	LPD3DXFONT font2;

	// Line
	LPD3DXLINE line;

	// Text Settings
	int textWidth;
	int textHeight;
	D3DXVECTOR2 text1Position;
	D3DXVECTOR2 text2Position;
	D3DXVECTOR2 text3Position;
	D3DXVECTOR2 text4Position;
	RECT text1Rect;
	RECT text2Rect;
	RECT text3Rect;
	RECT text4Rect;

public:
	MainMenu() : Game()
	{
		this->Initialize();
	}
	~MainMenu();

	void Initialize();
	void Update();
	void Render();
	void Input();
	bool CollisionDetection(RECT A, RECT B);
};

#endif