#include "Header.h"
#include "Game.h"
#include "MainMenu.h"
#include "Level1.h"
#include <stack>
//Window's Global
HWND g_hWnd = NULL;
WNDCLASS wndClass;
HRESULT hr;
IDirect3DDevice9* d3dDevice;
LPDIRECTINPUT8 dInput;
LPDIRECTINPUTDEVICE8 dInputKeyboardDevice;
BYTE diKeys[256];
LPDIRECTINPUTDEVICE8 dInputMouseDevice;
DIMOUSESTATE mouseState;
LPD3DXSPRITE sprite = NULL;
LPD3DXLINE line = NULL;
int counter;
int gameFPS;
FrameTimer* timer = new FrameTimer();
vector<Game*> game;
MainMenu* mainMenu = new MainMenu();
Level1* level1 = new Level1();

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message)
	{
		//	The message is post when we destroy the window.
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void CreateMyWindow() {
	ZeroMemory(&wndClass, sizeof(wndClass));

	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hInstance = GetModuleHandle(NULL);
	wndClass.lpfnWndProc = WindowProcedure;
	wndClass.lpszClassName = "My Window";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);

	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "Touhou?", WS_OVERLAPPEDWINDOW, 450, 0, MyWindowWidth, MyWindowHeight, NULL, NULL, GetModuleHandle(NULL), NULL);
	ShowWindow(g_hWnd, 1);
}

int CreateMy3D() {
	IDirect3D9* direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dPP;
	ZeroMemory(&d3dPP, sizeof(d3dPP));

	d3dPP.Windowed = true;
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dPP.BackBufferCount = 1;
	d3dPP.BackBufferWidth = MyWindowWidth;
	d3dPP.BackBufferHeight = MyWindowHeight;
	d3dPP.hDeviceWindow = g_hWnd;

	hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);

	hr = D3DXCreateSprite(d3dDevice, &sprite);

	hr = D3DXCreateLine(d3dDevice, &line);


	if (FAILED(hr)) {
		cout << "sprite creation error" << endl;
		return 0;
	}

	return 1;
}

void CreateMyDirectInput() {

	hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);

	hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);

	hr = dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);

	dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	dInputMouseDevice->SetDataFormat(&c_dfDIMouse);

	dInputKeyboardDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	dInputMouseDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
}

void InitializeLevel() {

	srand(time(0));
	mainMenu->Initialize();
	if (FAILED(hr)) {
		cout << "Failed to create player texture." << endl;
	}
}


int IfMyWindowIsRunning() {

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	if (msg.message != WM_QUIT)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) {
				return false;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	else {
		return false;
	}
	return true;
}

void CleanUpMyWindow() {
	UnregisterClass(wndClass.lpszClassName, GetModuleHandle(NULL));
}

void CleanUpLevel() {

}

void CleanUpMyDirectX() {
	sprite->Release();
	sprite = NULL;

	d3dDevice->Release();
	d3dDevice = NULL;

	line->Release();
	line = NULL;
}

void CleanUpMyDirectInput() {
	dInputKeyboardDevice->Unacquire();
	dInputKeyboardDevice->Release();
	dInputKeyboardDevice = NULL;

	dInputMouseDevice->Unacquire();
	dInputMouseDevice->Release();
	dInputMouseDevice = NULL;

	dInput->Release();
	dInput = NULL;

}
void Update(int FrameToUpdate) {
	for (int i = 0; i < FrameToUpdate; i++) {
		game.front()->Update();
	}
	

}

int main() {
	CreateMyWindow();
	CreateMy3D();
	CreateMyDirectInput();
	InitializeLevel();
	
	game.push_back(mainMenu);
	timer->Init(60);
	while (IfMyWindowIsRunning())
	{
		game.front()->Input();
		Update(timer->FramesToUpdate());
		game.front()->Render();

	}
	CleanUpMyDirectInput();
	CleanUpMyDirectX();
	CleanUpLevel();
	CleanUpMyWindow();

	return 0;

}