#pragma once
#include "Game.h"
#include "Header.h"

class PowerUp : public Game
{
private:
	float speed;
	int powerUpNum;
	


public:
	PowerUp() : Game() {

	}
	~PowerUp(); 
	void setPowerUpNum(int num);
	void Initialization(D3DXVECTOR2);
	void Update();
	void Render();
	int getPowerUpNum();
	
	RECT getColRect();

};

