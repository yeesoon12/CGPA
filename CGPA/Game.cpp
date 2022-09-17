#include "Header.h"
#include "Game.h"
Game::Game()
{
}

void Game::Initialize()
{

}

void Game::Render() {
	
}

void Game::CleanUp()
{
	texture->Release();
	texture = NULL;
}

void Game::Update(vector<Game*>*) {

}

void Game::Input() {
	
}

Game::~Game() {
	CleanUp();
}
