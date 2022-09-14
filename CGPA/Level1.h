#pragma once
#ifndef LEVEL1_H
#define LEVEL1_H
#include "Header.h"
#include "Game.h"
#include "Player.h"
#include "PowerUp.h"
#include "Enemy.h"
#include "EnemyBulletCombination.h"
class Level1 : public Game
{
protected:
	Player* player;
	PowerUp* powerUp;
	Enemy* enemy;
	EnemyBulletCombination* skill;
	vector<vector<EnemyBullet*>> bulletcombo1;
	vector<EnemyBullet*> currentPattern;
	int i;
	int j;
	float direction2;
	

public:
	Level1() : Game() {
		
	}
	~Level1();

	void clearBullet();
	void Initialize();
	void Update(int FrameToUpdate);
	void Render();
	void Input();
	bool CollisionDetection(RECT A, RECT B);
};




#endif