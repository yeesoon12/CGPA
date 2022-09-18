#include "Level1.h"

Level1::~Level1() {
}

void Level1::Initialize()
{
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/BackGround.png", &texture);
	player = new Player();
	player -> Initialize();
	enemy = new Enemy();
	direction2 = 2.f;
	bulletCD = 0;
	j = 0;
	counter = 0;

	// Set Key Press to false by default
	F1Pressed = false;
	F2Pressed = false; 
	F3Pressed = false;
	F4Pressed = false;

	isEnd = false;
	isDie = false;
	isWin = false;

	// Background Initialize
	scaling = D3DXVECTOR2(1, 1);
	centre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
	direction = 0;

	audioManager = new AudioManager();
	audioManager->InitializeAudio();
	audioManager->LoadSounds();

	position = D3DXVECTOR2(0,0);
	audioManager2 = new AudioManager();
	audioManager2->InitializeAudio();
	audioManager2->LoadSounds();

	// Use to on/off bgm
	bgm = 1;

	endCounter = 100;
	isStart=true;
}

void Level1::Update(vector<Game*>* game){
	
		if (bgm == 1)
		{
			audioManager->PlayLevel1BGM();
			bgm--;
		}
		if (isEnd)
		{
			endCounter--;
			audioManager->stopBackGround2();
			if (endCounter == 0 and isWin) { // if game is end and player is win, push win scene to the vector
				winScene = new WinScene();
				winScene->Initialize();
				game->pop_back();
				game->push_back(winScene);
			}
			else if (endCounter == 0 and isDie) { // if game is end and player is die, push end scene to the vector
				endScene = new EndScene();
				endScene->Initialize();
				game->pop_back();
				game->push_back(endScene);
			}
		}
		bullets = player->getBullet();
		for (int w = 0; w < bullets.size(); w++) { // check the enemy is collide with player's bullets
			bullet = bullets[w];
			if (CollisionDetection(bullet->GetColRect(), enemy->GetCollisionRect())) {
				enemy->minusHealth();// minus enemy health 
				bullet->SetIsHit(); //bullet is hit
			}
		}

		if (CollisionDetection(player->getColRect(), enemy->powerUp->getColRect())) { // check the player is collide with power up
			if (enemy->powerUp->getPowerUpNum() > 0) {
				player->addBullet(2); // add the bullet by 2
				enemy->powerUp->setPowerUpNum(0); 
				audioManager2->PlayPowerUp(); // player power up sound effect

			}
		}

		enemyBullets = enemy->getBullet();
		for (int i = 0; i < enemyBullets.size(); i++) {
			if (CollisionDetection(player->getColRect(), enemyBullets[i]->GetColRect())) {
				if (j < 0) {
					audioManager->PlayDeathSound(); // play death sound effect
					player->minusHealth(); // minus the player health by 1
					isEnd = true;
					isDie = true;
					j = 9999;
				}
			}
		}

		if (F1Pressed) {
			if (counter <= 0) {

				audioManager2->editBGM(0.1); // increase the volume of bgm
				counter = 5;
				F1Pressed = false;
			}
		}
		if (F2Pressed) {
			if (counter <= 0) {

				audioManager2->editBGM(-0.1); // decrease the volume of bgm
				counter = 5;
				F2Pressed = false;
			}
		}
		if (F3Pressed) {
			if (counter <= 0) {
				audioManager2->editSoundEffect(0.1); // increase the volume of sound effect

				counter = 5;
				F3Pressed = false;
			}
		}
		if (F4Pressed) {
			if (counter <= 0) {
				audioManager2->editSoundEffect(-0.1); // decrease the volume of sound effect

				counter = 5;
				F4Pressed = false;
			}
		}
		player->Update();
		enemy->Update();
		audioManager2->UpdateSound();
		if (player->IsUlti()) {
			enemy->clearBullet(); // if player press ulti, clear all the bullet on screen
		}
		bossHealth = enemy->GetHealthTime();
		if (bossHealth == 0) // when boss die, game end and win
		{
			isEnd = true;
			isWin = true;
		}
		bulletCD++;
		j--;
		counter--;
}
   
void Level1::Render() {
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	d3dDevice->BeginScene();

	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, 0, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	// Make player and enemy to render
	player->Render();
	enemy->Render();

	sprite->End();

	d3dDevice->EndScene();
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void Level1::Input(){
	// Ask enemy and player for input
	enemy->Input();
	player->Input();

	dInputKeyboardDevice->Acquire();
	dInputKeyboardDevice->GetDeviceState(256, diKeys);
	if (diKeys[DIK_F1] & 0x80) {
		F1Pressed = true;
	}
	if (diKeys[DIK_F2] & 0x80) {
		F2Pressed = true;
	}
	if (diKeys[DIK_F3] & 0x80) {
		F3Pressed = true;
	}
	if (diKeys[DIK_F4] & 0x80) {
		F4Pressed = true;
	}
}

bool Level1::CollisionDetection(RECT A, RECT B) // collision detection of two object with rect collision
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
