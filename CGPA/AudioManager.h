#pragma once
#include "fmod.hpp"
class AudioManager
{

public:
	FMOD::System* system;
	FMOD::Sound* sound1, * sound2, * soundTrack1;
	FMOD::Channel* channel = 0;
	FMOD_RESULT result;
	void* extraDriverData = 0;

	void InitializeAudio();
	void PlaySound1();
	void PlaySound2();
	void PlaySoundTrack1();
	void LoadSounds();
	void UpdateSound();

	AudioManager();
	~AudioManager();
};


