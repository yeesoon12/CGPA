#include "MagicBack.h"

MagicBack::~MagicBack()
{
}

void MagicBack::Initialize(D3DXVECTOR2 magicBackPosition)
{
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/CirleBack.png", &texture);

	if (FAILED(hr)) {
		cout << "Failed to load texture" << endl;
	}
	spriteWidth = 128;
	spriteHeight = 128;
	scaling = D3DXVECTOR2(1, 1);
	centre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
	direction=0;
	position = magicBackPosition; // initialize the position of magic back to the center enemy position
	red = 0;
	animRect.top = currentFrame * spriteHeight;
	animRect.bottom = animRect.top + spriteHeight;
	animRect.left = currentFrame * spriteWidth;
	animRect.right = animRect.left + spriteWidth;
}

void MagicBack::Update(D3DXVECTOR2 playerPosition,int stage)
{
	position = playerPosition + D3DXVECTOR2(-32,-15); // keep updating the position behind the boss
	direction += 0.05f; // let the magic back turning behind the boss
	red = stage * 85; // render the red color according to the boss life

}

void MagicBack::Render()
{
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(red, 255, 255));
}
