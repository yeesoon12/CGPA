#include "EnemySmallKnife.h"

void EnemySmallKnife::Initialization(float Direction, D3DXVECTOR2 position, int speed, float directionInc) {
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/EnemyBullet8.png", &texture);
	if (FAILED(hr)) {
		cout << "Failed to load texture" << endl;
	}

	textureWidth = 16;
	textureHeight = 16;
	increaseDir = directionInc; // set how much direction that will increase in every loop
	spriteRow = 1;
	spriteCol = 1;
	spriteWidth = textureWidth / spriteCol;
	spriteHeight = textureHeight / spriteRow;

	animRect.top = 0;
	animRect.bottom = 16;
	animRect.left = 0;
	animRect.right = 16;
	scaling = D3DXVECTOR2(1.f, 1.f);
	centre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);

	this->speed = speed;  //set the bullet direction speed and position
	direction = Direction;
	this->position = position;



	colRect.top = position.y+10;
	colRect.bottom = colRect.top + spriteHeight-20;
	colRect.left = position.x+10;
	colRect.right = colRect.left + spriteWidth-20;
}

void EnemySmallKnife::Update() {

	if (InBoundary(position)) { // update the bullet when it is in boundary


		position.x += sin(direction) * speed;
		position.y += -cos(direction) * speed;


	
	colRect.top = position.y -10;
	colRect.bottom = colRect.top+5;
	colRect.left = position.x + 5;
	colRect.right = colRect.left + 5;
	direction += increaseDir;
	
}
	

}



void EnemySmallKnife::Render() {
	if (InBoundary(position)) {// render the bullet when it is in boundary
		D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &this->position);
		sprite->SetTransform(&mat);
		sprite->Draw(texture, &animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	}
}
EnemySmallKnife::~EnemySmallKnife()
{
}