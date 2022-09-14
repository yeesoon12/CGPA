#pragma once
#include "EnemyBullet.h"
#include "Header.h"
class EnemyBall : public EnemyBullet
{
	int count;
	int fps;
	int reflectTime;
public:
	void Initialization(float Direction, D3DXVECTOR2 position);
	void Update();
	void Render();
};


