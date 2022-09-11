#include "Level1.h"

Level1::~Level1() {
}

void Level1::Initialize()
{
	player = new Player();
	enemy = new Enemy();
}

void Level1::Update() {
	
}

void Level1::Render() {
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	d3dDevice->BeginScene();

	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	// render game objects
	player->Render();
	enemy->Render();

	sprite->End();

	d3dDevice->EndScene();
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void Level1::Input() {
	player->Input();
}