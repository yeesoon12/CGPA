#include "PlayerShoot.h"
#include "Header.h"
void PlayerShoot::Initialization(D3DXVECTOR2 bulletPosition, float direction,int focus)
{
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/PlayerBullet.png", &texture);

	if (FAILED(hr)) {
		cout << "Failed to load texture" << endl;
	}
	speed = 20;
	textureWidth = 16;
	textureHeight = 16;
	isHit = false;
	fokus = focus;
	spriteRow = 1;
	spriteCol = 1;
	spriteWidth = textureWidth / spriteCol;
	spriteHeight = textureHeight / spriteRow;

	animRect.top = 0;
	animRect.bottom = 16;
	animRect.left = 0;
	animRect.right = 16;

	scaling = D3DXVECTOR2(2, 2);
	centre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
	this->direction=direction;
	position = bulletPosition;


	colRect.top = position.y;
	colRect.bottom = colRect.top + spriteHeight;
	colRect.left = position.x;
	colRect.right = colRect.left + spriteWidth;


}

void PlayerShoot::Update() {
	if (isHit) {
		colRect = { 0,0,0,0 };
	}
	if(!isHit){
	if (fokus == 1) {
		direction *= 0.90;
	}
	position.x += sin(direction) * speed;
	position.y += -cos(direction) * speed;
	colRect.top = position.y;
	colRect.bottom = colRect.top + spriteHeight;
	colRect.left = position.x;
	colRect.right = colRect.left + spriteWidth;
	}
}
void PlayerShoot::Render() {
	if (!isHit) {
	
	if(position.y>-10){
	
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
		}
    }
}

RECT PlayerShoot::GetColRect() {
	return colRect;
}
void PlayerShoot::SetIsHit() {
	isHit = true;
}