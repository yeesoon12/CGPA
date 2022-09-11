#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include<iostream>
#include <dinput.h>
class Object
{ public:
	LPDIRECT3DTEXTURE9 texture;
	int textureWidth;
	int textureHeight;
	int spriteWidth;
	int spriteHeight;
	int spriteRow;
	int spriteColum;
	RECT ColRect;
	RECT AnimRect;
	D3DXVECTOR2 Position;
	D3DXVECTOR2 Velocity;
	D3DXVECTOR2 Acceleration;
	D3DXVECTOR2 scaling;
	D3DXVECTOR2 spriteCentre;
	int CurrentFrame;
	float Direction;
	int objectID;
	float RoatationSpeed;
	int Mass;
};






