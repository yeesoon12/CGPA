#pragma once
#include "Game.h"
#include "Header.h"
#include "EnemyBullet.h"
#include "EnemyKnife.h"
#include "EnemySmallKnife.h"
#include "EnemyBall.h"
class EnemyBulletCombination : public Game
{
private:
	vector<EnemyBullet*> bulletpattern1;
	vector<EnemyBullet*> bulletpattern2;
	vector<EnemyBullet*> bulletpattern3;
	EnemyKnife* knife;
	EnemyBall* enegryBall;
	EnemySmallKnife* smallKnife;
	int count;
	int count2;

public:
	EnemyBulletCombination() : Game() {
	
	}
	~EnemyBulletCombination();

	void Initialization(float direction, D3DXVECTOR2 position, int bulletPa);
	void Update();
	void Render();
	vector<EnemyBullet*> getBulletPattern1();
	vector<EnemyBullet*> getBulletPattern2();
	vector<EnemyBullet*> getBulletPattern3();
	RECT getColRect();

};
