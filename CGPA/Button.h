#pragma once
#ifndef BUTTON_H
#define BUTTON_H
#include "Header.h"
#include "Game.h"

class Button : public Game
{
private:
	int buttonWidth;
	int buttonHeight;


public:
	Button() : Game() {
		this->Initialize();
	}
	Button();


	void Initialize();
	void Update();
	void Render();
	void Input();
};

#endif