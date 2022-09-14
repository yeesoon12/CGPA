#include "Header.h"
#include "Game.h"
Game::Game()
{
}

void Game::Initialize()
{
}

void Game::Render() {
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	//	Begin the scene
	d3dDevice->BeginScene();

	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	//	Sprite rendering. Study the documentation.
	//sprite->Draw(texture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	//sprite->Draw(texture, &playerRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	//sprite->Draw(texture, &playerRect, NULL, &position, D3DCOLOR_XRGB(255, 255, 255));

	//sprite->Draw(texture, &numbersRect, NULL, &numbersPosition, D3DCOLOR_XRGB(255, 255, 255));

	sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	//font->DrawText(sprite, "Hello World!", -1, &textRect, 0, D3DCOLOR_XRGB(255, 255, 255));

	//	End sprite drawing
	sprite->End();

	//line->Begin();
	//line->Draw(hourHandVectices, sizeof(hourHandVectices)/sizeof(D3DXVECTOR2), D3DCOLOR_XRGB(69, 42, 111));
	//line->End();

	//	End the scene
	d3dDevice->EndScene();

	//	Present the back buffer to screen
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void Game::CleanUp()
{
	texture->Release();
	texture = NULL;
}

void Game::Update(int FrameToUpdate) {

}

void Game::Input() {

}

Game::~Game() {
	CleanUp();
}
