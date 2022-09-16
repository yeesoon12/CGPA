#include "Spaceship.h"

void Spaceship::Initialize()
{
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/spaceship.png", &texture);

	if (FAILED(hr))
	{
		cout << "Failed to load texture123456789" << endl;
	}

	textureWidth = 64;
	textureHeight = 64;
	spriteRow = 2;
	spriteCol = 2;
	spriteWidth = textureWidth / spriteCol;
	spriteHeight = textureHeight / spriteRow;

	animRect.top = currentFrame * spriteHeight;
	animRect.bottom = animRect.top + spriteHeight;
	animRect.left = currentFrame * spriteWidth;
	animRect.right = animRect.left + spriteWidth;

	colRect.top = position.y;
	colRect.bottom = colRect.top + spriteHeight;
	colRect.left = position.x;
	colRect.right = colRect.left + spriteWidth;

	scaling = D3DXVECTOR2(1.0f, 1.0f);
	centre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);

	counter = 0;

	maxFrame = 2;
}

void Spaceship::Render()
{

}

void Spaceship::Update()
{
	
}

void Spaceship::Input()
{
	
}

Spaceship::~Spaceship() {
}
