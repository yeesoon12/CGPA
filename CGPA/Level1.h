#pragma once
#ifndef LEVEL1_H
#define LEVEL1_H
#include "Header.h"
#include "Game.h"
#include "Player.h"
#include "PowerUp.h"
#include "Enemy.h"
#include "WinScene.h"
#include "EndScene.h"

class Level1 : public Game
{
protected:
	Player* player;
	Enemy* enemy;
	WinScene* winScene;
	EndScene* endScene;
	vector<PlayerShoot*> bullets;
	PlayerShoot* bullet;
	int bulletCD;
	int j;
	boolean isStart;
	float direction2;
	vector<EnemyBullet*> enemyBullets;
	int bgm;
	int counter;
	int bossHealth;
	float soundEffectVolume;
	float bgmVolume;
	boolean isEnd;
	boolean isWin;
	boolean isDie;
	boolean F1Pressed;
	boolean F2Pressed;
	boolean F3Pressed;
	boolean F4Pressed;
	int endCounter;

public:
	Level1() : Game() {
		this->Initialize();
	}
	~Level1();
	void Initialize();
	void Update(vector<Game*>*);
	void Render();
	void Input();
	bool CollisionDetection(RECT A, RECT B);
};




#endif