#include "MainMenu.h"

MainMenu::~MainMenu() {
}

void MainMenu::Initialize()
{
	
}

void MainMenu::Update()
{

}

void MainMenu::Render()
{
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	d3dDevice->BeginScene();

	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	// Render objects


	sprite->End();

	d3dDevice->EndScene();
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void MainMenu::Input() {
	// cursor->Input();
}