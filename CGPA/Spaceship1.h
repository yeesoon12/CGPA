#pragma once

#include "Spaceship.h"

class Spaceship1 : public Spaceship
{
public:
	Spaceship1() : Spaceship() {
		this->Initialize();
	}
	~Spaceship1();

	void Initialize();
	void Update(int frameToUpdate);
	void Render();
	void Input();
	void CheckBoundary();
};