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
	void Input();
	int GetHealthTime();
private:
	EnemyBulletCombination* bulletCom;
	vector<EnemyBullet*> enemyBullets;
	AudioManager* audioManager;
	AudioManager* audioManager2;
	AudioManager* audioManager3;
	int fps;
	Ultimate* ulti;
	boolean isUlti;
	boolean F3Pressed;
	boolean F4Pressed;
	int counters;
	int stage;
	int speed;
	int checkMove;
	float direction2;
	float bossHealth;
	int bossDamage;
	int counter;
	int counter2;
	int count;
	int abc;
	int randomPosition;
	float smallKnifeDirection;
	float knifeDirection;
	int bulletCD;
	int bulletCD2;
	int attackPattern;
	int pattern1Counter;

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

