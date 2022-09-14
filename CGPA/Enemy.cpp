#include "Enemy.h"



void Enemy::Initialize()
{
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/boss.png", &texture);

	if (FAILED(hr)) {
		cout << "Failed to load texture123456789" << endl;
	}

	magicBack = new MagicBack();
	healthBar = new HealthBar();
	magicBack->Initialize(position);
	healthBar->Initialize(bossHealth, bossHealthTime);
	attackPosition = 0;
	bossHealth = 100;
	bossDamage = 100;
	counter = 500;
	textureWidth = 256;
	textureHeight = 160;
	bossHealthTime = 3;
	spriteRow = 2;
	spriteCol = 4;
	spriteWidth = textureWidth / spriteCol;
	spriteHeight = textureHeight / spriteRow;
	counters=0;
	fps = 12;
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
	velocity = D3DXVECTOR2(0, 0);
	position = D3DXVECTOR2((MyWindowWidth- spriteWidth) /2, -230);
	colRect.top = position.y;
	colRect.bottom = colRect.top + spriteHeight;
	colRect.left = position.x;
	colRect.right = colRect.left + spriteWidth;
	maxAttackPosition = 8;
	maxFrame = 3;
}

void Enemy::Update()
{
	
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
			if (bossHealth == 0) {
				bossHealthTime--;
				bossHealth = 100;
			}
		}
		if (bossHealthTime == 0) {
			bossHealthTime = 0;
			bossHealth = 0;
		}
		bossHealth -= 0.5;
		healthBar->Update(bossHealth, bossHealthTime);
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
	
	
	if (counter == 0) {
		counter = 500;
		if (attackPosition == maxAttackPosition) {
			attackPosition=0;
		}
		attackPosition++;
	}
	
	if (attackPosition == 1) {
		if (position.x > 50 ) {
			velocity.x = enemySpeedVertical;
			velocity.y = -enemySpeedHorizotal;
			position -= velocity;
		}
		if (position.x < 50) {
			position.x = 50;
			velocity = D3DXVECTOR2(0, 0);
		}
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

	magicBack->Update(position);
}

void Enemy::Render()
{
	magicBack->Render();
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	healthBar->Render();
}

Enemy::~Enemy()
{
}