#pragma once
#include "Header.h"
#include "Game.h"
#include "PlayerShoot.h"
#include "Catalysts.h"
#include "Ultimate.h"


class Player : public Game {
private:
	PlayerShoot* shoot;
	Catalysts* catalysts;
	AudioManager* audioManager;
	AudioManager* audioManager2;
	Ultimate* ulti;
	boolean upPressed;
	boolean downPressed;
	boolean leftPressed;
	boolean rightPressed;
	boolean spacePressed;
	boolean zPressed;
	boolean xPressed;
	boolean cPressed;
	boolean isUlti;
	boolean isUlti2;
	int ultiCD;
	int counter;
	int cd;
	int focus;
	D3DXVECTOR2 velocity;
	float speed;
	int health;
	int move;
	int bulletAmount;
	vector<PlayerShoot*> bullet;

	enum Movement {
		UPDOWN,
		LEFT,
		RIGHT
	};


public:
	Player() : Game() {
		this->Initialize();
	}
	~Player();

	void Initialize();
	void Update();
	void Render();
	void Input();
	void minusHealth();
	boolean IsUlti();
	void addBullet(int bulletAmounts);
	vector<PlayerShoot*> getBullet();
	RECT getColRect();
	
	
};

