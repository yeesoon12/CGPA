#pragma once
#include "Header.h"
#include "Game.h"

enum Direction {
	NO_MOVE,
	LEFT,
	RIGHT
};

class Player : public Game {
private:
	

	boolean upPressed;
	boolean downPressed;
	boolean leftPressed;
	boolean rightPressed;
	boolean spacePressed;
	boolean zPressed;
	boolean xPressed;
	boolean cPressed;

	D3DXVECTOR2 velocity;
	float speed;
	int health;

	void Move();
	void Shoot();
	void CheckBoundary();

public:
	Player() : Game() {
		this->Initialize();
	}
	~Player();

	void Initialize();
	void Update();
	void Render();
	void Input();
	
};

