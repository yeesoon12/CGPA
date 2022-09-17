#pragma once
#ifndef LEVELEX_H
#define LEVELEX_H
#include "Header.h"
#include "Game.h"
#include "Spaceship1.h"
#include "Spaceship2.h"
#include "LevelExBall.h"

class LevelEx : public Game
{
protected:
	Spaceship1* spaceship1;
	Spaceship2* spaceship2;
	LevelExBall* ball;

	// Line
	LPD3DXLINE line;

	// Font Type
	LPD3DXFONT font;
	D3DXVECTOR2 textPosition;
	int textWidth;
	int textHeight;
	RECT textRect;
	LPCSTR textString;

	// Win Box
	RECT box1;
	RECT box2;
	boolean isEnd;
	int winner;

public:
	LevelEx() : Game() {

	}
	~LevelEx();
	void Initialize();
	void Update(vector<Game*>*);
	void Render();
	void Input();
	bool CollisionDetection(RECT A, RECT B);
	bool CircleCollisionDetection(float radiusA, float radiusB, D3DXVECTOR2 positionA, D3DXVECTOR2 positionB);
	void CheckPlayerCollide();
	void CheckPlayerCollideWithBall();
	void CheckWinner();
};
#endif