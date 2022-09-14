#pragma once
#include "Game.h"
#include "Header.h"

class Catalysts : public Game
{
private:
	
	D3DXVECTOR2 position1;
	D3DXVECTOR2 position2;
	D3DXVECTOR2 catalystsCenter;
	float direction2;
	int fokus;
	D3DXVECTOR2 topPosition;
	D3DXVECTOR2 scaling2;


public:


	void Initialization(D3DXVECTOR2 catalystsPosition);
	void Update(D3DXVECTOR2 catalystsPosition, int focus);
	void Render();

};

