#pragma once
#include "Game.h"
#include "Cursor.h"

class WinScene : public Game
{
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
	RECT text1Rect;
	RECT text1ColRect;


	Cursor* cursor;

public:
	WinScene() : Game()
	{
		this->Initialize();
	}
	~WinScene();

	void Initialize();
	void Update(vector<Game*>* game);
	void Render();
	void Input();
	bool CollisionDetection(RECT A, RECT B);
};
