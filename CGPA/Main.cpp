//	Ask the compiler to include minimal header files for our program.
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include<iostream>
#include <dinput.h>
#include "FrameTimer.h"
#include "AudioManager.h"
//--------------------------------------------------------------------
using namespace std;
#pragma comment (lib,"d3d9.lib")
#pragma comment (lib,"d3dx9.lib")
#pragma comment (lib,"dinput8.lib")
#pragma comment (lib,"dxguid.lib")


//	Window handle
HWND g_hWnd = NULL;
WNDCLASS wndClass;
IDirect3DDevice9* d3dDevice;
LPDIRECT3DTEXTURE9 cursor = NULL;
LPD3DXSPRITE sprite = NULL;
LPD3DXFONT font = NULL;//this is the font brush
LPD3DXLINE line = NULL;
AudioManager* audioManager;

#define MyWindowWidth 800
#define MyWindowHeight 600
//#define BUTTONDOWN (name, key) (name.rgbButtons[key] & 0x80)
#define KEYDOWN(name, key) (name[key] & 0x80)

//enum CharacterMovement { moveDown, moveLeft, moveRight, moveUp };

DIMOUSESTATE mouseState;
LONG currentXpos;
LONG currentYpos;

//Gobal 
RECT spriteRect;
RECT cursorRect;


D3DXVECTOR2 mouseposition;
bool leftKeyPressed = false;
bool rightKeyPressed = false;
bool upKeyPressed = false;
bool downKeyPressed = false;
bool spaceKeyPressed = false;

bool wKeyPressed = false;
bool aKeyPressed = false;
bool sKeyPressed = false;
bool dKeyPressed = false;


int red = 0;
int blue = 0;
int green = 0;

FrameTimer* timer = new FrameTimer();




RECT mouseColRect;

//My Game Level

//Player 1 and 2 share globals
LPDIRECT3DTEXTURE9 texture = NULL;
int textureWidth = 0;
int textureHeight = 0;
int spriteWidth = 0;
int spriteHeight = 0;
int spriteRow = 0;
int spriteColum = 0;
int maxFrame = 0;

//player 1
RECT player1AnimRect;
RECT player1ColRect;
D3DXVECTOR2 player1Position;
D3DXVECTOR2 player1Velocity;
D3DXVECTOR2 player1Acceleration;
D3DXVECTOR2 scaling1;
D3DXVECTOR2 spriteCentre1;
int player1CurrentFrame = 0;
float player1Direction;
int spriteFPS1 = 15;
int player1Number;
float player1RoatationSpeed;
int player1Mass;
float player1EngineForce;
bool player1ForceOn;

//player 2
RECT player2AnimRect;
RECT player2ColRect;
D3DXVECTOR2 player2Position;
D3DXVECTOR2 player2Velocity;
D3DXVECTOR2 player2Acceleration;
int player2CurrentFrame = 0;
float player2Direction;
int spriteFPS2 = 15;
int player2Number;
D3DXVECTOR2 scaling2;
D3DXVECTOR2 spriteCentre2;
float player2RoatationSpeed;
int player2Mass;
float player2EngineForce;
bool player2ForceOn;


//Mass 1 and 2 share globals
LPDIRECT3DTEXTURE9 massTexture = NULL;
int massTextureWidth = 0;
int massTextureHeight = 0;
int massSpriteWidth = 0;
int massSpriteHeight = 0;
int massSpriteRow = 0;
int massSpriteColum = 0;
int massMaxFrame = 0;

//Mass 1
RECT mass1AnimRect;
RECT mass1ColRect;
D3DXVECTOR2 mass1Position;
D3DXVECTOR2 mass1Velocity;
D3DXVECTOR2 mass1Acceleration;
D3DXVECTOR2 massScaling1;
D3DXVECTOR2 massSpriteCentre1;
int mass1CurrentFrame = 0;
float mass1Direction;
int massSpriteFPS1 = 15;
int mass1Number;
float mass1RoatationSpeed;
int mass1Mass;
float mass1EngineForce;
int mass1HP;

//Mass 2
RECT mass2AnimRect;
RECT mass2ColRect;
D3DXVECTOR2 mass2Position;
D3DXVECTOR2 mass2Velocity;
D3DXVECTOR2 mass2Acceleration;
int mass2CurrentFrame = 0;
float mass2Direction;
int massSpriteFPS2 = 15;
int mass2Number;
D3DXVECTOR2 massScaling2;
D3DXVECTOR2 massSpriteCentre2;
float mass2RoatationSpeed;
int mass2Mass;
float mass2EngineForce;
int mass2HP;

//clocl globals
float timeCounter = 0;
int needldLenght = 100;
D3DXVECTOR2 startPoint{ 170,170 };
D3DXVECTOR2 endPoint{ 150,170 };
D3DXVECTOR2 lineVertices[] = { startPoint, endPoint };

//mouse globals
LPDIRECTINPUT8 dInput;
LPDIRECTINPUTDEVICE8  dInputKeyboardDevice;
LPDIRECTINPUTDEVICE8  dInputMouseDevice;
BYTE  diKeys[256];
char buffer[256];

//Sprite 
int jumpTime = 0;


//world
float gravity = 2;
float friction = 0.05f;

int counter = 0;
int CharacterCurrentMovement = 0;
int CharacterMovementSpeed = 5;


//--------------------------------------------------------------------

//	Window Procedure, for event handling
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//case WM_MOUSEMOVE:
		//{
		//	// Retrieve mouse screen position        
		//	int x1 = (short)LOWORD(lParam);
		//	int y1 = (short)HIWORD(lParam);
		//	position2.x = x1;
		//	position2.y = y1;
		//	//Do something with the mouse screen position
		//	break;
		//}

		//	The message is post when we destroy the window.
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		/*case WM_KEYDOWN:
			switch (wParam)
			{
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
			case VK_DOWN:
				downKeyPressed = true;
				break;
			case VK_UP:
				upKeyPressed = true;
				break;
			case VK_LEFT:
				leftKeyPressed = true;
				break;
			case VK_RIGHT:
				rightKeyPressed = true;
				break;
			case 'R':
				red += 5;
				break;
			case 'G':
				green += 5;
				break;
			case 'B':
				blue += 5;
				break;
			case VK_SPACE:
				red = 0;
				blue = 0;
				green = 0;
				spaceKeyPressed = true;
				break;
			}*/
			/*
				Write your code here...
			*/

			//	Default handling for other messages.
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
//--------------------------------------------------------------------

void CreateWindows()
{
	/*
		Step 1
		Define and Register a Window.
	*/

	//	Window's structure

	//	Set all members in wndClass to 0.
	ZeroMemory(&wndClass, sizeof(wndClass));

	//	Filling wndClass. You are to refer to MSDN for each of the members details.
	//	These are the fundamental structure members to be specify, in order to create your window.
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hInstance = GetModuleHandle(NULL);
	wndClass.lpfnWndProc = WindowProcedure;
	wndClass.lpszClassName = "My Window";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	//	Register the window.
	RegisterClass(&wndClass);

	/*
		Step 2
		Create the Window.
	*/
	//	You are to refer to MSDN for each of the parameters details.
	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "My Window's Name", WS_OVERLAPPEDWINDOW, 0, 100, MyWindowWidth, MyWindowHeight, NULL, NULL, GetModuleHandle(NULL), NULL);
	ShowWindow(g_hWnd, 1);
}

bool WindowIsRunning()
{
	//	Some interesting function to try out.
	//	ShowCursor(false);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	/*
		Step 3
		Handling window messages
		NOTE! There are several ways of writing the message loop.
		You have to based on which kind of application your are writing.
	*/
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		//	Receive a quit message
		if (msg.message == WM_QUIT)
			return false;
		//	Translate the message 
		TranslateMessage(&msg);
		//	Send message to your window procedure
		DispatchMessage(&msg);
	}
	return true;
}

void CleanLvWindow()
{
	texture->Release();
	texture = NULL;

	/*cursor->Release();
	cursor = NULL;

	font->Release();
	font = NULL;

	line->Release();
	line = NULL;*/
}

int InitializeLevel()
{
	srand(time(0));
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/practical9.png", &texture);
	hr = D3DXCreateTextureFromFile(d3dDevice, "Asset/mass.png", &massTexture);
	if (FAILED(hr))
		return 0;
	/*hr = D3DXCreateTextureFromFile(d3dDevice, "pointer.png", &cursor);*/

	//Player 1 and 2 share init
	textureWidth = 64;
	textureHeight = 64;
	spriteRow = 2;
	spriteColum = 2;
	spriteWidth = textureWidth / spriteColum;
	spriteHeight = textureHeight / spriteRow;
	maxFrame = 1;

	//player 1 init
	player1Number = 1;
	player1CurrentFrame = 0;
	player1AnimRect.top = player1CurrentFrame * spriteHeight;
	player1AnimRect.bottom = player1ColRect.top + spriteHeight;
	player1AnimRect.left = (player1Number - 1) * spriteWidth;
	player1AnimRect.right = player1ColRect.left + spriteWidth;

	player1Position = D3DXVECTOR2(100, 300);
	player1ColRect.top = player1Position.y;
	player1ColRect.bottom = player1ColRect.top + spriteHeight;
	player1ColRect.left = player1Position.x;
	player1ColRect.right = player1ColRect.left + spriteWidth;

	player1Velocity = D3DXVECTOR2(0, 0);
	player1Acceleration = D3DXVECTOR2(0, 0);
	player1Direction = 0.0f;
	spriteFPS1 = 1;

	scaling1 = D3DXVECTOR2(1.0f, 1.0f);
	spriteCentre1 = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);

	player1RoatationSpeed = 0.07f;
	player1Mass = 1;
	player1EngineForce = 1;
	player1ForceOn = false;

	//player 2 init
	player2Number = 2;
	player2CurrentFrame = 0;
	player2AnimRect.top = player2CurrentFrame * spriteHeight;
	player2AnimRect.bottom = player2ColRect.top + spriteHeight;
	player2AnimRect.left = (player2Number - 1) * spriteWidth;
	player2AnimRect.right = player2ColRect.left + spriteWidth;

	player2Position = D3DXVECTOR2(700, 300);
	player2ColRect.top = player2Position.y;
	player2ColRect.bottom = player2ColRect.top + spriteHeight;
	player2ColRect.left = player2Position.x;
	player2ColRect.right = player2ColRect.left + spriteWidth;

	player2Velocity = D3DXVECTOR2(0, 0);
	player2Acceleration = D3DXVECTOR2(0, 0);
	player2Direction = 0.0f;
	spriteFPS2 = 1;

	scaling2 = D3DXVECTOR2(1.0f, 1.0f);
	spriteCentre2 = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);

	player2RoatationSpeed = 0.07f;
	player2Mass = 1;
	player2EngineForce = 1;
	player2ForceOn = false;

	//Mass
	//mass 1 and 2 share init
	massTextureWidth = 32;
	massTextureHeight = 32;
	massSpriteRow = 0;
	massSpriteColum = 0;
	massSpriteWidth = 9;
	massSpriteHeight = 9;
	massMaxFrame = 0;

	//mass 1 init
	mass1Number = 1;
	mass1CurrentFrame = 0;
	mass1AnimRect.top = 0;
	mass1AnimRect.bottom = mass1AnimRect.top + massSpriteHeight;
	mass1AnimRect.left = 0;
	mass1AnimRect.right = mass1AnimRect.left + massSpriteWidth;

	mass1Position = D3DXVECTOR2(rand() % (MyWindowWidth - massSpriteWidth), rand() % (MyWindowHeight - massSpriteHeight));
	mass1ColRect.top = mass1Position.y;
	mass1ColRect.bottom = mass1ColRect.top + massSpriteHeight;
	mass1ColRect.left = mass1Position.x;
	mass1ColRect.right = mass1ColRect.left + massSpriteWidth;

	mass1Velocity = D3DXVECTOR2(0, 0);
	mass1Acceleration = D3DXVECTOR2(0, 0);
	mass1Direction = 0.0f;
	massSpriteFPS1 = 0;

	massScaling1 = D3DXVECTOR2(1.0f, 1.0f);
	massSpriteCentre1 = D3DXVECTOR2(massSpriteWidth / 2, massSpriteHeight / 2);

	mass1RoatationSpeed = 0;
	mass1Mass = 1;
	mass1HP = 1;
	//mass 2 init
	mass2Number = 2;
	mass2CurrentFrame = 0;
	mass2AnimRect.top = 0;
	mass2AnimRect.bottom = mass2AnimRect.top + massSpriteHeight;
	mass2AnimRect.left = 0;
	mass2AnimRect.right = mass2AnimRect.left + massSpriteWidth;

	mass2Position = D3DXVECTOR2(rand() % (MyWindowWidth - massSpriteWidth), rand() % (MyWindowHeight - massSpriteHeight));
	mass2ColRect.top = mass2Position.y;
	mass2ColRect.bottom = mass2ColRect.top + massSpriteHeight;
	mass2ColRect.left = mass2Position.x;
	mass2ColRect.right = mass2ColRect.left + massSpriteWidth;

	mass2Velocity = D3DXVECTOR2(0, 0);
	mass2Acceleration = D3DXVECTOR2(0, 0);
	mass2Direction = 0.0f;
	massSpriteFPS2 = 1;

	massScaling2 = D3DXVECTOR2(1.0f, 1.0f);
	massSpriteCentre2 = D3DXVECTOR2(massSpriteWidth / 2, massSpriteHeight / 2);

	mass2RoatationSpeed = 0;
	mass2Mass = 1;
	mass2EngineForce = 0;
	mass2HP = 1;

	AudioManager* audioManager = new AudioManager();
	audioManager->InitializeAudio();
	audioManager->LoadSounds();
	audioManager->PlaySoundTrack1();
}

bool CollisionDetection(RECT A, RECT B)
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

bool CircleCollisionDetection(float radisuA, float radiusB, D3DXVECTOR2 positionA, D3DXVECTOR2 positionB) {

	D3DXVECTOR2 distanceAB = positionA - positionB;

	if (pow((radisuA + radiusB), 2) > D3DXVec2LengthSq(&distanceAB)) {
		return true;
	}
	else {
		return false;
	}
}

void Update(int frameToUpdate)
{
	for (int i = 0; i < frameToUpdate; i++)
	{
		counter++;
		if (leftKeyPressed) {
			player1Direction -= player1RoatationSpeed;
		}
		if (rightKeyPressed) {
			player1Direction += player1RoatationSpeed;
		}
		if (upKeyPressed) {
			player1Acceleration.x = sin(player1Direction) * player1EngineForce / player1Mass;
			player1Acceleration.y = -cos(player1Direction) * player1EngineForce / player1Mass;
		}
		if (downKeyPressed) {
			player1Acceleration.x = -sin(player1Direction) * player1EngineForce / player1Mass;
			player1Acceleration.y = cos(player1Direction) * player1EngineForce / player1Mass;
		}
		player1Velocity += player1Acceleration;
		player1Velocity *= 1 - friction;
		player1Position += player1Velocity;
		if (player1Position.x<0 || player1Position.x>MyWindowWidth - spriteWidth)
		{
			if (player1Position.x < 0)
				player1Position.x = 0;
			if (player1Position.x > MyWindowWidth - spriteWidth)
				player1Position.x = MyWindowWidth - spriteWidth;
			player1Velocity.x *= -1;

		}
		if (player1Position.y<0 || player1Position.y>MyWindowHeight - spriteHeight)
		{
			if (player1Position.y < 0)
				player1Position.y = 0;
			if (player1Position.y > MyWindowHeight - spriteHeight)
				player1Position.y = MyWindowHeight - spriteHeight;
			player1Velocity.y *= -1;

		}
		//player1
		if (counter % (timer->GetFPS() / spriteFPS1) == 0) {
			player1CurrentFrame++;
			if (player1CurrentFrame > maxFrame) {
				player1CurrentFrame = 0;
			}
		}
		player1AnimRect.top = player1CurrentFrame * spriteHeight;
		player1AnimRect.bottom = player1AnimRect.top + spriteHeight;
		player1AnimRect.left = (player1Number - 1) * spriteWidth;
		player1AnimRect.right = player1AnimRect.left + spriteWidth;


		//player2
		if (aKeyPressed) {
			player2Direction -= player2RoatationSpeed;
		}
		if (dKeyPressed) {
			player2Direction += player2RoatationSpeed;
		}
		if (wKeyPressed) {
			player2Acceleration.x = sin(player2Direction) * player2EngineForce / player2Mass;
			player2Acceleration.y = -cos(player2Direction) * player2EngineForce / player2Mass;

		}
		if (sKeyPressed) {
			player2Acceleration.x = -sin(player2Direction) * player2EngineForce / player2Mass;
			player2Acceleration.y = cos(player2Direction) * player2EngineForce / player2Mass;

		}
		player2Velocity += player2Acceleration;
		player2Velocity *= 1 - friction;
		player2Position += player2Velocity;
		if (player2Position.x<0 || player2Position.x>MyWindowWidth - spriteWidth)
		{
			if (player2Position.x < 0)
				player2Position.x = 0;
			if (player2Position.x > MyWindowWidth - spriteWidth)
				player2Position.x = MyWindowWidth - spriteWidth;
			player2Velocity.x *= -1;

		}
		if (player2Position.y<0 || player2Position.y>MyWindowHeight - spriteHeight)
		{
			if (player2Position.y < 0)
				player2Position.y = 0;
			if (player2Position.y > MyWindowHeight - spriteHeight)
				player2Position.y = MyWindowHeight - spriteHeight;
			player2Velocity.y *= -1;

		}
		if (counter % (timer->GetFPS() / spriteFPS2) == 0) {
			player2CurrentFrame++;
			if (player2CurrentFrame > maxFrame) {
				player2CurrentFrame = 0;

			}
		}
		player2AnimRect.top = player2CurrentFrame * spriteHeight;
		player2AnimRect.bottom = player2AnimRect.top + spriteHeight;
		player2AnimRect.left = (player2Number - 1) * spriteWidth;
		player2AnimRect.right = player2AnimRect.left + spriteWidth;


		//if (CollisionDetection(player1ColRect, player2ColRect)) {
		//	/*if (player1ForceOn) {
		//		player2Velocity += player1Velocity;
		//		player1Velocity *= -1;
		//		cout << "1" << endl;
		//	}
		//	else if (player2ForceOn) {
		//		player1Velocity += player2Velocity;
		//		player2Velocity *= -1;
		//		cout << "2" << endl;
		//	}
		//	else {
		//		player1Velocity.x *= -1;
		//		player1Velocity.y *= -1;
		//		player2Velocity.x *= -1;
		//		player2Velocity.y *= -1;
		//		cout << "Collied!" << endl;
		//	}*/
		//	
		//	D3DXVECTOR2 player2 = player2Velocity;
		//	player2Velocity *= -0.5;
		//	player2Velocity += player1Velocity;
		//	player1Velocity *= -0.5;
		//	player1Velocity += player2;

		//	
		//}




		//mass collision
		if (CircleCollisionDetection(spriteWidth / 2, spriteWidth / 2, player1Position + spriteCentre1, player2Position + spriteCentre2)) {

			cout << "player 1 touch player 2" << endl;
		}
		if (mass1HP > 0) {
			if (CircleCollisionDetection(spriteWidth / 2, massSpriteWidth / 2, player1Position + spriteCentre1, mass1Position + massSpriteCentre1)) {
				mass1HP -= 1;
				player1Mass += mass1Mass;
				cout << "player 1 touch mass 1" << endl;
			}
		}
		if (mass2HP > 0) {
			if (CircleCollisionDetection(spriteWidth / 2, massSpriteWidth / 2, player1Position + spriteCentre1, mass2Position + massSpriteCentre2)) {
				mass2HP -= 1;
				player1Mass += mass2Mass;
				cout << "player 1 touch mass 2" << endl;
			}
		}




		player1ForceOn = false;
		player2ForceOn = false;
		wKeyPressed = false;
		aKeyPressed = false;
		sKeyPressed = false;
		dKeyPressed = false;
		leftKeyPressed = false;
		rightKeyPressed = false;
		upKeyPressed = false;
		downKeyPressed = false;
		spaceKeyPressed = false;
		player1Acceleration = D3DXVECTOR2(0, 0);
		player2Acceleration = D3DXVECTOR2(0, 0);
	}




}

void CleanupWindow()
{
	//	Free up the memory.
	UnregisterClass(wndClass.lpszClassName, GetModuleHandle(NULL));
}

void CreateMyDInput() {
	//	Direct Input object.



	//	Create the Direct Input object.
	HRESULT hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);

	//	Direct Input keyboard device.


	//	Create the keyboard device.
	hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);
	hr = dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);
	//	Set the input data format.
	dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	dInputMouseDevice->SetDataFormat(&c_dfDIMouse);

	//	Set the cooperative level.
	//	To Do:
	//	Try with different combination.
	dInputKeyboardDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	dInputMouseDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	///*---
	//	For buffered data
	//	//	Define buffer for input.
	//	//const int DEVICE_BUFFER_SIZE = 4;
	//	//DIDEVICEOBJECTDATA deviceBuffer[DEVICE_BUFFER_SIZE];

	//	////	Set the event buffer / properties.
	//	//DIPROPDWORD dipdw;
	//	//dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	//	//dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	//	//dipdw.diph.dwObj = 0;
	//	//dipdw.diph.dwHow = DIPH_DEVICE;
	//	//dipdw.dwData = DEVICE_BUFFER_SIZE;

	//	//hr = dInputKeyboardDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	//--*/



	//	Key input buffer


}

void CleanUpMyDInput() {
	//	Release keyboard device.
	dInputKeyboardDevice->Unacquire();
	dInputKeyboardDevice->Release();
	dInputKeyboardDevice = NULL;

	//	Release DirectInput.
	dInput->Release();
	dInput = NULL;
}

int CreateDXWindow()
{
	//	Define Direct3D 9.
	IDirect3D9* direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	//	Define how the screen presents.
	D3DPRESENT_PARAMETERS d3dPP;
	ZeroMemory(&d3dPP, sizeof(d3dPP));

	//	Refer to Direct3D 9 documentation for the meaning of the members.
	d3dPP.Windowed = true;
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dPP.BackBufferCount = 1;
	d3dPP.BackBufferWidth = MyWindowWidth;
	d3dPP.BackBufferHeight = MyWindowHeight;
	d3dPP.hDeviceWindow = g_hWnd;

	//	Create a Direct3D 9 device.
	//	Can guve reason
	HRESULT hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);

	hr = D3DXCreateSprite(d3dDevice, &sprite);

	//	To Do: Cout out the message to indicate the failure.
	if (FAILED(hr))
		return 0;
	return 1;
}

void GetInput() {

	//	Acquire the device.

	/*dInputKeyboardDevice->GetDeviceState(256, diKeys);*/
	dInputKeyboardDevice->Acquire();
	// Check the keyboard and see if any keys are currently being pressed
	dInputKeyboardDevice->GetDeviceState(sizeof(buffer), (LPVOID)&buffer);

	// Do something with the input
	// Here the KEYDOWN macro checks whether the left arrow key was pressed
	if (KEYDOWN(buffer, DIK_UP))
	{
		std::cout << "UP" << std::endl;
		upKeyPressed = true;
		player1ForceOn = true;
	}
	if (KEYDOWN(buffer, DIK_DOWN))
	{
		std::cout << "DOWN" << std::endl;
		downKeyPressed = true;
		player1ForceOn = true;
	}
	if (KEYDOWN(buffer, DIK_LEFT))
	{
		std::cout << "LEFT" << std::endl;
		leftKeyPressed = true;
	}
	if (KEYDOWN(buffer, DIK_RIGHT))
	{
		std::cout << "RIGHT" << std::endl;
		rightKeyPressed = true;
	}
	if (KEYDOWN(buffer, DIK_SPACE))
	{
		std::cout << "SPACE" << std::endl;
		spaceKeyPressed = true;
	}
	if (KEYDOWN(buffer, DIK_W))
	{
		std::cout << "W" << std::endl;
		wKeyPressed = true;
		player2ForceOn = true;
	}
	if (KEYDOWN(buffer, DIK_A))
	{
		std::cout << "A" << std::endl;
		aKeyPressed = true;
	}
	if (KEYDOWN(buffer, DIK_D))
	{
		std::cout << "D" << std::endl;
		dKeyPressed = true;
	}
	if (KEYDOWN(buffer, DIK_S))
	{
		std::cout << "S" << std::endl;
		sKeyPressed = true;
		player2ForceOn = true;
	}
	/*if (diKeys[DIK_UP] & 0x80)
	{
		std::cout << "UP" << std::endl;
		upKeyPressed = true;
	}
	if (diKeys[DIK_DOWN] & 0x80)
	{
		std::cout << "DOWN" << std::endl;
		downKeyPressed = true;
	}
	if (diKeys[DIK_LEFT] & 0x80)
	{
		std::cout << "LEFT" << std::endl;
		leftKeyPressed = true;
	}
	if (diKeys[DIK_RIGHT] & 0x80)
	{
		std::cout << "RIGHT" << std::endl;
		rightKeyPressed = true;
	}
	if (diKeys[DIK_SPACE] & 0x80)
	{
		std::cout << "SPACE" << std::endl;
		spaceKeyPressed = true;
	}*/
	dInputMouseDevice->Acquire();
	dInputMouseDevice->GetDeviceState(sizeof(mouseState), &mouseState);
	mouseposition.x += mouseState.lX;
	mouseposition.y += mouseState.lY;


}

void CleanupSXWindow()
{
	//	Release the device when exiting.
	d3dDevice->Release();
	//	Reset pointer to NULL, a good practice.
	d3dDevice = NULL;

	sprite->Release();
	sprite = NULL;

}

//void DrawClock()
//{
//	for (int i = 0; i < 12; i++)
//	{
//		int innerRadius = 80;
//		int outerRadius = 100;
//
//		float x = sin(i * 30 * 3.142 / 180) * innerRadius;
//		float y = -cos(i * 30 * 3.142 / 180) * innerRadius;
//
//		lineVertices[0] = D3DXVECTOR2(startPoint.x + x, startPoint.y + y);
//
//		x = sin(i * 30 * 3.142 / 180) * outerRadius;
//		y = -cos(i * 30 * 3.142 / 180) * outerRadius;
//
//		lineVertices[1] = D3DXVECTOR2(startPoint.x + x, startPoint.y + y);
//
//		line->Draw(lineVertices, 2, D3DCOLOR_XRGB(255, 255, 255));
//	}
//}

void Render()
{
	//	To Do:
		//	Update.

		//	Clear the back buffer.
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(red, green, blue), 1.0f, 0);

	//	Begin the scene
	d3dDevice->BeginScene();

	//	To Do:
	//	Drawing.
	//	Clear and begin scene


	//	Specify alpha blend will ensure that the sprite will render the background with alpha.
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMATRIX mat;


	//	Sprite rendering. Study the documentation.
	//sprite->Draw(texture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	//sprite->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	//sprite->Draw(texture, &spriteRect, NULL, &position, D3DCOLOR_XRGB(255, 255, 255));
	//sprite->Draw(cursor, &cursorRect, NULL, &position2, D3DCOLOR_XRGB(255, 255, 255));

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling1, &spriteCentre1, player1Direction, &player1Position);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, &player1AnimRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling2, &spriteCentre2, player2Direction, &player2Position);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, &player2AnimRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	//draw mass 1
	if (mass1HP > 0) {
		D3DXMatrixTransformation2D(&mat, NULL, 0.0, &massScaling1, &massSpriteCentre1, mass1Direction, &mass1Position);
		sprite->SetTransform(&mat);
		sprite->Draw(massTexture, &mass1AnimRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	}


	//draw mass 2
	if (mass2HP > 0) {
		D3DXMatrixTransformation2D(&mat, NULL, 0.0, &massScaling2, &massSpriteCentre2, mass2Direction, &mass2Position);
		sprite->SetTransform(&mat);
		sprite->Draw(massTexture, 0, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	}


	//	End sprite drawing
	sprite->End();



	//	End the scene
	d3dDevice->EndScene();

	//	Present the back buffer to screen
	d3dDevice->Present(NULL, NULL, NULL, NULL);



	//	End and present scene
}

//	use WinMain if you don't want the console
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	CreateWindows();
	CreateDXWindow();
	CreateMyDInput();
	InitializeLevel();



	timer->Init(60);
	while (WindowIsRunning())
	{
		GetInput();
		Update(timer->FramesToUpdate());
		Render();
	}
	CleanUpMyDInput();
	CleanLvWindow();
	CleanupSXWindow();
	CleanupWindow();



	return 0;
}
//--------------------------------------------------------------------

