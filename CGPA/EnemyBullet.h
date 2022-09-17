#pragma once
#include "Game.h"
#include "Header.h"

class EnemyBullet : public Game
{
protected:
	int speed;
	D3DXMATRIX mat;
	D3DXVECTOR2 acceleration;
	int isReflection;
	int randomNumber;


public:


	void Initialization();
	virtual void Update();
	void Render();
	RECT GetColRect();
	BOOLEAN InBoundary(D3DXVECTOR2 position);
	BOOLEAN Reflection(D3DXVECTOR2 position);

};

