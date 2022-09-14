#include "Level1.h"

Level1::~Level1() {
}

void Level1::Initialize()
{
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/BackGround.png", &texture);
	player = new Player();
	player -> Initialize();
	powerUp = new PowerUp();
	powerUp->Initialization();
	enemy = new Enemy();
	direction2 = 2.f;
	i = 0;
	j = 0;
	skill = new EnemyBulletCombination();

	scaling = D3DXVECTOR2(1, 1);
	centre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
	direction = 0;
	position = D3DXVECTOR2(0,0);
	AudioManager* audioManager = new AudioManager();
	audioManager->InitializeAudio();
	audioManager->LoadSounds();
	audioManager->PlayLevel1BGM();
}

void Level1::Update() {
	if(j<50){
		
	if (i == 40) {
	
		skill = new EnemyBulletCombination();
	
		skill->Initialization((float) rand(),D3DXVECTOR2{ MyWindowWidth / 2,200 },1);
		bulletcombo1.push_back(skill->getBulletPattern1());
		for(int i=0; i<3;i++){
		skill = new EnemyBulletCombination();
		skill->Initialization(direction2, D3DXVECTOR2{ MyWindowWidth / 2,200 },3);
		bulletcombo1.push_back(skill->getBulletPattern3());
		direction2 += 1;
		}
		i = 0;
	
		j++;
		direction2 -=2.9f;
	}
	}
	for (int i = 0; i < bulletcombo1.size(); i++) {

		currentPattern = bulletcombo1[i];
		for (int i = 0; i < currentPattern.size(); i++)
		currentPattern[i]->Update();

	}
	player->Update();
	powerUp->Update();
	enemy->Update();
	skill->Update();
	if(powerUp->getPowerUpNum()==1){
	if (CollisionDetection(player->getColRect(), powerUp->getColRect()))
	{
		player->addBullet(2);
		powerUp->setPowerUpNum(0);
		
	}
	}
	if (player->IsUlti()) {
		clearBullet();
	}
	i++;
}     
void Level1::clearBullet() {
	bulletcombo1.clear();
}

void Level1::Render() {
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	d3dDevice->BeginScene();

	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, 0, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	for (int i = 0; i < bulletcombo1.size(); i++) {

		currentPattern = bulletcombo1[i];
		for (int i = 0; i < currentPattern.size(); i++)
			currentPattern[i]->Render();
		

	}
	powerUp->Render();
	player->Render();
	enemy->Render();

	sprite->End();

	d3dDevice->EndScene();
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void Level1::Input() {
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