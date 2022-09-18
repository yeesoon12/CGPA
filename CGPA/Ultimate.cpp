#include "Ultimate.h"

void Ultimate::Initialization(D3DXVECTOR2 playerPosition) {
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/Ultimate.png", &texture);
	if (FAILED(hr)) {
		cout << "Failed to load texture" << endl;
	}

	textureWidth = 32;
	textureHeight = 32;
	//to get the player position
	position = playerPosition;
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


	colRect.top = position.y;
	colRect.bottom = colRect.top + spriteHeight;
	colRect.left = position.x;
	colRect.right = colRect.left + spriteWidth;
}

void Ultimate::Update() {
	//to let texture more bigger
	scaling+= D3DXVECTOR2(5,5);
	
}
void Ultimate::Render() {
	D3DXMATRIX mat;
	//draw the ultimate texture 
	D3DXMatrixTransformation2D(&mat, &centre, 0.0, &scaling, &centre, direction, &position);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(100, 100, 100));



}