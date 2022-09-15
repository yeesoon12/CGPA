#include "EnemyBullet.h"

void EnemyBullet::Initialization() {

}
void EnemyBullet::Update(){}
void EnemyBullet::Render(){}
BOOLEAN EnemyBullet::InBoundary(D3DXVECTOR2 position) {
	if (position.x < -250)
		return false;
	if (position.x > MyWindowWidth+200)
		return false;
	if (position.y < -250)
		return false;
	if(position.y> MyWindowHeight+200)
		return false;
	
	return true;
}

RECT EnemyBullet::GetColRect() {
	return colRect;
}
