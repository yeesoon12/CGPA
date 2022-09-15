#include "EnemySmallKnife.h"

void EnemySmallKnife::Initialization(float Direction, D3DXVECTOR2 position) {
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/EnemyBullet8.png", &texture);
	if (FAILED(hr)) {
		cout << "Failed to load texture" << endl;
	}

	textureWidth = 16;
	textureHeight = 16;

	spriteRow = 1;
	spriteCol = 1;
	spriteWidth = textureWidth / spriteCol;
	spriteHeight = textureHeight / spriteRow;

	animRect.top = 0;
	animRect.bottom = 16;
	animRect.left = 0;
	animRect.right = 16;
	scaling = D3DXVECTOR2(1.5f, 1.5f);
	centre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);

	speed = 0;
	direction = Direction;
	this->position = position;



	colRect.top = position.y+10;
	colRect.bottom = colRect.top + spriteHeight-20;
	colRect.left = position.x+10;
	colRect.right = colRect.left + spriteWidth-20;
}

void EnemySmallKnife::Update() {

	if (InBoundary(position)) {
		speed = 5;

		position.x += sin(direction) * speed;
		position.y += -cos(direction) * speed;


	}
	colRect.top = position.y + 5;
	colRect.bottom = colRect.top + spriteHeight - 10;
	colRect.left = position.x + 5;
	colRect.right = colRect.left + spriteWidth - 10;
	
	

}



void EnemySmallKnife::Render() {
	if (InBoundary(position)) {
		D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &this->position);
		sprite->SetTransform(&mat);
		sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	}
}
