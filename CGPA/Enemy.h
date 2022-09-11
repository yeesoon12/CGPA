#pragma once
#include "Game.h"
class Enemy: public Game
{
public:
	Enemy() : Game() {
		this->Initialize();
	}
	~Enemy();

	void Initialize();
	void Update();
	void Render();
private:
	int bossHealth;
	int bossDamage;
};

