#include "Cursor.h"

Cursor::~Cursor()
{
}

void Cursor::Initialize()
{
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/cursor.png", &cursor);
	textureWidth = 82;
	textureHeight = 32;
	spriteRow = 1;
	spriteCol = 2;
	spriteWidth = textureWidth / spriteCol;
	spriteHeight = textureHeight / spriteRow;
	currentFrame = 0;


	isColl = false;

	rotation = 0.0f;
	scaling = D3DXVECTOR2(1.0, 1.0);
	centre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
	mouseposition.x = MyWindowWidth / 2;
	mouseposition.y = MyWindowHeight / 2;

	animRect.top = 0;
	animRect.bottom = animRect.top + spriteHeight;
	animRect.left = currentFrame * spriteWidth;
	animRect.right = animRect.left + spriteWidth;

	mouseColRect.left = mouseposition.x;
	mouseColRect.top = mouseposition.y;
	mouseColRect.right = mouseColRect.left + spriteWidth;
	mouseColRect.bottom = mouseColRect.top + spriteHeight;
}

void Cursor::Update()
{
	if (isColl) {
		currentFrame = 1;
		isColl = false;
	}
	else {
		currentFrame = 0;
	}
	animRect.top = 0;
	animRect.bottom = animRect.top + spriteHeight;
	animRect.left = currentFrame * spriteWidth;
	animRect.right = animRect.left + spriteWidth;

	mouseColRect.left = mouseposition.x;
	mouseColRect.top = mouseposition.y;
	mouseColRect.right = mouseColRect.left + 12;
	mouseColRect.bottom = mouseColRect.top + 12;
}

void Cursor::Render()
{
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, rotation, &mouseposition);
	sprite->SetTransform(&mat);
	sprite->Draw(cursor, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

}

void Cursor::Input()
{
	dInputMouseDevice->Acquire();
	dInputMouseDevice->GetDeviceState(sizeof(mouseState), &mouseState);
	if (BUTTONDOWN(mouseState, 0)) {
		cout << "left" << endl;
		mouseLeftClick = true;
	}
	else
		mouseLeftClick = false;
	
	if (BUTTONDOWN(mouseState, 1)) {
		cout << "right" << endl;
		mouseRightClick = true;
	}
	else
		mouseRightClick = false;
	mouseposition.x += mouseState.lX;
	mouseposition.y += mouseState.lY;
}

RECT Cursor::GetCollision()
{
	return mouseColRect;
}
