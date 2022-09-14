#include "Spaceship.h"

void Spaceship::Initialize()
{
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/spaceship.png", &texture);

	if (FAILED(hr)) {
		cout << "Failed to load texture123456789" << endl;
	}

	upKeyPressed = false;
	downKeyPressed = false;
	leftKeyPressed = false;
	rightKeyPressed = false;
	spaceKeyPressed = false;
	wKeyPressed = false;
	aKeyPressed = false;
	sKeyPressed = false;
	dKeyPressed = false;

	velocity = D3DXVECTOR2(0, 0);
	speed = 2.f;

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

	scaling = D3DXVECTOR2(1.0f, 1.0f);
	centre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
	direction = 0;
	// position = D3DXVECTOR2(MyWindowWidth / 2, 800);

	colRect.top = position.y;
	colRect.bottom = colRect.top + spriteHeight;
	colRect.left = position.x;
	colRect.right = colRect.left + spriteWidth;

	maxFrame = (spriteRow * spriteCol) - 1;
}

void Spaceship::Render()
{
	


	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
}

void Spaceship::Update() {



}

void Spaceship::Input() {
	dInputKeyboardDevice->Acquire();
	dInputKeyboardDevice->GetDeviceState(256, diKeys);

	// shoot update
	if (diKeys[DIK_SPACE] & 0x80) {
		spaceKeyPressed = true;
	}

	// movement
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



void Spaceship::CheckBoundary() { // TODO: fix this shit
	if (position.x - speed < 0) {
		leftKeyPressed = false;
	}

	if (position.x + spriteWidth + speed > MyWindowWidth) {
		rightKeyPressed = false;
	}

	if (position.y - speed < 0) {
		upKeyPressed = false;
	}

	if (position.y + spriteHeight + speed > MyWindowHeight) {
		downKeyPressed = false;
	}
}

void Spaceship::Move() {
	CheckBoundary();

	if (upKeyPressed) {
		position.y -= speed;
		upKeyPressed = false;
	}

	if (downKeyPressed) {
		position.y += speed;
		downKeyPressed = false;
	}

	if (leftKeyPressed) {
		position.x -= speed;
		leftKeyPressed = false;
	}

	if (rightKeyPressed) {
		position.x += speed;
		rightKeyPressed = false;
	}


	position += velocity;

}


Spaceship::~Spaceship() {
}
