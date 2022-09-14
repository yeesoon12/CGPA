#pragma once
#include "fmod.hpp"
class AudioManager
{

public:
	FMOD::System* system;
	FMOD::Sound* Level1BGM, * GunShoot, * UltiSound;
	FMOD::Channel* channel = 0;
	FMOD_RESULT result;
	void* extraDriverData = 0;

	void InitializeAudio();
	void PlayLevel1BGM();
	void PlayGunShoot();
	void PlayUltiSound();
	void LoadSounds();
	void UpdateSound();

	AudioManager();
	~AudioManager();
};


