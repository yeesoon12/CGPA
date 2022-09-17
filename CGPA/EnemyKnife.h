#pragma once
#include "EnemyBullet.h"
#include "Header.h"
class EnemyKnife : public EnemyBullet
{

public:
	EnemyKnife() : EnemyBullet() {
		this->Initialize();
	}
	~EnemyKnife();
	void Initialization(float Direction,D3DXVECTOR2 position, int speed,int);
	void Update();
	void Render();
};

