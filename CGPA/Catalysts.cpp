#include "Catalysts.h"

void Catalysts::Initialization(D3DXVECTOR2 catalystsPosition) {
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/Catalysts.png", &texture);
		if (FAILED(hr)) {
			cout << "Failed to load texture" << endl;
		}

	textureWidth = 15;
	textureHeight = 15;

	position1 = catalystsPosition + D3DXVECTOR2(-27, 10);
	position2 = catalystsPosition + D3DXVECTOR2(+46, 10);
	spriteRow = 1;
	spriteCol = 1;
	spriteWidth = textureWidth / spriteCol;
	spriteHeight = textureHeight / spriteRow;

	animRect.top = 0;
	animRect.bottom = 15;
	animRect.left = 0;
	animRect.right = 15;
	scaling = D3DXVECTOR2(1.0f, 1.0f);
	scaling2 = D3DXVECTOR2(1.0f, 1.0f);
	centre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
	

	colRect.top = position.y;
	colRect.bottom = colRect.top + spriteHeight;
	colRect.left = position.x;
	colRect.right = colRect.left + spriteWidth;
}

void Catalysts::Update(D3DXVECTOR2 catalystsPosition, int focus) {
	fokus = focus;
	//If player didnt press C to focus their bullet, move catalysts to the specific position
	if(focus==0){
		if (position1.x != catalystsPosition.x - 27)
			position1.x = position1.x - 10;

		if (position1.x <= catalystsPosition.x - 27)
			position1.x = catalystsPosition.x - 27;

		if (position1.y != catalystsPosition.y + 10)
			position1.y = position1.y + 15;

		if (position1.y >= catalystsPosition.y + 10)
			position1.y = catalystsPosition.y + 10;

		if (position2.x != catalystsPosition.x + 46)
			position2.x = position2.x - 10;

		if (position2.x <= catalystsPosition.x + 46)
			position2.x = catalystsPosition.x + 46;

		if (position2.y != catalystsPosition.y + 10)
			position2.y = position2.y + 27.5;

		if (position2.y >= catalystsPosition.y + 10)
			position2.y = catalystsPosition.y + 10;
		
	}
	
	//If player press C to focus their bullet, move catalysts to the specific position
	else if (focus == 1) {
		if(position1 != catalystsPosition + D3DXVECTOR2(-7, -30)){
			position1 += D3DXVECTOR2{ 7.5,-12.5 };
			if (position1.x >= catalystsPosition.x - 7)
				position1.x = catalystsPosition.x - 10;
			if (position1.y <= catalystsPosition.y - 30)
				position1.y = catalystsPosition.y - 30;
			
		}
		if (position2 != catalystsPosition + D3DXVECTOR2(+26, -30)) {
			position2 += D3DXVECTOR2{ -7.5,-12.5 };
			if (position2.x <= catalystsPosition.x +26)
				position2.x = catalystsPosition.x +30;
			if (position2.y <= catalystsPosition.y - 30)
				position2.y = catalystsPosition.y - 30;

		}
	
	}
	//make the catalysts turn around the player
	direction += 0.075f;
	direction2 -= 0.075f;
	
}
void Catalysts::Render() {
			D3DXMATRIX mat;
			D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position1);
			sprite->SetTransform(&mat);
			sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
			D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling2, &centre, direction2, &position2);
			sprite->SetTransform(&mat);
			sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	
	
}