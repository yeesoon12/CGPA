#include "EnemyKnife.h"


void EnemyKnife::Initialization(float Direction, D3DXVECTOR2 position, int speed, int reflectionTime) {
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/EnemyBullet7.png", &texture);
	if (FAILED(hr)) {
		cout << "Failed to load texture" << endl;
	}

	textureWidth = 32;
	textureHeight = 32;

	spriteRow = 1;
	spriteCol = 1;
	spriteWidth = textureWidth / spriteCol;
	spriteHeight = textureHeight / spriteRow;

	
	animRect.top = 0;
	animRect.bottom = 32;
	animRect.left = 0;
	animRect.right = 32;
	scaling = D3DXVECTOR2(1.f, 1.f);
	centre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);

	this->speed = speed;       // Set the bullet with the given speed, direction and position
	direction = Direction;
	this->position = position;
	
	isReflection = reflectionTime; // set how many time the bullet can reflect with boudary
	
	colRect.top = position.y;
	colRect.bottom = colRect.top + spriteHeight;
	colRect.left = position.x;
	colRect.right = colRect.left + spriteWidth;
}

void EnemyKnife::Update() {
	// if bullet is in boudary, update it
	if (InBoundary(position)) {
	position.x += sin(direction) * speed;
	position.y += -cos(direction) * speed;

	colRect.top = position.y+5;
	colRect.bottom = colRect.top + 3;
	colRect.left = position.x+20;
	colRect.right = colRect.left + 3;
	}
	if(isReflection>0){//check the remain bullet reflect time
	if (Reflection(position)) { // if bullet touch the reflect boudary
		randomNumber = rand()%1571 + 4713;
		direction += (randomNumber % 1000); // randomly change the bullet direction with a certain degree
		isReflection--; //reflect time -1
	}
	
	}
}



void EnemyKnife::Render() {
	// if bullet is in boudary, Render it
	if (InBoundary(position)) {
		D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &this->position);
		sprite->SetTransform(&mat);
		sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	}
}

EnemyKnife::~EnemyKnife()
{
}