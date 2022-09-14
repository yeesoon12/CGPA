#include "EnemyKnife.h"

void EnemyKnife::Initialization(float Direction, D3DXVECTOR2 position) {
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/EnemyBullet7.png", &texture);
	if (FAILED(hr)) {
		cout << "Failed to load texture" << endl;
	}

	textureWidth = 32;
	textureHeight = 32;

	spriteRow = 1;
	spriteCol = 1;
	spriteWidth = textureWidth / spriteCol;
	spriteHeight = textureHeight / spriteRow;

	animRect.top = 0;
	animRect.bottom = 32;
	animRect.left = 0;
	animRect.right = 32;
	scaling = D3DXVECTOR2(1.0f, 1.0f);
	centre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);

	speed = 0; 
	direction = Direction;
	this->position = position;

	
	
	colRect.top = position.y;
	colRect.bottom = colRect.top + spriteHeight;
	colRect.left = position.x;
	colRect.right = colRect.left + spriteWidth;
}

void EnemyKnife::Update() {
	
	if (InBoundary(position)) {
		speed = 5;
		position.x += sin(direction) * speed;
		position.y += -cos(direction) * speed;

	}
	

}



void EnemyKnife::Render() {
	if (InBoundary(position)) {
		D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &this->position);
		sprite->SetTransform(&mat);
		sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	}
}
