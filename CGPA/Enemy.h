#pragma once
#include "Game.h"
#include "MagicBack.h"
#include "HealthBar.h"
class Enemy: public Game
{
enum Direction {
		STAND,
		MOVE
};
public:
	Enemy() : Game() {
		this->Initialize();
	}
	~Enemy();

	void Initialize();
	void Update();
	void Render();
private:
	int fps;
	int counters;
	int checkMove;
	float bossHealth;
	int bossDamage;
	int counter;
	int attackPosition;
	int maxAttackPosition;
	float enemySpeedVertical;
	float enemySpeedHorizotal;
	int bossHealthTime;
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 acceleration;
	MagicBack* magicBack;
	HealthBar* healthBar;
};

