#include "PlayerShoot.h"
#include "Header.h"
void PlayerShoot::Initialization(D3DXVECTOR2 bulletPosition, int bulletNum,int focus)
{
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/PlayerBullet.png", &texture);

	if (FAILED(hr)) {
		cout << "Failed to load texture" << endl;
	}
	speed = { 0,-17.5 };
	speed2 = { 2.5,-17.5 };
	speed3 = { -2.5,-17.5 };
	speed4 = { 5,-17.5 };
	speed5 = { -5,-17.5 };
	textureWidth = 16;
	textureHeight = 16;
	
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
	direction = 0;
	position = bulletPosition;
	position2 = bulletPosition;
	position3 = bulletPosition;
	position4 = bulletPosition;
	position5 = bulletPosition;
	bulletAmount = bulletNum;

	colRect.top = position.y;
	colRect.bottom = colRect.top + spriteHeight;
	colRect.left = position.x;
	colRect.right = colRect.left + spriteWidth;


}

void PlayerShoot::Update() {
	if (fokus == 1) {
		speed2.x = 1.f;
		speed3.x = -1.f;
		speed4.x = 2.f;
		speed5.x = -2.f;
	}
	position += speed;
	position2 += speed2;
	position3 += speed3;
	position4 += speed4;
	position5 += speed5;

}
void PlayerShoot::Render() {
	D3DXMATRIX mat;
	
	if(position.y>-10){
	
		if(bulletAmount==1){
		
			D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position);
			sprite->SetTransform(&mat);
	sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
		}
		else if (bulletAmount == 3) {
			
			D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position);
			sprite->SetTransform(&mat);
			sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
			
			D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position2);
			sprite->SetTransform(&mat);
			sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
			
			D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position3);
			sprite->SetTransform(&mat);
			sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
		}
		else if (bulletAmount == 5) {
			
			D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position);
			sprite->SetTransform(&mat);
			sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

			D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position2);
			sprite->SetTransform(&mat);
			sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

			D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position3);
			sprite->SetTransform(&mat);

			sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
			D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position4);
			sprite->SetTransform(&mat);

			sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
			D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position5);
			sprite->SetTransform(&mat);
			sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
		}
	}
}