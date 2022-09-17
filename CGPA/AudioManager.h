#pragma once
#include "fmod.hpp"
class AudioManager
{

private:
	float backgroundSound;
	float soundEffect;

public:
	FMOD::System* system;
	FMOD::Sound* levelExBGM, * Level1BGM, * GunShoot, * UltiSound, * deathSound, * exploSound, * enemyBulletShoot1, * enemyBulletShoot2, * PowerUpSound, * EvoSound;
	FMOD::Channel* channel = 0;
	FMOD_RESULT result;
	void* extraDriverData = 0;

	void InitializeAudio();
	void PlayLevelExBGM();
	void PlayLevel1BGM();
	void PlayEvoSound();
	void PlayGunShoot();
	void PlayPowerUp();
	void PlayEnemyBulletShoot1();
	void PlayEnemyBulletShoot2();
	void PlayUltiSound();
	void PlayDeathSound();
	void PlayExploSound();
	void LoadSounds();
	void UpdateSound();
	float CheckSoundVolume(float);
	void editSoundEffect(float);
	void editBGM(float);
	AudioManager();
	~AudioManager();
};


