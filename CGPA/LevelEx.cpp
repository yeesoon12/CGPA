#include "LevelEx.h"

LevelEx::~LevelEx() {
}

void LevelEx::Initialize()
{
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/levelExBG.png", &texture);
	spaceship1 = new Spaceship1();
	spaceship2 = new Spaceship2();
	spaceship1->Initialize();
	spaceship2->Initialize();

	scaling = D3DXVECTOR2(1, 1);
	centre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
	direction = 0;
	position = D3DXVECTOR2(0, 0);

	AudioManager* audioManager = new AudioManager();
	audioManager->InitializeAudio();
	audioManager->LoadSounds();
	// audioManager->PlayLevelExBGM();
}

void LevelEx::Update()
{
	// Player collide each other
	if (CircleCollisionDetection(spriteWidth / 2, spriteWidth / 2, position + centre, position + centre))
	{
		cout << "Player Collided" << endl;
	}

	spaceship1->Update();
	spaceship2->Update();
}


void LevelEx::Render() {
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	d3dDevice->BeginScene();

	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, 0, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	spaceship1->Render();
	spaceship2->Render();

	sprite->End();

	d3dDevice->EndScene();
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void LevelEx::Input() {
	spaceship1->Input();
	spaceship2->Input();
}

bool LevelEx::CollisionDetection(RECT A, RECT B)
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

bool LevelEx::CircleCollisionDetection(float radiusA, float radiusB, D3DXVECTOR2 positionA, D3DXVECTOR2 positionB)
{
	D3DXVECTOR2 distanceAB = positionA - positionB;
	if (pow(radiusA + radiusB, 2) > D3DXVec2LengthSq(&distanceAB))
	{
		return true;
	}
	else
	{
		return false;
	}
}