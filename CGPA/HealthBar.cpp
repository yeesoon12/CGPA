#include "HealthBar.h"



void HealthBar::Initialize(int bossHealth1, int bossHealthTime)
{
	barTexture=NULL;
	font = NULL;
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/HP_Box.png", &texture);
	 hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/HP_Bar.png", &barTexture);
	 hr = D3DXCreateFont(d3dDevice, 34, 0, FW_BOLD, 1, false,
		 DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		 DEFAULT_PITCH | FF_DONTCARE, "Bradley Hand ITC", &font); //set the font attribute like style,size etc.
	if (FAILED(hr)) {
		cout << "Failed to load texture" << endl;
	}

	spriteWidth = 500;
	spriteHeight = 30;
	scaling = D3DXVECTOR2(1, 1);
	barScaling = D3DXVECTOR2(1, 1);
	centre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
	direction = 0;
	position = D3DXVECTOR2((MyWindowWidth - spriteWidth) / 2,5);
	bossHealthTimes = bossHealthTime;
	bossHealths = bossHealth1;
	animRect.top = currentFrame * spriteHeight;
	animRect.bottom = animRect.top + spriteHeight;
	animRect.left = currentFrame * spriteWidth;
	animRect.right = animRect.left + spriteWidth;

	textRect.top = 10;
	textRect.bottom = textRect.top + spriteHeight;
	textRect.left =  445;
	textRect.right = textRect.left + spriteWidth;
	
}

void HealthBar::Update(float bossHealth1,int bossHealthTime) // pass how many life the boss still have and how much health left
{
	bossHealthTimes = bossHealthTime;
	cout << barScaling.x << endl;
	barScaling.x = (float)bossHealth1/100; 
	if (barScaling.x < 0) {// set the horizontal scaling cant be less than 0
		barScaling.x = 0;
		if (barScaling.x == 0) {
			barScaling = D3DXVECTOR2(1, 1);  // if bossHealth = 0 , reset the hp to full
		}
	}
	if (bossHealthTimes == 0) {
		barScaling.x = 0;// if boss life is 0, health will not be render
	}
	
	animRect.top = currentFrame * spriteHeight; //update animation 
	animRect.bottom = animRect.top + spriteHeight;
	animRect.left = currentFrame * spriteWidth;
	animRect.right = animRect.left + spriteWidth;
}

void HealthBar::Render()
{
	D3DXMATRIX mat;
	if (bossHealthTimes >0) {
		D3DXMatrixTransformation2D(&mat, NULL, 0.0, &barScaling, &centre, direction, &position);
		sprite->SetTransform(&mat);
		sprite->Draw(barTexture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 0, 0));
	}

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	switch (bossHealthTimes) { //render how much life boss still have
	case 3:
		font->DrawText(sprite, "x3", 2, &textRect, 0, D3DCOLOR_XRGB(255, 127, 80));
		break;
	case 2:
		font->DrawText(sprite, "x2", 2, &textRect, 0, D3DCOLOR_XRGB(0, 0, 255));
		break;
	case 1:
		font->DrawText(sprite, "x1", 2, &textRect, 0, D3DCOLOR_XRGB(255, 0, 0));
		break;
	case 0:
		font->DrawText(sprite, "x0", 2, &textRect, 0, D3DCOLOR_XRGB(255,255, 0));
		break;

	}
}

HealthBar::~HealthBar()
{
}