#pragma once
#include "Game.h"
#include "Header.h"

class EnemyBullet : public Game
{
protected:
	int speed;
	D3DXMATRIX mat;
	D3DXVECTOR2 acceleration;
	


public:


	void Initialization();
	void Update();
	void Render();
	BOOLEAN InBoundary(D3DXVECTOR2 position);

};

