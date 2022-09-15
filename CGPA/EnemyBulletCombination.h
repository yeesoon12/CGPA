#pragma once
#include "Game.h"
#include "Header.h"
#include "EnemyBullet.h"
#include "EnemyKnife.h"
#include "EnemySmallKnife.h"
#include "EnemyBall.h"
class EnemyBulletCombination : public Game
{





public:
	EnemyKnife* knife;
	EnemyBall* enegryBall;
	EnemySmallKnife* smallKnife;
	EnemyBulletCombination() : Game() {
	
	}
	~EnemyBulletCombination();

	void Update();
	void Render();

};
