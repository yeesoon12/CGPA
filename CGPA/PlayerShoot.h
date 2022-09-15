#pragma once


#include "Game.h"
#include "Header.h"

class PlayerShoot : public Game
{
private:
	float speed;
	int fokus;
	boolean isHit;

public:

	PlayerShoot() : Game() {
		
	}
	~PlayerShoot();

	void Initialization(D3DXVECTOR2 bulletPosition, float,int focus);
	void Update();
	void Render();
	RECT GetColRect();
	void SetIsHit();
		
};

