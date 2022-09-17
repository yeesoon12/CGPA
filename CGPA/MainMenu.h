#pragma once
#ifndef MAINMENU_H
#define MAINMENU_H
#include "Header.h"
#include "Game.h"
#include "Cursor.h"
#include "Level1.h"
#include "LevelEx.h"

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
	int textBorder;
	D3DXVECTOR2 text1Position;
	D3DXVECTOR2 text2Position;
	D3DXVECTOR2 text3Position;
	D3DXVECTOR2 text4Position;

	RECT text1Rect;
	RECT text2Rect;
	RECT text3Rect;
	RECT text4Rect;
	RECT text1ColRect;
	RECT text2ColRect;
	RECT text3ColRect;
	RECT text4ColRect;

	Level1* level1;
	LevelEx* levelEx;
	Cursor* cursor;

public:
	MainMenu() : Game()
	{
		this->Initialize();
	}
	~MainMenu();

	void Initialize();
	void Update(vector<Game*>*);
	void Render();
	void Input();
	bool CollisionDetection(RECT A, RECT B);
};

#endif