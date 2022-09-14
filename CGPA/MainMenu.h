#pragma once
#ifndef MAINMENU_H
#define MAINMENU_H
#include "Header.h"
#include "Game.h"
#include "Button.h"

class MainMenu : public Game
{
protected:
	Button* button1;
	Button* button2;
	Button* button3;

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
};

#endif