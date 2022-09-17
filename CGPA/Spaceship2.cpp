#include "Spaceship2.h"

void Spaceship2::Initialize()
{
	// Set all key press to false
	upKeyPressed = false;
	downKeyPressed = false;
	leftKeyPressed = false;
	rightKeyPressed = false;
	spaceKeyPressed = false;
	wKeyPressed = false;
	aKeyPressed = false;
	sKeyPressed = false;
	dKeyPressed = false;

	currentFrame = 0;
	maxFrame = 1;

	position = D3DXVECTOR2(284, 484);

	direction = 0.0f;
	spriteFPS = 10;

	velocity = D3DXVECTOR2(0, 0);
	acceleration = D3DXVECTOR2(0, 0);

	rotationSpeed = 0.07f;
	mass = 1.0f;
	enginePower = 1.0f;

	gravity = 2;
	friction = 0.05;
	currentMovement = 0;
	movementSpeed = 5;

	animRect.top = currentFrame * spriteHeight;
	animRect.bottom = animRect.top + spriteHeight;
	animRect.left = spriteWidth;
	animRect.right = animRect.left + spriteWidth;

	colRect.top = position.y;
	colRect.bottom = colRect.top + spriteHeight;
	colRect.left = position.x;
	colRect.right = colRect.left + spriteWidth;
}

void Spaceship2::Render()
{
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
}

void Spaceship2::Update()
{
	// Key Press
	if (leftKeyPressed)
	{
		direction -= rotationSpeed;
	}
	if (rightKeyPressed)
	{
		direction += rotationSpeed;
	}
	if (upKeyPressed)
	{
		acceleration.x = sin(direction) * enginePower / mass;
		acceleration.y = -cos(direction) * enginePower / mass;
	}
	if (downKeyPressed)
	{
		acceleration.x = -sin(direction) * enginePower / mass;
		acceleration.y = cos(direction) * enginePower / mass;
	}

	velocity += acceleration;
	velocity *= 1 - friction;
	position += velocity;

	currentFrame++;
	if (currentFrame > maxFrame)
	{
		currentFrame = 0;
	}

	animRect.top = currentFrame * spriteHeight;
	animRect.bottom = animRect.top + spriteHeight;
	animRect.left = spriteWidth;
	animRect.right = animRect.left + spriteWidth;

	colRect.top = position.y;
	colRect.bottom = colRect.top + spriteHeight;
	colRect.left = position.x;
	colRect.right = colRect.left + spriteWidth;

	CheckBoundary();

	//  Animation Loop
	counter++;
	if (counter % spriteFPS == 0)
	{
		currentFrame++;
		if (currentFrame > maxFrame)
			currentFrame = 0;
	}

	upKeyPressed = false;
	downKeyPressed = false;
	leftKeyPressed = false;
	rightKeyPressed = false;

	acceleration = D3DXVECTOR2(0, 0);
}

void Spaceship2::Input()
{
	dInputKeyboardDevice->Acquire();
	dInputKeyboardDevice->GetDeviceState(256, diKeys);

	// Movement Key Press
	if (diKeys[DIK_W] & 0x80) {
		upKeyPressed = true;
	}

	if (diKeys[DIK_S] & 0x80) {
		downKeyPressed = true;
	}

	if (diKeys[DIK_A] & 0x80) {
		leftKeyPressed = true;
	}

	if (diKeys[DIK_D] & 0x80) {
		rightKeyPressed = true;
	}
}

void Spaceship2::CheckBoundary()
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

Spaceship2::~Spaceship2() {}
