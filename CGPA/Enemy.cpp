#include "Enemy.h"



void Enemy::Initialize()
{
	//display enemy texture
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/boss2.png", &texture);
	hr = D3DXCreateLine(d3dDevice, &line);//draw line
	if (FAILED(hr)) {//fail to laod texture
		cout << "Failed to load texture" << endl;
	}
	//audio enemy
	powerUp = new PowerUp();
	magicBack = new MagicBack();
	healthBar = new HealthBar();
	bulletCom = new EnemyBulletCombination();
	attackPattern = 0;
	isUlti = false;
	line = NULL;
	//EnemyBulletInitialize
	smallKnifeDirection = 0;
	knifeDirection = 0;
	
	magicBack->Initialize(position);
	healthBar->Initialize(bossHealth, bossHealthTime);
	attackPosition = 0;
	bossHealth = 100;
	stage = 1;
	bossDamage = 100;
	counter = 150;
	textureWidth = 256;
	textureHeight = 160;
	bossHealthTime = 3;
	spriteRow = 2;
	direction2 = 0;
	spriteCol = 4;
	count = 10;
	counter2 = 0;
	F3Pressed = false;
	F4Pressed = false;
	isPower = false;
	spriteWidth = textureWidth / spriteCol;
	spriteHeight = textureHeight / spriteRow;
	counters=0;
	speed = 0;
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
	bulletCD2=15;
	scaling = D3DXVECTOR2(1.0f, 1.2f);
	centre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
	direction = 0;
	pattern1Counter = 0;
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
{   
	//enemy walk position
	switch (attackPattern) {
	case 1: {
		if(bossHealthTime==3){
		if (bulletCD <= 0) {//to limit the bulllet amount
			smallKnifeDirection = (rand()%1700+2000);
			smallKnifeDirection /= 1000;
			knifeDirection = rand();
			for (int i = 0; i < 4; i++) {//set different types of bullet
				bulletCom->smallKnife = new EnemySmallKnife();
				bulletCom->smallKnife->Initialization(smallKnifeDirection, position + centre - D3DXVECTOR2{ 10,0 }, 7,0);
				enemyBullets.push_back(bulletCom->smallKnife);
				smallKnifeDirection += 0.08f;
				
			
				bulletCD = 20;
			}
			audioManager->PlayEnemyBulletShoot2();
		}
		if (bulletCD2 <= 0) {
			for (int i = 0; i < 40; i++) {//set different types of bullet
				bulletCom->knife = new EnemyKnife();
				bulletCom->knife->Initialization(knifeDirection, position + centre - D3DXVECTOR2{ 10,0 }, 10, 0);
				enemyBullets.push_back(bulletCom->knife);
				knifeDirection += 0.1571;
				bulletCD2 = 20;
			}
			audioManager->PlayEnemyBulletShoot1();;
		}
	
	}
		else if (bossHealthTime == 2) {
		
			float positionX2 = (rand() % 50) +180;
			if (bulletCD <= 0) {//set different types of bullet
				for (int i = 0; i < 11; i++) {
					bulletCom->smallKnife = new EnemySmallKnife();
					bulletCom->smallKnife->Initialization(3.142, position + centre - D3DXVECTOR2{ positionX2,-10 }, 7,0);
					enemyBullets.push_back(bulletCom->smallKnife);				
					smallKnifeDirection += 0.08f;
					bulletCD = 30;
					positionX2 -=40;
				}
				audioManager->PlayEnemyBulletShoot2();
			}
		}
		else if (bossHealthTime == 1) {

			float positionX2 = (rand() % 50) + 180;
			if (bulletCD <= 0) {
				for (int i = 0; i < 11; i++) {//set different types of bullet
					float directionInc = rand() % 60+(- 30);
					directionInc /= 1000;
					bulletCom->smallKnife = new EnemySmallKnife();
					bulletCom->smallKnife->Initialization(3.142, position + centre - D3DXVECTOR2{ positionX2,-10 }, 10,directionInc);
					enemyBullets.push_back(bulletCom->smallKnife);				
					smallKnifeDirection += 0.08f;
					bulletCD = 20;
					positionX2 -= 40;
				}
				audioManager->PlayEnemyBulletShoot2();
			}
		}
		break;
	}
	case 2: {
		if (bossHealthTime == 3){

			if (bulletCD2 == 0) {

				for (int i = 0; i < 6; i++) {//set different types of bullet
					knifeDirection = (rand() % 2200 + 2000);
					knifeDirection /= 1000;
					bulletCom->knife = new EnemyKnife();
					bulletCom->knife->Initialization(knifeDirection, position + centre - D3DXVECTOR2{ 10,0 }, rand() % 8 + 6, 0);
					enemyBullets.push_back(bulletCom->knife);	
					bulletCD2 = 5;
				}
				audioManager->PlayEnemyBulletShoot1();
			}
	}
		else if (bossHealthTime == 2) {
			if (bulletCD2 <= 0) {
				for (int i = 0; i < 15; i++) {//set different types of bullet
					bulletCom->knife = new EnemyKnife();
					bulletCom->knife->Initialization(knifeDirection, position + centre - D3DXVECTOR2{ 10,0 }, 8, 2);
					enemyBullets.push_back(bulletCom->knife);
					knifeDirection += 0.419;	
					bulletCD2 = 20;
				}
				audioManager->PlayEnemyBulletShoot1();
			}
		}
		else if (bossHealthTime == 1) {
			float positionX2 = (rand() % 50) + 180;
			if (bulletCD <= 0) {
				for (int i = 0; i < 11; i++) {//set different types of bullet
					float directionInc = rand() % 60 + (-30);
					directionInc /= 1000;
					bulletCom->smallKnife = new EnemySmallKnife();
					bulletCom->smallKnife->Initialization(3.142, position + centre - D3DXVECTOR2{ positionX2,-10 }, 10, directionInc);
					enemyBullets.push_back(bulletCom->smallKnife);		
					smallKnifeDirection += 0.08f;
					bulletCD = 20;
					positionX2 -= 40;
				}
				audioManager->PlayEnemyBulletShoot2();
			}
			if (bulletCD2 <= 0) {

				for (int i = 0; i < 6; i++) {//set different types of bullet
					knifeDirection = (rand() % 6148);
					knifeDirection /= 1000;
					bulletCom->knife = new EnemyKnife();
					bulletCom->knife->Initialization(knifeDirection, position + centre - D3DXVECTOR2{ 10,0 }, rand() % 8 + 6, 2);
					enemyBullets.push_back(bulletCom->knife);				
					bulletCD2 = 5;
				}
				audioManager->PlayEnemyBulletShoot1();
			}
		}
		break;
	}
	default: {

	}
	}
	//update the bullet
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
			//limit the ultimate of the player can use for one level
			if (bossHealth == 0&& bossHealthTime==3) {
				bossHealthTime--;
				bossHealth = 200;
				attackPattern = 1;
				ulti = new Ultimate();
				ulti->Initialization(position + centre);
				audioManager->PlayExploSound();
				
				isUlti = true;
				drop = true;
				ulti = new Ultimate();
				ulti->Initialization(position + centre);
				enemyBullets.clear();
				attackPattern = 1;
			}
			else if(bossHealth == 0 && bossHealthTime == 2) {
				bossHealthTime--;
				bossHealth = 400;
				drop = true;
				ulti = new Ultimate();
				attackPattern = 1;
				audioManager->PlayExploSound();
				ulti->Initialization(position + centre);
				enemyBullets.clear();
			}

			if (bossHealth == 0 && bossHealthTime==1) {
				bossHealthTime--;
				bossHealth = 0;
				attackPattern = 0;
				ulti = new Ultimate();
				audioManager->PlayExploSound();
				ulti->Initialization(position + centre);
				enemyBullets.clear();
			}
		}
		
	
		//set the hp of the boss to health bar
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
	//set the boss if boss hp drop
	if (bossHealthTime==3&&bossHealth <= 60&&drop) {
			
			powerUp->Initialization(position);
			attackPattern = 2;
			audioManager->PlayEvoSound();
			isPower = true;
			drop = false;
		
	}
	if (bossHealthTime == 2 && bossHealth <= 120 && drop) {

		powerUp->Initialization(position);
		isPower = true;
		attackPattern = 2;
		audioManager->PlayEvoSound();
		drop = false;

	}
	if (bossHealthTime==1&&bossHealth <= 240&&drop) {
			
			powerUp->Initialization(position);
			isPower = true;
			attackPattern = 2;
			audioManager->PlayEvoSound();
			drop = false;
		
	}
	//let boss move down from up
	if (attackPosition == 0) {
		if (position.y < 120) {
			velocity.y = 3.0f;
			position += velocity;
			speed = 3;

		}
		if (position.y > 120) {
			position.y = 120;
			speed = 0;
		}
	}
	//animation of the boss
	if (speed != 0) {
		checkMove = MOVE;
	}

	if (speed == 0) {
		checkMove = STAND;
	}
	if (checkMove == 1 && currentFrame == 0)
	{
		currentFrame = 2;
	}
	animRect.top = checkMove * spriteHeight;
	animRect.bottom = animRect.top + spriteHeight;
	animRect.left = currentFrame * spriteWidth;
	animRect.right = animRect.left + spriteWidth;
	//enemy collision
	colRect.top = position.y;
	colRect.bottom = colRect.top + spriteHeight;
	colRect.left = position.x - 10;
	colRect.right = colRect.left + spriteWidth + 20;
	
	//edit sound effect
	if (F3Pressed) {
		if (counter2 <= 0) {
			counter2 = 5;
			F3Pressed = false;
		}

	}
	if (F4Pressed) {
		if (counter2 <= 0) {
			counter2 = 5;
			F4Pressed = false;
		}

	}
	//reset enemy position
	if (attackPosition == 0 and counter == 0) {
		attackPattern = 1;
	}
	if (counter == 0) {
		;
		counter = 500;
		attackPosition = rand() % 4 + 1;
		direction2 = 0;
		abc = 0;
		//limit position of the boss
		if (position.y > 180) {
			attackPosition = rand() % 2 + 3;
		}
		//limit time of boss standing 
		if (attackPosition == 3 || attackPosition == 4) {
			counter = 430;
		}
	}
	if (attackPosition == 1) {//pattern 1 walking of boss
		speed == 0;
		if (abc == 0) {
			speed = 3;
			if (direction2 <= 3.142)
				direction2 += 0.05;
			else
				abc++;
		}
		else if (abc == 1)
		{
			speed = 3;
			if (direction2 >= -3.142)
				direction2 -= 0.05;
			else
				abc--;
		}

		position.x += sin(direction2) * speed;
		position.y += -cos(direction2) * speed;

	}

	if (attackPosition == 2) {//pattern 2 walking of boss
		speed == 0;

		if (abc == 0) {
			speed = 3;
			if (direction2 >= -3.142)
				direction2 -= 0.05;
			else
				abc++;
		}
		else if (abc == 1)
		{
			speed = 3;
			if (direction2 <= 3.142)
				direction2 += 0.05;
			else
				abc--;
		}
		position.x += sin(direction2) * speed;
		position.y += -cos(direction2) * speed;
	}
	if (attackPosition == 3) {//pattern 3 walking of boss
		if (abc == 0) {
			speed = 3;
			if (direction2 <= 4.713) {
				direction2 += 0.05;
				position.x += sin(direction2) * speed;
				position.y += -cos(direction2) * speed;
			}
			else
				abc++;
		}
		if (abc == 1) {

			if (position.x > 70) {
				speed = 3;
				position.x -= speed / 1.5;
				if (position.x < 70) {
					position.x = 70;
					direction2 = 0;
					abc++;
				}
			}

		}
		if (abc == 2) {
			speed = 3;
			if (direction2 <= 1.571)
				direction2 += 0.05;
			position.x += sin(direction2) * speed / 1.5;
			position.y += -cos(direction2) * speed / 1.5;
			if (position.x > (MyWindowWidth - spriteWidth) / 2) {
				speed = 3;
				position.x = (MyWindowWidth - spriteWidth) / 2;
				if (position.y > 120) {
					position.y -= speed / 1.5;
					if (position.y < 120) {
						position.y = 120;
						speed = 0;
					}
				}
				if (position.y < 120) {
					position.y += speed / 1.5;
					if (position.y > 120) {
						position.y = 120;
						speed = 0;
					}
				}
			}
		}
	}
	if (attackPosition == 4) {//pattern 4 walking of boss
		speed = 0;
		if (abc == 0) {
			if (direction2 >= -4.713) {
				speed = 3;
				direction2 -= 0.05;
				position.x += sin(direction2) * speed;
				position.y += -cos(direction2) * speed;
			}
			else
				abc++;
		}
		if (abc == 1) {
			speed = 3;
			if (position.x < 500) {
				position.x += speed / 1.5;
				if (position.x > 500) {
					position.x = 500;
					direction2 = 0;
					abc++;
				}
			}

		}
		if (abc == 2) {
			speed = 3;
			if (direction2 >= -1.571)
				direction2 -= 0.05;
			position.x += sin(direction2) * speed / 1.5;
			position.y += -cos(direction2) * speed / 1.5;
			if (position.x < (MyWindowWidth - spriteWidth) / 2) {
				position.x = (MyWindowWidth - spriteWidth) / 2;
				if (position.y > 120) {
					position.y -= speed / 1.5;
					if (position.y < 120) {
						position.y = 120;
						speed = 0;
					}
				}
				if (position.y < 120) {
					position.y += speed / 1.5;
					if (position.y > 120) {
						position.y = 120;
						speed = 0;
					}
				}
			}
		}
	}
	if (isPower) {
		powerUp->Update();
	}
	magicBack->Update(position,stage);
	bulletCD--;
	bulletCD2--;
	counter2--;
}

void Enemy::Render()
{ if(bossHealthTime!=0){
	//draw the magic back of the enemy
	magicBack->Render();
	D3DXMATRIX mat;
	//draw the enemy texture
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	//draw the health bar of the enemy
	healthBar->Render();
	//draw the power up if hp lower than 50%
	if (isPower) {
		powerUp->Render();
	}
	if (isUlti) {//draw the ultimate texture
		ulti->Render();
	}
	//draw the bullet
	for (int i = 0; i < enemyBullets.size(); i++)
	{
		enemyBullets[i]->Render();
	}
}
}
RECT Enemy::GetCollisionRect() {//ckeck collision
	return colRect;
}
void Enemy::minusHealth() {//minus hp of the boss
	bossHealth -= 2;
}
void Enemy::clearBullet() {//clear the bullet
	enemyBullets.clear();
}
Enemy::~Enemy()
{
}

vector<EnemyBullet*> Enemy::getBullet() {//get bullet
	return enemyBullets;
}
void Enemy::Input() {//get input for user
	dInputKeyboardDevice->Acquire();
	dInputKeyboardDevice->GetDeviceState(256, diKeys);
	if (diKeys[DIK_F3] & 0x80) {
		F3Pressed = true;
	}
	if (diKeys[DIK_F4] & 0x80) {
		F4Pressed = true;
	}
}

int Enemy::GetHealthTime() {//get how many time left of boss health
	return bossHealthTime;
}