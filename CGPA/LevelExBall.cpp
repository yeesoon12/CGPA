#include "LevelExBall.h"
LevelExBall::~LevelExBall() {
}

void LevelExBall::Initialize()
{
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/EnemyBullet3.png", &texture);

	textureWidth = 16;
	textureHeight = 16;
	spriteWidth = textureWidth;
	spriteHeight = textureHeight;

	animRect.top = 0;
	animRect.bottom = animRect.top + spriteHeight;
	animRect.left = 0;
	animRect.right = animRect.left + spriteWidth;

	colRect.top = position.y;
	colRect.bottom = colRect.top + spriteHeight;
	colRect.left = position.x;
	colRect.right = colRect.left + spriteWidth;

	scaling = D3DXVECTOR2(1.0f, 1.0f);
	centre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
	direction = 0.0f;
	position = D3DXVECTOR2(293, 393);

	velocity = D3DXVECTOR2(0, 0);
	mass = 1.0f;
	gravity = 2;
	friction = 0.02;
}

void LevelExBall::Render()
{
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
}

void LevelExBall::Update()
{
	velocity *= 1 - friction;
	position += velocity;

	colRect.top = position.y;
	colRect.bottom = colRect.top + spriteHeight;
	colRect.left = position.x;
	colRect.right = colRect.left + spriteWidth;

	CheckBoundary();
}

void LevelExBall::CheckBoundary()
{
	if (position.x < 0 || position.x > MyWindowWidth - spriteWidth)
	{
		if (position.x < 0)
			position.x = 0;
		if (position.x > MyWindowWidth - spriteWidth)
			position.x = MyWindowWidth - spriteWidth;

		velocity.x *= -1;
	}

	if (position.y < 0 || position.y > MyWindowHeight - spriteHeight)
	{
		if (position.y < 0)
			position.y = 0;
		if (position.y > MyWindowHeight - spriteHeight)
			position.y = MyWindowHeight - spriteHeight;
		velocity.y *= -1;
	}
}

D3DXVECTOR2 LevelExBall::getVelocity()
{
	return velocity;
}

void LevelExBall::setVelocity(D3DXVECTOR2 velocity)
{
	this->velocity = velocity;
}

float LevelExBall::getMass()
{
	return mass;
}

float LevelExBall::getRadius()
{
	return spriteWidth / 2;
}

RECT LevelExBall::getColRect()
{
	return colRect;
}

D3DXVECTOR2 LevelExBall::getPosition()
{
	return position;
}

D3DXVECTOR2 LevelExBall::getCentre()
{
	return centre;
}