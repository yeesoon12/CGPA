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

	D3DXVECTOR2 getVelocity();
	void setVelocity(D3DXVECTOR2 velocity);
	void addVelocity(D3DXVECTOR2 velocity);
	float getMass();
	float getRadius();
	RECT getColRect();
	D3DXVECTOR2 getPosition();
	D3DXVECTOR2 getCentre();
};

#endif