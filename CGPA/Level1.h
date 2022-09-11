#pragma once
#ifndef LEVEL1_H
#define LEVEL1_H
#include "Header.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"

class Level1 : public Game
{
protected:
	Player* player;
	Enemy* enemy;

	

public:
	Level1() : Game() {
		this->Initialize();
	}
	~Level1();

	void Initialize();
	void Update();
	void Render();
	void Input();
};




#endif