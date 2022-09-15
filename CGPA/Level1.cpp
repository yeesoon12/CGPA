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

	
	scaling = D3DXVECTOR2(1, 1);
	centre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
	direction = 0;
	position = D3DXVECTOR2(0,0);
	audioManager2 = new AudioManager();
	audioManager2->InitializeAudio();
	audioManager2->LoadSounds();
	AudioManager* audioManager = new AudioManager();
	audioManager->InitializeAudio();
	audioManager->LoadSounds();
	audioManager->PlayLevel1BGM();


}

void Level1::Update() {

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
		
		}
	}

	enemyBullets = enemy->getBullet();
	for (int i = 0; i < enemyBullets.size(); i++) {
		if (CollisionDetection(player->getColRect(), enemyBullets[i]->GetColRect())) {
			if(j<0){
			audioManager2->PlayDeathSound();
			player->minusHealth();
			j = 999;
			}
		}
	}
	player->Update();
	enemy->Update();

	if (player->IsUlti()) {
		enemy->clearBullet();
	}

	bulletCD++;
	j--;
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
	player->Input();
	
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