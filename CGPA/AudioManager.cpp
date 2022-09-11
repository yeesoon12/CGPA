#include "AudioManager.h"
void AudioManager::InitializeAudio()
{
    result = FMOD::System_Create(&system);
    result = system->init(32, FMOD_INIT_NORMAL, extraDriverData);
}

void AudioManager::PlaySound1()
{
    result = system->playSound(sound1, 0, false, &channel);
}

void AudioManager::PlaySound2()
{
    result = system->playSound(sound2, 0, false, &channel);
}

void AudioManager::PlaySoundTrack1()
{
    result = system->playSound(soundTrack1, 0, false, &channel);
    channel->setVolume(1);
    channel->setPan(-1);
}

void AudioManager::LoadSounds()
{
    result = system->createSound("conga.wav", FMOD_DEFAULT, 0, &sound1);
    result = sound1->setMode(FMOD_LOOP_OFF);

    result = system->createSound("conga.wav", FMOD_DEFAULT, 0, &sound2);
    result = sound1->setMode(FMOD_LOOP_OFF);


    result = system->createStream("Asset/explo.ogg", FMOD_DEFAULT, 0, &soundTrack1);
    result = sound1->setMode(FMOD_LOOP_NORMAL);
}

void AudioManager::UpdateSound()
{
    result = system->update();
}

AudioManager::AudioManager() {

}

AudioManager::~AudioManager() {

}