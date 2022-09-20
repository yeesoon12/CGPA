#include "EndScene.h"
#include "Level1.h"
#include "MainMenu.h"
EndScene::~EndScene() {}

void EndScene::Initialize()
{
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/End.png", &texture);
	hr = D3DXCreateFont(d3dDevice, 75, 16, FW_BOLD, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "MV Boli", &font);
	scaling = D3DXVECTOR2(1, 1);
	centre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
	direction = 0;
	position = D3DXVECTOR2(0, 0);

	cursor = new Cursor();
	cursor->Initialize();

	textWidth = 270;
	textHeight = 65;
	textBorder = 5;

	text1Position = D3DXVECTOR2(167, 200);
	text2Position = D3DXVECTOR2(167, 350);

	text1Rect.top = text1Position.y;
	text1Rect.bottom = text1Rect.top + textHeight;
	text1Rect.left = text1Position.x;
	text1Rect.right = text1Rect.left + textWidth;

	text2Rect.top = text2Position.y;
	text2Rect.bottom = text2Rect.top + textHeight;
	text2Rect.left = text2Position.x;
	text2Rect.right = text2Rect.left + textWidth;

	text1ColRect.top = text1Position.y - textBorder;
	text1ColRect.bottom = text1Rect.top + textHeight + textBorder;
	text1ColRect.left = text1Position.x - textBorder;
	text1ColRect.right = text1Rect.left + textWidth + textBorder;

	text2Rect.top = text2Position.y;
	text2Rect.bottom = text2Rect.top + textHeight;
	text2Rect.left = text2Position.x;
	text2Rect.right = text2Rect.left + textWidth;

	text2ColRect.top = text2Position.y - textBorder;
	text2ColRect.bottom = text2Rect.top + textHeight + textBorder;
	text2ColRect.left = text2Position.x - textBorder;
	text2ColRect.right = text2Rect.left + textWidth + textBorder;
}

void EndScene::Update(vector<Game*>* game)
{
	cursor->Update();

	// Detect the cursor collide with the text
	if (CollisionDetection(text1ColRect, cursor->GetCollision()))
	{
		cursor->isColl = true;
		if (cursor->mouseLeftClick) 
		{
			game->pop_back();
			game->push_back(new Level1());
		}
	}

	if (CollisionDetection(text2ColRect, cursor->GetCollision()))
	{
		cursor->isColl = true;
		if (cursor->mouseLeftClick)
		{
			game->pop_back();
			game->pop_back();
			game->push_back(new MainMenu());
		}
	}
}

void EndScene::Render()
{
	// Background
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	d3dDevice->BeginScene();

	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMATRIX mat;
	// Draw Background
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, 0, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	font->DrawText(sprite, "Restart Game", 13, &text1Rect, 0, D3DCOLOR_XRGB(255, 50, 50));
	font->DrawText(sprite, "Back To Menu", 13, &text2Rect, 0, D3DCOLOR_XRGB(255, 50, 50));

	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	cursor->Render();
	sprite->End();

	d3dDevice->EndScene();
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void EndScene::Input()
{
	cursor->Input();
}

bool EndScene::CollisionDetection(RECT A, RECT B)
{
	if (A.top > B.bottom)
		return false;
	if (A.bottom < B.top)
		return false;
	if (A.left > B.right)
		return false;
	if (A.right < B.left)
		return false;

	return true;
}