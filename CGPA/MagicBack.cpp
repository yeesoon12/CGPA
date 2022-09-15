#include "MagicBack.h"

MagicBack::~MagicBack()
{
}

void MagicBack::Initialize(D3DXVECTOR2 magicBackPosition)
{
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/CirleBack.png", &texture);

	if (FAILED(hr)) {
		cout << "Failed to load texture123456789" << endl;
	}
	spriteWidth = 128;
	spriteHeight = 128;
	scaling = D3DXVECTOR2(1, 1);
	centre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
	direction=0;
	position = magicBackPosition;
	red = 0;
	animRect.top = currentFrame * spriteHeight;
	animRect.bottom = animRect.top + spriteHeight;
	animRect.left = currentFrame * spriteWidth;
	animRect.right = animRect.left + spriteWidth;
}

void MagicBack::Update(D3DXVECTOR2 playerPosition,int stage)
{
	position = playerPosition + D3DXVECTOR2(-32,-15);
	direction += 0.05f;
	red = stage * 85;

}

void MagicBack::Render()
{
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(red, 255, 255));
}
