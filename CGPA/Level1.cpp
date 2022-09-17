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
	F1Pressed = false;
	F2Pressed = false; 
	F3Pressed = false;
	F4Pressed = false;
	isEnd = false;
	isDie = false;
	isWin = false;
	scaling = D3DXVECTOR2(1, 1);
	centre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
	direction = 0;
	position = D3DXVECTOR2(0,0);
	audioManager2 = new AudioManager();
	audioManager2->InitializeAudio();
	audioManager2->LoadSounds();

	bgm = 1;

	endCounter = 100;

}

void Level1::Update(vector<Game*>* game){

	if(bgm==1)
	{
		audioManager2->PlayLevel1BGM();
		bgm--;
	}
	if (isEnd ) {
		endCounter--;
		if (endCounter == 0 and isWin) {
			winScene = new WinScene();
			winScene->Initialize();
			game->push_back(winScene);
		}
		else if (endCounter == 0 and isDie) {
			endScene = new EndScene();
			endScene->Initialize();
			game->push_back(endScene);
		}
	}
		bullets = player->getBullet();
		for (int w = 0; w < bullets.size(); w++) {
			bullet = bullets[w];
			if (CollisionDetection(bullet->GetColRect(), enemy->GetCollisionRect())) {
				enemy->minusHealth();
				bullet->SetIsHit();
			}
		}

	if (CollisionDetection(player->getColRect(), enemy->powerUp->getColRect())) {
		if(enemy->powerUp->getPowerUpNum()>0){
			player->addBullet(2);
		enemy->powerUp->setPowerUpNum(0);
		audioManager2->PlayPowerUp();
		
		}
	}

	enemyBullets = enemy->getBullet();
	for (int i = 0; i < enemyBullets.size(); i++) {
		if (CollisionDetection(player->getColRect(), enemyBullets[i]->GetColRect())) {
			if(j<0){
			audioManager2->PlayDeathSound();
			player->minusHealth();
			isEnd = true;
			isDie = true;
			j = 9999;
			}
		}
	}
	if (F1Pressed) {
		if (counter <= 0) {
			
			audioManager2->editBGM(0.1);
			counter = 5;
			F1Pressed = false;
		}

	}
	if (F2Pressed) {
		if (counter <= 0) {
			
			audioManager2->editBGM(-0.1);
			counter = 5;
			F2Pressed = false;
		}

	}
	if (F3Pressed) {
		if (counter <= 0) {
			audioManager2->editSoundEffect(0.1);
		
			counter = 5;
			F3Pressed = false;
		}

	}
	if (F4Pressed) {
		if (counter <= 0) {
			audioManager2->editSoundEffect(-0.1);
			
			counter = 5;
			F4Pressed = false;
		}

	}
	player->Update();
	enemy->Update();
	audioManager2->UpdateSound();
	if (player->IsUlti()) {
		enemy->clearBullet();
	}
	bossHealth = enemy->GetHealthTime();
	if (bossHealth == 0)
	{
		audioManager->~AudioManager();
		audioManager2->~AudioManager();
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

	
	player->Render();
	enemy->Render();

	sprite->End();

	d3dDevice->EndScene();
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void Level1::Input(){
	enemy->Input();
	player->Input();
	dInputKeyboardDevice->Acquire();
	dInputKeyboardDevice->GetDeviceState(256, diKeys);
	if (diKeys[DIK_F1] & 0x80) {
		F1Pressed = true;
		cout << "abc" << endl;
	}
	if (diKeys[DIK_F2] & 0x80) {
		F2Pressed = true;
	}
	if (diKeys[DIK_F3] & 0x80) {
		F3Pressed = true;
		cout << "abc" << endl;
	}
	if (diKeys[DIK_F4] & 0x80) {
		F4Pressed = true;
	}
}

bool Level1::CollisionDetection(RECT A, RECT B)
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