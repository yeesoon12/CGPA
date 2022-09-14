#pragma once
#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "Header.h"
#include "Game.h"

class Spaceship : public Game
{
private:

	boolean upKeyPressed;
	boolean downKeyPressed;
	boolean leftKeyPressed;
	boolean rightKeyPressed;
	boolean spaceKeyPressed;
	boolean wKeyPressed;
	boolean aKeyPressed;
	boolean sKeyPressed;
	boolean dKeyPressed;

	D3DXVECTOR2 velocity;
	float speed;

	void Move();
	void Shoot();
	void CheckBoundary();


public:
	Spaceship() : Game() {
		this->Initialize();
	}
	~Spaceship();

	void Initialize();
	void Update();
	void Render();
	void Input();
};

#endif