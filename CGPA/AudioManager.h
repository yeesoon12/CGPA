#pragma once
#include "fmod.hpp"
class AudioManager
{

private:
	float backgroundSound;
	float soundEffect;

public:
	FMOD::System* system;
	FMOD::Sound* levelExBGM, * Level1BGM, * UltiSound, * deathSound, * exploSound, * enemyBulletShoot1, * enemyBulletShoot2, * PowerUpSound, * EvoSound, *playerShoot;
	FMOD::Channel* channel = 0;
	char* channelGroup;
	FMOD::ChannelGroup* bgmGroup = 0;
	FMOD::ChannelGroup* seGroup = 0;
	FMOD_RESULT result;
	void* extraDriverData = 0;

	void InitializeAudio();
	void PlayLevelExBGM();
	void setBgmVolume(float);
	void setSeVolume(float);
	void PlayLevel1BGM();
	void PlayEvoSound();
	void PlayPlayerShoot();
	void PlayPowerUp();
	void PlayEnemyBulletShoot1();
	void PlayEnemyBulletShoot2();
	void PlayUltiSound();
	void PlayDeathSound();
	void PlayExploSound();
	float getBgmVolume();
	float getSeVolume();
	void LoadSounds();
	void UpdateSound();
	void stopBGM();
	AudioManager();
	~AudioManager();
};


