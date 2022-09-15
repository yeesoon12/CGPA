#include "Enemy.h"



void Enemy::Initialize()
{
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/boss2.png", &texture);
	hr = D3DXCreateLine(d3dDevice, &line);
	if (FAILED(hr)) {
		cout << "Failed to load texture123456789" << endl;
	}
	powerUp = new PowerUp();
	magicBack = new MagicBack();
	healthBar = new HealthBar();
	bulletCom = new EnemyBulletCombination();
	attackPattern = 1;
	isUlti = false;
	line = NULL;

	
	magicBack->Initialize(position);
	healthBar->Initialize(bossHealth, bossHealthTime);
	attackPosition = 0;
	bossHealth = 100;
	stage = 1;
	bossDamage = 100;
	counter = 500;
	textureWidth = 256;
	textureHeight = 160;
	bossHealthTime = 3;
	spriteRow = 2;
	direction2 = 0;
	spriteCol = 4;
	count = 10;
	isPower = false;
	spriteWidth = textureWidth / spriteCol;
	spriteHeight = textureHeight / spriteRow;
	counters=0;
	fps = 12;
	bulletCD = 15;
	drop = true;
	enemySpeedVertical = 3.6 / 2;
	enemySpeedHorizotal = 1.5 / 2;
	currentFrame = 0;
	animRect.top = currentFrame * spriteHeight;
	animRect.bottom = animRect.top + spriteHeight;
	animRect.left = currentFrame * spriteWidth;
	animRect.right = animRect.left + spriteWidth;

	scaling = D3DXVECTOR2(1.0f, 1.2f);
	centre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
	direction = 0;
	bulletDirection = 0;
	velocity = D3DXVECTOR2(0, 0);
	position = D3DXVECTOR2((MyWindowWidth- spriteWidth) /2, -230);
	colRect.top = position.y;
	colRect.bottom = colRect.top + spriteHeight;
	colRect.left = position.x;
	colRect.right = colRect.left + spriteWidth;
	maxAttackPosition = 8;
	maxFrame = 3;
	abc = 0;
}

void Enemy::Update()
{	switch(attackPattern){
	case 1:if(bulletCD==0){
		bulletDirection++;
		for (int i = 0; i < 3; i++) {
			bulletCom->smallKnife = new EnemySmallKnife();
			bulletCom->smallKnife->Initialization(bulletDirection, position + centre - D3DXVECTOR2{ 10,0 });
			enemyBullets.push_back(bulletCom->smallKnife);
			bulletDirection += 0.2f;
		}
	bulletCD = 15;
	}
	default: {

	}
}
	for (int i = 0; i < enemyBullets.size(); i++)
	{
		enemyBullets[i]->Update();
	}


	counter--;
	counters++;
	if (counters >= fps) {
		currentFrame++;
		
		if (currentFrame == maxFrame) {
			currentFrame = 0;
		}
		
		counters = 0;
		
		if (bossHealth < 0) {
			bossHealth = 0;
			if (bossHealth == 0&& bossHealthTime==3) {
				bossHealthTime--;
				bossHealth = 200;
				ulti = new Ultimate();
				ulti->Initialization(position + centre);
				
				isUlti = true;
				drop = true;
				ulti = new Ultimate();
				ulti->Initialization(position + centre);
				enemyBullets.clear();
			}
			else if(bossHealth == 0 && bossHealthTime == 2) {
				bossHealthTime--;
				bossHealth = 400;
				drop = true;
				ulti = new Ultimate();
				ulti->Initialization(position + centre);
				enemyBullets.clear();
			}

			if (bossHealth == 0 && bossHealthTime==1) {
				bossHealthTime--;
				bossHealth = 0;
				ulti = new Ultimate();
				ulti->Initialization(position + centre);
				enemyBullets.clear();
			}
		}
		
	

		if(bossHealthTime==3){
		healthBar->Update(bossHealth, bossHealthTime);
		}
		if (bossHealthTime == 2) {
			healthBar->Update(bossHealth/2, bossHealthTime);
			stage = 2;
		}
		if (bossHealthTime == 1) {
			healthBar->Update(bossHealth/4, bossHealthTime);
			stage = 3;
		}
		if (bossHealthTime == 0) {
			healthBar->Update(0, bossHealthTime);
			stage = 3;
		}
	}

	if (isUlti) {
		ulti->Update();
	}

	if (bossHealthTime==3&&bossHealth <= 60&&drop) {
			
			powerUp->Initialization(position);
			isPower = true;
			drop = false;
		
	}
	if (bossHealthTime == 2 && bossHealth <= 120 && drop) {

		powerUp->Initialization(position);
		isPower = true;
		drop = false;

	}
	if (bossHealthTime==1&&bossHealth <= 240&&drop) {
			
			powerUp->Initialization(position);
			isPower = true;
			drop = false;
		
	}
	if (attackPosition == 0) {
		if (position.y < 120) {
			velocity.y = 3.0f;
			position += velocity;
			
		}
		if (position.y > 120) {
			position.y = 120;
			velocity = D3DXVECTOR2(0, 0);
		}
	}
	if (velocity != D3DXVECTOR2(0, 0)) {
		checkMove = MOVE;
	}

	if (velocity == D3DXVECTOR2(0, 0)){
		checkMove = STAND;
	}
	
	animRect.top = checkMove * spriteHeight;
	animRect.bottom = animRect.top + spriteHeight;
	animRect.left = currentFrame * spriteWidth;
	animRect.right = animRect.left + spriteWidth;
	colRect.top = position.y;
	colRect.bottom = colRect.top + spriteHeight;
	colRect.left = position.x-10;
	colRect.right = colRect.left + spriteWidth+20;
	
	
	if (counter == 0) {
		counter = 500;
		if (attackPosition == maxAttackPosition) {
			attackPosition=0;
		}
		attackPosition++;
	}
	
	if (attackPosition == 1) {
		int speed = 3;

		if(abc==0){
			if (direction2 <= 3.142)
				direction2 += 0.05;
			else
				abc++;
		}
		else if(abc==1)
			{
				if (direction2 >= -3.142)
					direction2 -= 0.05;
				else
					abc--;
			}
		position.x += sin(direction2) * speed;
		position.y += -cos(direction2) * speed;
		/*if (position.x > 50 ) {
			velocity.x = enemySpeedVertical;
			velocity.y = -enemySpeedHorizotal;
			position -= velocity;
		}
		if (position.x < 50) {
			position.x = 50;
			velocity = D3DXVECTOR2(0, 0);
		}*/
	}
	if (attackPosition == 2) {


		if (position.x < (MyWindowWidth - spriteWidth)/2) {
			velocity.x = -enemySpeedVertical;
			velocity.y = enemySpeedHorizotal;
			position -= velocity;
		}
		if (position.x > (MyWindowWidth - spriteWidth) / 2) {
			position.x = (MyWindowWidth - spriteWidth) / 2;
			velocity = D3DXVECTOR2(0, 0);
		}
	}

	if (attackPosition == 3) {
		if (position.x < (MyWindowWidth - spriteWidth) - 50) {
			velocity.x = -enemySpeedVertical;
			velocity.y = -enemySpeedHorizotal;
			position -= velocity;
		}
		if (position.x > (MyWindowWidth - spriteWidth) - 50) {
			velocity = D3DXVECTOR2(0, 0);
			position.x = (MyWindowWidth - spriteWidth) - 50;
		}
	}
	if (attackPosition == 4) {
		if (position.x > (MyWindowWidth - spriteWidth) / 2) {
			velocity.x = enemySpeedVertical;
			velocity.y = enemySpeedHorizotal;
			position -= velocity;
		}
		if (position.x < (MyWindowWidth - spriteWidth) / 2) {
			velocity = D3DXVECTOR2(0, 0);
			position.x = (MyWindowWidth - spriteWidth) / 2;
		}
	}

	if (attackPosition == 5) {
		if (position.x <  (MyWindowWidth-spriteWidth)-40 || position.y >30) {
			velocity.x = enemySpeedVertical;
			velocity.y = -enemySpeedHorizotal;
			position += velocity;
			if (position.x > (MyWindowWidth - spriteWidth) - 40) {
				position.x =  (MyWindowWidth - spriteWidth) - 40;
				velocity= D3DXVECTOR2(0, 0);
			}
			if (position.y < 30) {
				position.y =  30;
				velocity = D3DXVECTOR2(0, 0);
			}
		}
		
	}
	if (attackPosition == 6) {
		if (position.x > (MyWindowWidth - spriteWidth)/2 || position.y < 120) {
			velocity.x = -enemySpeedVertical;
			velocity.y = enemySpeedHorizotal;
			position += velocity;
			if (position.x < (MyWindowWidth - spriteWidth) / 2) {
				velocity = D3DXVECTOR2(0, 0);
				position.x = (MyWindowWidth - spriteWidth) / 2;
			}
			if (position.y > 120) {
				velocity = D3DXVECTOR2(0, 0);
				position.y = 120;
			}
		}

	}
	if (attackPosition == 7) {
		if (position.x > 50 || position.y > 30) {
			velocity.x = enemySpeedVertical;
			velocity.y = enemySpeedHorizotal;
			position -= velocity;
			if (position.x < 50) {
				position.x = 50;
				velocity = D3DXVECTOR2(0, 0);
			}
			if (position.y < 30) {
				position.y = 30;
				velocity = D3DXVECTOR2(0, 0);
			}
		}

	}
	if (attackPosition == 8) {
		if (position.x < (MyWindowWidth - spriteWidth) / 2 || position.y < 120) {
			velocity.x = enemySpeedVertical;
			velocity.y = enemySpeedHorizotal;
			position += velocity;
			if (position.x > (MyWindowWidth - spriteWidth) / 2) {
				velocity = D3DXVECTOR2(0, 0);
				position.x = (MyWindowWidth - spriteWidth) / 2;
			}
			if (position.y > 120) {
				velocity = D3DXVECTOR2(0, 0);
				position.y = 120;
			}
		}

	}
	if (isPower) {
		powerUp->Update();
	}
	magicBack->Update(position,stage);
	bulletCD--;
}

void Enemy::Render()
{
	magicBack->Render();
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	healthBar->Render();
	if (isPower) {
		powerUp->Render();
	}
	if (isUlti) {
		ulti->Render();
	}
	for (int i = 0; i < enemyBullets.size(); i++)
	{
		enemyBullets[i]->Render();
	}

}
RECT Enemy::GetCollisionRect() {
	return colRect;
}
void Enemy::minusHealth() {
	bossHealth -= 0.3;
}
void Enemy::clearBullet() {
	enemyBullets.clear();
}
Enemy::~Enemy()
{
}

vector<EnemyBullet*> Enemy::getBullet() {
	return enemyBullets;
}