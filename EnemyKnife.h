#pragma once
#include "EnemyBullet.h"
#include "Header.h"
class EnemyKnife : public EnemyBullet
{

public:
	void Initialization(float Direction,D3DXVECTOR2 position);
	void Update();
	void Render();
};

