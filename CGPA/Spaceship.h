#pragma once
#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "Header.h"
#include "Game.h"

class Spaceship : public Game
{
protected:
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
	D3DXVECTOR2 acceleration;

	int spriteFPS;

	float rotationSpeed;
	float mass;
	float enginePower;

	float gravity;
	float friction;
	int currentMovement;
	int movementSpeed;

	int counter;

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