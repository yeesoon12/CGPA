#pragma once
#ifndef LEVELEXBALL_H
#define LEVELEXBALL_H
#include "Header.h"
#include "Game.h"

class LevelExBall : public Game
{
private:
	D3DXVECTOR2 velocity;
	float mass;
	float gravity;
	float friction;

public:
	LevelExBall() : Game() {
		this->Initialize();
	}
	~LevelExBall();

	void Initialize();
	void Render();
	void Update();
	void CheckBoundary();

	D3DXVECTOR2 getVelocity();
	void setVelocity(D3DXVECTOR2 velocity);
	float getMass();
	float getRadius();
	RECT getColRect();
	D3DXVECTOR2 getPosition();
	D3DXVECTOR2 getCentre();
};

#endif
