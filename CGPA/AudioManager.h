#pragma once
#include "fmod.hpp"
class AudioManager
{

public:
	FMOD::System* system;
	FMOD::Sound* levelExBGM, * Level1BGM, * GunShoot, * UltiSound, * deathSound;
	FMOD::Channel* channel = 0;
	FMOD_RESULT result;
	void* extraDriverData = 0;

	void InitializeAudio();
	void PlayLevelExBGM();
	void PlayLevel1BGM();
	void PlayGunShoot();
	void PlayUltiSound();
	void PlayDeathSound();
	void LoadSounds();
	void UpdateSound();

	AudioManager();
	~AudioManager();
};


