#pragma once
#include "EnemyBullet.h"
#include "Header.h"
class EnemySmallKnife : public EnemyBullet
{
private:
	float increaseDir;
public:
	EnemySmallKnife() : EnemyBullet() {
		
	}
	~EnemySmallKnife();
	void Initialization(float Direction, D3DXVECTOR2 position, int speed, float directionInc);
	void Update();
	void Render();
};



