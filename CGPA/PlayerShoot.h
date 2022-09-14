#pragma once


#include "Game.h"
#include "Header.h"

class PlayerShoot : public Game
{
private:
	D3DXVECTOR2 speed;
	D3DXVECTOR2 speed2;
	D3DXVECTOR2 speed3;
	D3DXVECTOR2 speed4;
	D3DXVECTOR2 speed5;
	int bulletAmount;
	int fokus;
	D3DXVECTOR2 position2;
	D3DXVECTOR2 position3;
	D3DXVECTOR2 position4;
	D3DXVECTOR2 position5;

public:

	PlayerShoot() : Game() {
		
	}
	~PlayerShoot();

	void Initialization(D3DXVECTOR2 bulletPosition, int bulletNum,int focus);
	void Update();
	void Render();
		
};

