#include "Player.h"

void Player::Initialize()
{
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/Player.png", &texture);

	if (FAILED(hr)) {
		cout << "Failed to load texture123456789" << endl;
	}

	health = 3;
	upPressed = false;
	downPressed = false;
	leftPressed = false;
	rightPressed = false;
	spacePressed = false;
	velocity = D3DXVECTOR2(0, 0);
	speed = 2.f;

	textureWidth = 512;
	textureHeight = 308;

	spriteRow = 3;
	spriteCol = 8;
	spriteWidth = textureWidth / spriteCol;
	spriteHeight = textureHeight / spriteRow;

	animRect.top = currentFrame * spriteHeight;
	animRect.bottom = animRect.top + spriteHeight;
	animRect.left = currentFrame * spriteWidth;
	animRect.right = animRect.left + spriteWidth;

	scaling = D3DXVECTOR2(0.7, -0.7);
	centre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
	direction = 0;
	position = D3DXVECTOR2(MyWindowWidth/2, 800);

	colRect.top = position.y;
	colRect.bottom = colRect.top + spriteHeight;
	colRect.left = position.x;
	colRect.right = colRect.left + spriteWidth;

	maxFrame = (spriteRow * spriteCol) - 1;
}

void Player::Render()
{
	if (health <= 0) {
		return;
	}


	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
}

void Player::Update() {
	


}

void Player::Input() {
	dInputKeyboardDevice->Acquire();
	dInputKeyboardDevice->GetDeviceState(256, diKeys);

	// shoot update
	if (diKeys[DIK_SPACE] & 0x80) {
		spacePressed = true;
	}

	// movement
	if (diKeys[DIK_W] & 0x80) {
		upPressed = true;
	}

	if (diKeys[DIK_S] & 0x80) {
		downPressed = true;
	}

	if (diKeys[DIK_A] & 0x80) {
		leftPressed = true;
	}

	if (diKeys[DIK_D] & 0x80) {
		rightPressed = true;
	}
}



void Player::CheckBoundary() { // TODO: fix this shit
	if (position.x - speed < 0) {
		leftPressed = false;
	}

	if (position.x + spriteWidth + speed > MyWindowWidth) {
		rightPressed = false;
	}

	if (position.y - speed < 0) {
		upPressed = false;
	}

	if (position.y + spriteHeight + speed > MyWindowHeight) {
		downPressed = false;
	}
}

void Player::Move() {
	CheckBoundary();

	if (upPressed) {
		position.y -= speed;
		upPressed = false;
	}

	if (downPressed) {
		position.y += speed;
		downPressed = false;
	}

	if (leftPressed) {
		position.x -= speed;
		leftPressed = false;
	}

	if (rightPressed) {
		position.x += speed;
		rightPressed = false;
	}


	position += velocity;

}


Player::~Player() {
}
