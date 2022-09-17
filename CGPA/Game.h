#pragma once
#ifndef GAME_H
#define GAME_H

#include "Header.h"

class Game {
protected:
    int fps;
    RECT animRect;
    RECT colRect;

    int spriteWidth;
    int spriteHeight;
    int spriteCol;
    int spriteRow;

    int currentFrame;
    int maxFrame;

    int textureWidth;
    int textureHeight;

    D3DXVECTOR2 scaling;
    D3DXVECTOR2 centre;
    float direction;
    float rotation;


    D3DXVECTOR2 position;
    RECT cursorRect;
    D3DXVECTOR2 mouseposition;
    LPDIRECT3DTEXTURE9 cursor;
    LPDIRECT3DTEXTURE9 texture;
    float soundVolume;

public:
    Game();
    ~Game();

    virtual void Initialize();
    virtual void Render();
    virtual void CleanUp();
    virtual void Update(vector<Game*>*);
    virtual void Input();
};

#endif
