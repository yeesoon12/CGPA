#include "AudioManager.h"
void AudioManager::InitializeAudio()
{
    result = FMOD::System_Create(&system);
    result = system->init(32, FMOD_INIT_NORMAL, extraDriverData);
}

void AudioManager::PlayLevelExBGM()
{
    result = system->playSound(levelExBGM, 0, false, &channel);
    channel->setVolume(0.6);
}

void AudioManager::PlayLevel1BGM()
{
    result = system->playSound(Level1BGM, 0, false, &channel);
    channel->setVolume(0.6);
}

void AudioManager::PlayGunShoot()
{
    result = system->playSound(GunShoot, 0, false, &channel);
}

void AudioManager::PlayUltiSound()
{
    result = system->playSound(UltiSound, 0, false, &channel);

}

void AudioManager::PlayDeathSound()
{
    result = system->playSound(deathSound, 0, false, & channel);

}

void AudioManager::LoadSounds()
{
    result = system->createSound("Asset/levelExBGM.mp3", FMOD_DEFAULT, 0, &levelExBGM);
    result = levelExBGM->setMode(FMOD_LOOP_NORMAL);

    result = system->createSound("Asset/Level1BGM.mp3", FMOD_DEFAULT, 0, &Level1BGM);
    result = Level1BGM->setMode(FMOD_LOOP_NORMAL);

    result = system->createSound("Asset/GunShoot.mp3", FMOD_DEFAULT, 0, &GunShoot);
    result = GunShoot->setMode(FMOD_DEFAULT);


    result = system->createStream("Asset/UltiSound.mp3", FMOD_DEFAULT, 0, &UltiSound);
    result = UltiSound->setMode(FMOD_DEFAULT);

    result = system->createStream("Asset/death.mp3", FMOD_DEFAULT, 0, &deathSound);
    result = deathSound->setMode(FMOD_DEFAULT);
}

void AudioManager::UpdateSound()
{
    result = system->update();
}

AudioManager::AudioManager() {

}

AudioManager::~AudioManager() {

}