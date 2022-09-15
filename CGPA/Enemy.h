#pragma once
#include "Game.h"
#include "MagicBack.h"
#include "HealthBar.h"
#include "PowerUp.h"
#include "EnemyBulletCombination.h"
#include "Ultimate.h"
class Enemy: public Game
{
enum Direction {
		STAND,
		MOVE
};
public:
	Enemy() : Game() {
		this->Initialize();
	}
	~Enemy();

	void Initialize();
	void Update();
	void Render();
	RECT GetCollisionRect();
	void minusHealth();
	void clearBullet();
	PowerUp* powerUp;
	vector<EnemyBullet*> getBullet();
private:
	EnemyBulletCombination* bulletCom;
	vector<EnemyBullet*> enemyBullets;
	int fps;
	Ultimate* ulti;
	boolean isUlti;
	int counters;
	int stage;
	int checkMove;
	float direction2;
	float bossHealth;
	int bossDamage;
	int counter;
	int count;
	int abc;
	int bulletDirection;
	int bulletCD;
	int attackPattern;

	LPD3DXLINE line;

	boolean drop;
	boolean isPower;
	int attackPosition;
	int maxAttackPosition;
	float enemySpeedVertical;
	float enemySpeedHorizotal;
	int bossHealthTime;
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 acceleration;
	MagicBack* magicBack;
	HealthBar* healthBar;
	
};

