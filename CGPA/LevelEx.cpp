#include "LevelEx.h"

D3DXVECTOR2 lineVertices3[] = {
	D3DXVECTOR2(251, 0),
	D3DXVECTOR2(350, 0),
	D3DXVECTOR2(350, 1),
	D3DXVECTOR2(251, 1),
	D3DXVECTOR2(251, 0)
};

D3DXVECTOR2 lineVertices4[] = {
	D3DXVECTOR2(251, 799),
	D3DXVECTOR2(350, 799),
	D3DXVECTOR2(350, 800),
	D3DXVECTOR2(251, 800),
	D3DXVECTOR2(251, 799)
};

LevelEx::~LevelEx() {
}

void LevelEx::Initialize()
{
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/levelExBG.png", &texture);
	hr = D3DXCreateLine(d3dDevice, &line);
	hr = D3DXCreateFont(d3dDevice, 40, 0, FW_BOLD, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "MV Boli", &font);

	winner = 0;
	scaling = D3DXVECTOR2(1, 1);
	centre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
	direction = 0;
	position = D3DXVECTOR2(0, 0);

	spaceship1 = new Spaceship1();
	spaceship2 = new Spaceship2();
	ball = new LevelExBall();

	spaceship1->Initialize();
	spaceship2->Initialize();
	ball->Initialize();
	
	box1.top = 0;
	box1.bottom = 1;
	box1.left = 251;
	box1.right = 350;
	
	box2.top = 799;
	box2.bottom = 800;
	box2.left = 251;
	box2.right = 350;

	counter = 300;
	isEnd = false;

	textPosition = D3DXVECTOR2(201, 370);

	textWidth = 220;
	textHeight = 40;

	textRect.top = textPosition.y;
	textRect.bottom = textRect.top + textHeight;
	textRect.left = textPosition.x;
	textRect.right = textRect.left + textWidth;

	winner = 0;
	audioManager->PlayLevelExBGM();
}

void LevelEx::Update(vector<Game*>* game)
{
	spaceship1->Update();
	spaceship2->Update();
	ball->Update();

	// Collision Detection for all objects
	CheckPlayerCollide();
	CheckPlayerCollideWithBall();
	CheckWinner();

	// Use to check if any player wins then show the text on screen
	if (winner == 1)
	{
		textString = "Player 1 Win!";
	}
	else if (winner == 2)
	{
		textString = "Player 2 Win!";
	}
	
	if (isEnd) {
		counter--;
		audioManager->stopBGM();
		if (counter == 0)
		{
			game->pop_back();
		}
	}
}

void LevelEx::Render()
{
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	d3dDevice->BeginScene();

	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, 0, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	spaceship1->Render();
	spaceship2->Render();
	ball->Render();

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &centre, direction, &position);
	sprite->SetTransform(&mat);
	font->DrawText(sprite, textString, 13, &textRect, 0, D3DCOLOR_XRGB(255, 255, 255));

	sprite->End();

	line->Begin();
	line->Draw(lineVertices3, 5, D3DCOLOR_XRGB(255, 165, 0));
	line->Draw(lineVertices4, 5, D3DCOLOR_XRGB(255, 165, 0));
	line->End();

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
	if (pow(radiusA + radiusB, 2) > D3DXVec2LengthSq(&distanceAB)) return true; else return false;
}

void LevelEx::CheckPlayerCollide()
{
	if (CircleCollisionDetection(spaceship1->getRadius(), spaceship2->getRadius(),
		spaceship1->getPosition() + spaceship1->getCentre(), spaceship2->getPosition() + spaceship2->getCentre()))
	{
		double d = sqrt(pow(spaceship1->getPosition().x - spaceship1->getPosition().y, 2) + pow(spaceship2->getPosition().x - spaceship2->getPosition().y, 2));
		double nx = (spaceship1->getPosition().y - spaceship1->getPosition().x) / d;
		double ny = (spaceship2->getPosition().y - spaceship2->getPosition().x) / d;

		double p1 = 2 * (spaceship1->getVelocity().x * nx + spaceship1->getVelocity().y * ny -
			spaceship2->getVelocity().x * nx - spaceship2->getVelocity().y * ny) /
			(spaceship1->getMass() + spaceship2->getMass());

		double p2 = 2 * (spaceship2->getVelocity().x * nx + spaceship2->getVelocity().y * ny -
			spaceship1->getVelocity().x * nx - spaceship1->getVelocity().y * ny) /
			(spaceship2->getMass() + spaceship1->getMass());

		spaceship1->setVelocity(D3DXVECTOR2(
			(spaceship1->getVelocity().x - p1 * spaceship1->getMass() * spaceship2->getMass()),
			(spaceship1->getVelocity().y - p1 * spaceship1->getMass() * spaceship2->getMass())
		));

		spaceship2->setVelocity(D3DXVECTOR2(
			(spaceship2->getVelocity().x - p2 * spaceship2->getMass() * spaceship1->getMass()),
			(spaceship2->getVelocity().y - p2 * spaceship2->getMass() * spaceship1->getMass())
		));
	}
}

void LevelEx::CheckPlayerCollideWithBall()
{
	if (CircleCollisionDetection(spaceship1->getRadius(), ball->getRadius(),
		spaceship1->getPosition() + spaceship1->getCentre(), ball->getPosition() + ball->getCentre()))
	{
		// Calculate new velocity
		float newVelX1 = (spaceship1->getVelocity().x * (spaceship1->getMass() - ball->getMass()) +
			(2 * ball->getMass() * ball->getVelocity().x)) / (spaceship1->getMass() + ball->getMass());
		float newVelY1 = (spaceship1->getVelocity().y * (spaceship1->getMass() - ball->getMass()) +
			(2 * ball->getMass() * ball->getVelocity().y)) / (spaceship1->getMass() + ball->getMass());
		float newVelX2 = (ball->getVelocity().x * (ball->getMass() - spaceship1->getMass()) +
			(2 * spaceship1->getMass() * spaceship1->getVelocity().x)) / (spaceship1->getMass() + ball->getMass());
		float newVelY2 = (ball->getVelocity().y * (ball->getMass() - spaceship1->getMass()) +
			(2 * spaceship1->getMass() * spaceship1->getVelocity().y)) / (spaceship1->getMass() + ball->getMass());

		// Set the velocity
		spaceship1->setVelocity(D3DXVECTOR2(newVelX1, newVelY1));
		ball->setVelocity(D3DXVECTOR2(newVelX2, newVelY2));
	}

	if (CircleCollisionDetection(spaceship2->getRadius(), ball->getRadius(),
		spaceship2->getPosition() + spaceship2->getCentre(), ball->getPosition() + ball->getCentre()))
	{
		// Calculate new velocity
		float newVelX1 = (spaceship2->getVelocity().x * (spaceship2->getMass() - ball->getMass()) +
			(2 * ball->getMass() * ball->getVelocity().x)) / (spaceship2->getMass() + ball->getMass());
		float newVelY1 = (spaceship2->getVelocity().y * (spaceship2->getMass() - ball->getMass()) +
			(2 * ball->getMass() * ball->getVelocity().y)) / (spaceship2->getMass() + ball->getMass());
		float newVelX2 = (ball->getVelocity().x * (ball->getMass() - spaceship2->getMass()) +
			(2 * spaceship2->getMass() * spaceship2->getVelocity().x)) / (spaceship2->getMass() + ball->getMass());
		float newVelY2 = (ball->getVelocity().y * (ball->getMass() - spaceship2->getMass()) +
			(2 * spaceship2->getMass() * spaceship2->getVelocity().y)) / (spaceship2->getMass() + ball->getMass());

		// Set the velocity
		spaceship2->setVelocity(D3DXVECTOR2(newVelX1, newVelY1));
		ball->setVelocity(D3DXVECTOR2(newVelX2, newVelY2));
	}
}

void LevelEx::CheckWinner()
{
	// If the ball touches the player's base, opponent wins.
	if (CollisionDetection(ball->getColRect(), box1))
	{
		winner = 2;
		isEnd = true;
	}

	if (CollisionDetection(ball->getColRect(), box2))
	{
		winner = 1;
		isEnd = true;
	}
}