#include "EnemyBulletCombination.h"

void EnemyBulletCombination::Initialization(float direction,D3DXVECTOR2 position, int bulletPa) {
	count = 0;
	count2=0;
	this->direction = direction;
	this->position = position;
	if(bulletPa==1){
	for(int j =0; j<30; j++){
		
			knife = new EnemyKnife();
			knife->Initialization(this->direction, this->position);
			bulletpattern1.push_back(knife);
			this->direction +=3.142/15;
		
	}
	}
	else if(bulletPa==2){
	for (int j = 0; j < 5; j++) {
		
		smallKnife = new EnemySmallKnife();
		smallKnife->Initialization(this->direction, this->position);
		bulletpattern2.push_back(smallKnife);
		this->direction += 0.05;

	}
	}
	else if (bulletPa == 3) {
		for (int j = 0; j < 3; j++) {

			enegryBall = new EnemyBall();
			enegryBall->Initialization(this->direction, this->position);
			bulletpattern3.push_back(enegryBall);
			this->direction += 0.05;

		}
	}


}

void EnemyBulletCombination::Update() {




}
void EnemyBulletCombination::Render() {

	
}
vector<EnemyBullet*> EnemyBulletCombination::getBulletPattern1() {
	return bulletpattern1;
}

vector<EnemyBullet*> EnemyBulletCombination::getBulletPattern2() {
	return bulletpattern2;
}

vector<EnemyBullet*> EnemyBulletCombination::getBulletPattern3() {
	return bulletpattern3;
}



