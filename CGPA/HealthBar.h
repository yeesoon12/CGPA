#pragma once
#include "Game.h"
class HealthBar: public Game
{
public:
	HealthBar(): Game() {

	}
	~HealthBar();

	void Initialize(int,int);
	void Update(float,int);
	void Render();
private:
	float bossHealths;
	int bossHealthTimes;
	LPDIRECT3DTEXTURE9 barTexture;
	LPD3DXFONT font;
	RECT textRect;
	D3DXVECTOR2 barScaling;
};

