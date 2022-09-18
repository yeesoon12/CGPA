#pragma once
#include "Game.h"
#include "Cursor.h"

class EndScene : public Game
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
	D3DXVECTOR2 text2Position;
	RECT text1Rect;
	RECT text2Rect;
	RECT text1ColRect;
	RECT text2ColRect;
	Cursor* cursor;

public:
	EndScene() : Game()
	{
		this->Initialize();
	}
	~EndScene();

	void Initialize();
	void Update(vector<Game*>*);
	void Render();
	void Input();
	bool CollisionDetection(RECT A, RECT B);
};

