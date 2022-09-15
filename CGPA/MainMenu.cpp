#include "MainMenu.h"

D3DXVECTOR2 lineVertices[2];

MainMenu::~MainMenu() {
}

void MainMenu::Initialize()
{
	// Background Image
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/mainMenuBG.jpg", &texture);

	scaling = D3DXVECTOR2(1, 1);
	centre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
	direction = 0;
	position = D3DXVECTOR2(0, 0);

	// Line
	hr = D3DXCreateLine(d3dDevice, &line);
	lineVertices[0] = D3DXVECTOR2(200, 200);
	lineVertices[1] = D3DXVECTOR2(400, 400);


	// Text
	hr = D3DXCreateFont(d3dDevice, 30, 0, FW_BOLD, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "MV Boli", &font);
	hr = D3DXCreateFont(d3dDevice, 20, 0, FW_BOLD, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial Narrow", &font2);

	textWidth = 200;
	textHeight = 30;

	text1Position = D3DXVECTOR2(400, 280);
	text2Position = D3DXVECTOR2(400, 320);
	text3Position = D3DXVECTOR2(400, 360);
	text4Position = D3DXVECTOR2(40, 700);

	text1Rect.top = text1Position.y;
	text1Rect.bottom = text1Rect.top + textHeight;
	text1Rect.left = text1Position.x;
	text1Rect.right = text1Rect.left + textWidth;

	text2Rect.top = text2Position.y;
	text2Rect.bottom = text2Rect.top + textHeight;
	text2Rect.left = text2Position.x;
	text2Rect.right = text2Rect.left + textWidth;

	text3Rect.top = text3Position.y;
	text3Rect.bottom = text3Rect.top + textHeight;
	text3Rect.left = text3Position.x;
	text3Rect.right = text3Rect.left + textWidth;

	text4Rect.top = text4Position.y;
	text4Rect.bottom = text4Rect.top + textHeight;
	text4Rect.left = text4Position.x;
	text4Rect.right = text4Rect.left + textWidth;
}

void MainMenu::Update()
{

}

void MainMenu::Render()
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
	
	// Draw Text
	font->DrawText(sprite, "Start Game", 10, &text1Rect, 0, D3DCOLOR_XRGB(255, 255, 255));
	font->DrawText(sprite, "Settings", 8, &text2Rect, 0, D3DCOLOR_XRGB(255, 255, 255));
	font->DrawText(sprite, "Quit Game", 9, &text3Rect, 0, D3DCOLOR_XRGB(255, 255, 255));
	font2->DrawText(sprite, "Extra Game", 10, &text4Rect, 0, D3DCOLOR_XRGB(0, 0, 0));

	line->Begin();
	line->Draw(lineVertices, 2, D3DCOLOR_XRGB(255, 255, 255));
	line->End();

	sprite->End();

	d3dDevice->EndScene();
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void MainMenu::Input() {
	// cursor->Input();
}

bool MainMenu::CollisionDetection(RECT A, RECT B)
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