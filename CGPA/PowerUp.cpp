#include "PowerUp.h"

void PowerUp::Initialization() {
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
	position = { 400,200 };
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
	position.y += speed;
	colRect.top = position.y;
	colRect.bottom = colRect.top + spriteHeight;
	colRect.left = position.x;
	colRect.right = colRect.left + spriteWidth;


}
void PowerUp::Render() {

	if(powerUpNum==1){
	D3DXMATRIX mat;
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