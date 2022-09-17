#include "Player.h"

void Player::Initialize()
{
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/Player.png", &texture);

	if (FAILED(hr)) {
		cout << "Failed to load texture" << endl;
	}
	
	audioManager = new AudioManager();
	audioManager2 = new AudioManager();
	audioManager->InitializeAudio();
	audioManager->LoadSounds();
	audioManager2->InitializeAudio();
	audioManager2->LoadSounds();
	catalysts = new Catalysts();
	
	cd = 0;
	focus = 0;
	health = 1;
	upPressed = false;
	downPressed = false;
	leftPressed = false;
	rightPressed = false;
	spacePressed = false;
	zPressed = false;
	xPressed = false;
	cPressed = false;
	isUlti = false;
	F3Pressed = false;
	F4Pressed = false;
	velocity = D3DXVECTOR2(0, 0);
	speed = 7.0f;
	bulletAmount = 1;
	textureWidth = 512;
	textureHeight = 280;
	counter = 0;
	counter2 = 0;
	spriteRow = 3;
	spriteCol = 8;
	spriteWidth = textureWidth / spriteCol;
	spriteHeight = textureHeight / spriteRow;
	ultiCD = 100;
	animRect.top = currentFrame * spriteHeight;
	animRect.bottom = animRect.top + spriteHeight;
	animRect.left = currentFrame * spriteWidth;
	animRect.right = animRect.left + spriteWidth;

	scaling = D3DXVECTOR2(0.5, 0.5);
	centre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
	direction =0;
	position = D3DXVECTOR2(MyWindowWidth/2, 700);
	catalysts->Initialization(position);
	colRect.top = position.y;
	colRect.bottom = colRect.top + spriteHeight;
	colRect.left = position.x;
	colRect.right = colRect.left + spriteWidth;

	fps = 20;
	maxFrame = spriteCol-1;
}

void Player::Render()
{
	if (health <= 0) {
		return;
	}
	if (isUlti)
		ulti->Render();
	counter++;
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	catalysts->Render();
	
	for (int i = 0; i < bullet.size(); i++) {
		
		bullet[i]->Render();
	
	}
	

	
}

void Player::Update() {
	isUlti2 = false;
	if (bulletAmount >= 5)
		bulletAmount = 5;

	catalysts->Update(position,focus);
	if (!leftPressed && !rightPressed)
		move = UPDOWN;
	if (!cPressed) {
		focus = 0;

	}
	for (int i = 0; i < bullet.size(); i++) {

		bullet[i]->Update();

	}
	if (!zPressed) {
		speed = 7.0f;

	}

	if (zPressed) {
		speed = 2.5f;
		zPressed = false;
		
	}
	if (xPressed) {
		if (ultiCD < 0 and health>0){
		
			ulti = new Ultimate();
		ulti->Initialization(position);
		audioManager2->PlayUltiSound();
		isUlti = true;
		isUlti2 = true;
		ultiCD = 350;
		}
		xPressed = false;

	}
	if (cPressed) {
		focus = 1;
		cPressed = false;

	}

	if (upPressed) {
		position.y -= speed;
		upPressed = false;
		
	}

	if (downPressed) {
		position.y += speed;
		downPressed = false;
		
	}

	if (leftPressed) {
		position.x -= speed;
		leftPressed = false;
		move = LEFT;
	}

	if (rightPressed) {
		position.x += speed;
		rightPressed = false;
		move = RIGHT;
	}

	if (F3Pressed) {
		if (counter2 <= 0) {
			audioManager->editSoundEffect(0.1);
			audioManager2->editSoundEffect(0.1);
			counter2 = 5;
			F3Pressed = false;
		}
			
	}
	if (F4Pressed) {
		if (counter2 <= 0) {
			audioManager->editSoundEffect(-0.1);
			audioManager2->editSoundEffect(-0.1);
			counter2 = 5;
			F4Pressed = false;
		}

	}
	if (spacePressed) {
		if(cd<0&&health>0){
		audioManager->PlayGunShoot();
		if(bulletAmount==1){
		shoot = new PlayerShoot();
		shoot->Initialization(position, 0,focus);
		bullet.push_back(shoot);
		}
		else if (bulletAmount == 3) {
			shoot = new PlayerShoot();
			shoot->Initialization(position, 0, focus);
			bullet.push_back(shoot);
			shoot = new PlayerShoot();
			shoot->Initialization(position, 0.15, focus);
			bullet.push_back(shoot);
			shoot = new PlayerShoot();
			shoot->Initialization(position, -0.15, focus);
			bullet.push_back(shoot);
		}
		else if (bulletAmount == 5) {
			shoot = new PlayerShoot();
			shoot->Initialization(position, 0, focus);
			bullet.push_back(shoot);
			shoot = new PlayerShoot();
			shoot->Initialization(position, 0.3, focus);
			bullet.push_back(shoot);
			shoot = new PlayerShoot();
			shoot->Initialization(position, 0.15, focus);
			bullet.push_back(shoot);
			shoot = new PlayerShoot();
			shoot->Initialization(position, -0.15, focus);
			bullet.push_back(shoot);
			shoot = new PlayerShoot();
			shoot->Initialization(position, -0.3, focus);
			bullet.push_back(shoot);
		}
		spacePressed = false;
		cd = 6;
		}
		
	}
	if (position.x < 0) {
		position.x = 0;
	}

	if (position.x + spriteWidth/2 > MyWindowWidth) {
		position.x = MyWindowWidth - spriteWidth/2;
	}

	if (position.y < 0) {
		position.y = 0;
	}

	if (position.y + spriteHeight / 2 > MyWindowHeight) {
		position.y = MyWindowHeight - spriteHeight / 2;
	}
	animRect.top = move * spriteHeight;
	animRect.bottom = animRect.top + spriteHeight;
	animRect.left = currentFrame * spriteWidth;
	animRect.right = animRect.left + spriteWidth;
	
	colRect.top = position.y;
	colRect.bottom = colRect.top + 2;
	colRect.left = position.x+10;
	colRect.right = colRect.left +10;
	spacePressed = false;
	if (isUlti)
		ulti->Update();
	if(counter>=fps){
	currentFrame++;
	if (currentFrame >= maxFrame)
	{
		currentFrame = 0;
	}
	
	counter = 0;
	}
	cd--;
	counter2--;
	ultiCD--;
}

void Player::minusHealth() {
	health--;
}
void Player::Input() {
	dInputKeyboardDevice->Acquire();
	dInputKeyboardDevice->GetDeviceState(256, diKeys);

	// shoot update
	if (diKeys[DIK_SPACE] & 0x80) {
		spacePressed = true;
	}

	// movement
	if (diKeys[DIK_UP] & 0x80) {
		upPressed = true;
	}

	if (diKeys[DIK_DOWN] & 0x80) {
		downPressed = true;
	}

	if (diKeys[DIK_LEFT] & 0x80) {
		leftPressed = true;
	}

	if (diKeys[DIK_RIGHT] & 0x80) {
		rightPressed = true;
	}

	if (diKeys[DIK_Z] & 0x80) {
		zPressed = true;
	}
	if (diKeys[DIK_X] & 0x80) {
		xPressed = true;
	}
	if (diKeys[DIK_C] & 0x80) {
		cPressed = true;
		
	}
	if (diKeys[DIK_F3] & 0x80) {
		F3Pressed = true;
	}
	if (diKeys[DIK_F4] & 0x80) {
		F4Pressed = true;
	}
}
vector<PlayerShoot*> Player::getBullet()
{
	return bullet;
}

void Player::addBullet(int bulletAmounts) {
	bulletAmount += bulletAmounts;
}
RECT Player::getColRect() {
	return colRect;
}

boolean Player::IsUlti() {
	if (isUlti2 == true)
		return true;
	if (isUlti2 == false)
		return false;
}
Player::~Player() {

}
