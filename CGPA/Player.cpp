#include "Player.h"

void Player::Initialize() // initialize player 
{
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/Player.png", &texture);

	if (FAILED(hr)) {
		cout << "Failed to load texture" << endl;
	}
	
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
	if (health <= 0) { // not to render when player is die
		return;
	}
	if (isUlti) // render ulti when player press ulti button
		ulti->Render();
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
	if (bulletAmount >= 5) //bullet amount cant be more than 5
		bulletAmount = 5;

	catalysts->Update(position,focus); //update the catalyst according to the focus and position
	if (!leftPressed && !rightPressed)
		move = UPDOWN;// set the sprite animation when player is not moving left or right
	if (!cPressed) { // reset the focus when c is not pressed
		focus = 0;

	}
	for (int i = 0; i < bullet.size(); i++) {

		bullet[i]->Update();

	} // update all the bullets that has been fire out
	if (!zPressed) {
		speed = 7.0f;// reset the speed when player didnt press z

	}

	if (zPressed) {
		speed = 2.5f; // when z pressed, decrease the player speed
		zPressed = false;
		
	}
	if (xPressed) {
		if (ultiCD < 0 and health>0){
		
			ulti = new Ultimate();	//create a new ulti
		ulti->Initialization(position); // initialize player position to the ulti position
		audioManager->PlayUltiSound();// play ultimate sound
		isUlti = true;
		isUlti2 = true;
		ultiCD = 300; // set the ulti cd
		}
		xPressed = false;

	}
	if (cPressed) {
		focus = 1; // focus the bullet infront of the player
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
		move = LEFT;// set the animation to second row
	}

	if (rightPressed) {
		position.x += speed;
		rightPressed = false;
		move = RIGHT;// set the animation to third row
	}

	if (F3Pressed) {
		if (counter2 <= 0) { //increase

			counter2 = 5;
			F3Pressed = false;
		}
			
	}
	if (F4Pressed) { //decrease sound effect
		if (counter2 <= 0) {
			counter2 = 5;
			F4Pressed = false;
		}

	}
	if (spacePressed) {
		if(cd<0&&health>0){
		audioManager->PlayGunShoot();// play gun shoot sound when is fire
		if(bulletAmount==1){ // render the bullets according to the bullets amount
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
		cd = 6; //set the cd of bullet shoot
		}
		
	}
	if (position.x < 0) { //player cant move out the boundary
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
	animRect.top = move * spriteHeight; //update animation rect
	animRect.bottom = animRect.top + spriteHeight;
	animRect.left = currentFrame * spriteWidth;
	animRect.right = animRect.left + spriteWidth;
	
	colRect.top = position.y; //update col rect
	colRect.bottom = colRect.top + 2;
	colRect.left = position.x+10;
	colRect.right = colRect.left +10;
	spacePressed = false; //set the key press back to false
	if (isUlti)
		ulti->Update(); //only update the ulti when there is a ulti
	if(counter>=fps){ // adjust the animation speed of the player
	currentFrame++;
	if (currentFrame >= maxFrame)
	{
		currentFrame = 0;
	}
	
	counter = 0;
	}
	counter++;
	cd--;
	counter2--;
	ultiCD--;
}

void Player::minusHealth() { // decrease the health of the player
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
vector<PlayerShoot*> Player::getBullet() // return all the bullet that shooted 
{
	return bullet;
}

void Player::addBullet(int bulletAmounts) { // add the bullet amount of the player
	bulletAmount += bulletAmounts;
}
RECT Player::getColRect() {
	return colRect;
}// return collision rect

boolean Player::IsUlti() {
	if (isUlti2 == true)
		return true;
	if (isUlti2 == false)
		return false;
} // return the is ulti function
Player::~Player() {

}
