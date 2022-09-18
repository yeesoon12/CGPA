#include "PowerUp.h"

void PowerUp::Initialization(D3DXVECTOR2 position) {
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/PowerUp.png", &texture);
	if (FAILED(hr)) {
		cout << "Failed to load texture" << endl;
	}
	powerUpNum = 1;
	textureWidth = 14;
	textureHeight = 14;
	speed = 5.0f;
	spriteRow = 1;
	spriteCol = 1;
	//Initialize power up position to enemy position
	this->position = position;
	spriteWidth = textureWidth / spriteCol;
	spriteHeight = textureHeight / spriteRow;

	animRect.top = 0;
	animRect.bottom = 14;
	animRect.left = 0;
	animRect.right = 14;
	scaling = D3DXVECTOR2(1.5f, 1.5f);
	centre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);


	colRect.top = position.y;
	colRect.bottom = colRect.top + spriteHeight;
	colRect.left = position.x;
	colRect.right = colRect.left + spriteWidth;
}

void PowerUp::Update() {
	//let power up drop down from enemy
	if(powerUpNum> 0){
	position.y += speed;
	colRect.top = position.y-10;
	colRect.bottom = colRect.top + spriteHeight+30;
	colRect.left = position.x-10;
	colRect.right = colRect.left + spriteWidth+30;
	
	}
	else if (powerUpNum = 0) {
		colRect = { 0,0,0,0 };
	}
}
void PowerUp::Render() {

	if (powerUpNum > 0) {
	D3DXMATRIX mat;
	//draw power up texture
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, 0, &position);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	}

}

RECT PowerUp::getColRect() {
	return colRect;
}

int PowerUp::getPowerUpNum() {
	return powerUpNum;
}
void PowerUp::setPowerUpNum(int num) {
	powerUpNum = num;
}