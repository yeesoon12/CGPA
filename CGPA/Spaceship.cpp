#include "Spaceship.h"

void Spaceship::Initialize()
{
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/spaceship.png", &texture);

	if (FAILED(hr))
	{
		cout << "Failed to load spaceship texture." << endl;
	}

	textureWidth = 64;
	textureHeight = 64;
	spriteRow = 2;
	spriteCol = 2;
	spriteWidth = textureWidth / spriteCol;
	spriteHeight = textureHeight / spriteRow;

	animRect.top = currentFrame * spriteHeight;
	animRect.bottom = animRect.top + spriteHeight;
	animRect.left = currentFrame * spriteWidth;
	animRect.right = animRect.left + spriteWidth;

	colRect.top = position.y;
	colRect.bottom = colRect.top + spriteHeight;
	colRect.left = position.x;
	colRect.right = colRect.left + spriteWidth;

	scaling = D3DXVECTOR2(1.0f, 1.0f);
	centre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);

	counter = 0;

	maxFrame = 2;
}

D3DXVECTOR2 Spaceship::getVelocity()
{
	return velocity;
}

void Spaceship::setVelocity(D3DXVECTOR2 velocity)
{
	this->velocity = velocity;
}

void Spaceship::addVelocity(D3DXVECTOR2 velocity)
{
	this->velocity += velocity;
}

float Spaceship::getMass()
{
	return mass;
}

float Spaceship::getRadius()
{
	return spriteWidth / 2;
}

RECT Spaceship::getColRect()
{
	return colRect;
}

D3DXVECTOR2 Spaceship::getPosition()
{
	return position;
}

D3DXVECTOR2 Spaceship::getCentre()
{
	return centre;
}

Spaceship::~Spaceship() {
}