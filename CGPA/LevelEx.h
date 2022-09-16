#pragma once
#ifndef LEVELEX_H
#define LEVELEX_H
#include "Header.h"
#include "Game.h"
#include "Spaceship1.h"
#include "Spaceship2.h"

class LevelEx : public Game
{
protected:
	Spaceship1* spaceship1;
	Spaceship2* spaceship2;

public:
	LevelEx() : Game() {

	}
	~LevelEx();
	void Initialize();
	void Update();
	void Render();
	void Input();
	bool CollisionDetection(RECT A, RECT B);
	bool CircleCollisionDetection(float radiusA, float radiusB, D3DXVECTOR2 positionA, D3DXVECTOR2 positionB);
};

#endif