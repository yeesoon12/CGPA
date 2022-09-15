#pragma once
#ifndef LEVEL1_H
#define LEVEL1_H
#include "Header.h"
#include "Game.h"
#include "Player.h"
#include "PowerUp.h"
#include "Enemy.h"
class Level1 : public Game
{
protected:
	Player* player;
	Enemy* enemy;
	vector<PlayerShoot*> bullets;
	PlayerShoot* bullet;
	int bulletCD;
	int j;
	float direction2;
	vector<EnemyBullet*> enemyBullets;
	AudioManager* audioManager2;
	

public:
	Level1() : Game() {
		
	}
	~Level1();
	void Initialize();
	void Update();
	void Render();
	void Input();
	bool CollisionDetection(RECT A, RECT B);
};




#endif