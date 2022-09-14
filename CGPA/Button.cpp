#include "Button.h"

Button::~Button() {
}

void Button::Initialize()
{
	position = D3DXVECTOR2(0, 0);

	buttonWidth = 100;
	buttonHeight = 100;

	colRect.top = position.y;
	colRect.bottom = position.y + buttonHeight;
	colRect.left = position.x;
	colRect.right = position.x + buttonWidth;
}

void Button::Update() {
}

void Button::Render()
{

}

void Button::Input() {
}