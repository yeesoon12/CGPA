#pragma once
#include "Game.h"
class MagicBack : public Game
{
public:
	MagicBack() : Game() {

	}
	~MagicBack();


	void Initialize(D3DXVECTOR2);
	void Update(D3DXVECTOR2, int);
	void Render();
private:
	int red;
};

