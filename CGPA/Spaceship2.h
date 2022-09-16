#pragma once

#include "Spaceship.h"

class Spaceship2 : public Spaceship
{
public:
	Spaceship2() : Spaceship() {
		this->Initialize();
	}
	~Spaceship2();

	void Initialize();
	void Update(int frameToUpdate);
	void Render();
	void Input();
	void CheckBoundary();
};