#pragma once
#ifndef MAINMENU_H
#define MAINMENU_H
#include "Header.h"
#include "Game.h"

class MainMenu : public Game
{
protected:
	

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