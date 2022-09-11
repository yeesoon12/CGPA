#pragma once

#ifndef HEADER_H
#define HEADER_H

// include perpustakaan
#define WIN32_LEAN_AND_MEAN
#define BUTTONDOWN(name, key) (name.rgbButtons[key] & 0x80)

#define MyWindowWidth 600
#define MyWindowHeight 900

#include <iostream>
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "fmod_vc.lib")

#include "AudioManager.h"
#include "FrameTimer.h"

using namespace std;
extern LPD3DXSPRITE sprite;
extern IDirect3DDevice9* d3dDevice;
extern LPDIRECTINPUT8 dInput;
extern LPDIRECTINPUTDEVICE8 dInputKeyboardDevice;
extern LPDIRECTINPUTDEVICE8 dInputMouseDevice;
extern DIMOUSESTATE mouseState;
extern BYTE diKeys[256];
extern AudioManager* audioManager;


#endif
