#include "PlayerShoot.h"
#include "Header.h"
void PlayerShoot::Initialization(D3DXVECTOR2 bulletPosition, float direction,int focus)
{
	//draw the player bullet
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/PlayerBullet.png", &texture);

	if (FAILED(hr)) {
		cout << "Failed to load texture" << endl;
	}
	speed = 20;
	textureWidth = 16;
	textureHeight = 16;
	isHit = false;
	fokus = focus;//focus the bullet shoot
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
	this->direction=direction;//Initialize the player bullet position to player
	position = bulletPosition;//get the bullet position


	colRect.top = position.y;
	colRect.bottom = colRect.top + spriteHeight;
	colRect.left = position.x;
	colRect.right = colRect.left + spriteWidth;


}

void PlayerShoot::Update() {
	//if the bullet is hit the collision become 0
	if (isHit) {
		colRect = { 0,0,0,0 };
	}
	//if the bullet is not hit the direct will change
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
	//draw the bullet texture
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
		}
    }
}

RECT PlayerShoot::GetColRect() {//check collision
	return colRect;
}
void PlayerShoot::SetIsHit() {//check hit the enemy
	isHit = true;
}