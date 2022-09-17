#pragma once
#include "Game.h"

class Cursor : public Game
{
public:
	Cursor() : Game()
	{
		this->Initialize();
	}
	~Cursor();
	boolean mouseLeftClick;
	boolean mouseRightClick;
	void Initialize();
	void Update();
	void Render();
	void Input();
	RECT GetCollision();
	bool isColl;

private:
	RECT mouseColRect;

};
