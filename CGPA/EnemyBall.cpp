#include "EnemyBall.h"

void EnemyBall::Initialization(float Direction, D3DXVECTOR2 position) {
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/EnemyBullet2.png", &texture);
	if (FAILED(hr)) {
		cout << "Failed to load texture" << endl;
	}

	textureWidth = 128;
	textureHeight = 32;

	spriteRow = 1;
	spriteCol = 4;
	spriteWidth = textureWidth / spriteCol;
	spriteHeight = textureHeight / spriteRow;

	reflectTime = 5;

	animRect.top = 0;
	animRect.bottom = 32;
	animRect.left = 0;
	animRect.right = 32;
	scaling = D3DXVECTOR2(1.0f, 1.0f);
	centre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
	fps = 15;
	speed = 0;
	direction = Direction;
	this->position = position;
	currentFrame = 0;
	maxFrame = 4;
	count = 0;

	colRect.top = position.y;
	colRect.bottom = colRect.top + spriteHeight;
	colRect.left = position.x;
	colRect.right = colRect.left + spriteWidth;
}

void EnemyBall::Update() {

	if (InBoundary(position)) {
		speed = 5;
		position.x += sin(direction) * speed;
		position.y += -cos(direction) * speed;

	}
	
	animRect.top = 0;
	animRect.bottom = animRect.top + spriteHeight;
	animRect.left = currentFrame* spriteWidth;
	animRect.right = animRect.left+32;
	if(count>=fps){
	currentFrame++;
	if (currentFrame >= maxFrame) {
		currentFrame = 0;
	}
	count = 0;
	}
	count++;

	
}



void EnemyBall::Render() {
	if (InBoundary(position)) {
		D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &this->position);
		sprite->SetTransform(&mat);
		sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	}
}
