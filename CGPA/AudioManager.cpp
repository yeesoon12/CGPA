#include "AudioManager.h"
void AudioManager::InitializeAudio()
{
    result = FMOD::System_Create(&system);
    result = system->init(32, FMOD_INIT_NORMAL, extraDriverData);
    backgroundSound=1.f;
    soundEffect=1.f;
}

void AudioManager::PlayLevelExBGM()
{
    result = system->playSound(levelExBGM, 0, false, &channel);
    channel->setVolume(0.6);
}

void AudioManager::PlayLevel1BGM()
{
    result = system->playSound(Level1BGM, 0, false, &channel);
    
    backgroundSound = CheckSoundVolume(backgroundSound);
  
    channel->setVolume(backgroundSound);
}

void AudioManager::PlayEvoSound()
{
    result = system->playSound(EvoSound, 0, false, &channel);
    soundEffect = CheckSoundVolume(soundEffect);
    channel->setVolume(soundEffect);
}

void AudioManager::PlayPowerUp()
{
    result = system->playSound(PowerUpSound, 0, false, &channel);
    soundEffect = CheckSoundVolume(soundEffect);
    channel->setVolume(soundEffect);
  
}


void AudioManager::PlayEnemyBulletShoot1()
{
    result = system->playSound(enemyBulletShoot1, 0, false, &channel);
    soundEffect = CheckSoundVolume(soundEffect);
    channel->setVolume(soundEffect);
}
void AudioManager::PlayEnemyBulletShoot2()
{
    result = system->playSound(enemyBulletShoot2, 0, false, &channel);
        soundEffect = CheckSoundVolume(soundEffect);
    channel->setVolume(soundEffect);
}
void AudioManager::PlayGunShoot()
{
    result = system->playSound(GunShoot, 0, false, &channel);
    soundEffect = CheckSoundVolume(soundEffect);
    channel->setVolume(soundEffect);
}

void AudioManager::PlayUltiSound()
{
    result = system->playSound(UltiSound, 0, false, &channel);
    soundEffect = CheckSoundVolume(soundEffect);
    channel->setVolume(soundEffect);

}

void AudioManager::PlayDeathSound()
{
    result = system->playSound(deathSound, 0, false, &channel);
    soundEffect = CheckSoundVolume(soundEffect);
    channel->setVolume(soundEffect);

}
void AudioManager::PlayExploSound() {
    result = system->playSound(exploSound, 0, false, &channel);
    soundEffect = CheckSoundVolume(soundEffect);
    channel->setVolume(soundEffect);
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

    result = system->createStream("Asset/BossExplo.mp3", FMOD_DEFAULT, 0, &exploSound);
    result = exploSound->setMode(FMOD_DEFAULT);

    result = system->createStream("Asset/EnemyBulletShoot1.mp3", FMOD_DEFAULT, 0, &enemyBulletShoot1);
    result = enemyBulletShoot1->setMode(FMOD_DEFAULT);

    result = system->createStream("Asset/EnemyBulletShoot2.mp3", FMOD_DEFAULT, 0, &enemyBulletShoot2);
    result = enemyBulletShoot2->setMode(FMOD_DEFAULT);

    result = system->createStream("Asset/PowerUpSound.mp3", FMOD_DEFAULT, 0, &PowerUpSound);
    result = PowerUpSound->setMode(FMOD_DEFAULT);
    result = system->createStream("Asset/Evo.mp3", FMOD_DEFAULT, 0, &EvoSound);
    result = PowerUpSound->setMode(FMOD_DEFAULT);
}

void AudioManager::UpdateSound()
{
    result = system->update();

}

AudioManager::AudioManager() {

}

AudioManager::~AudioManager() {

}
float AudioManager::CheckSoundVolume(float soundVolume) {
    if (soundVolume <= 0)
        return 0;
    if (soundVolume >= 1)
        return 1;
    return soundVolume;
}

void AudioManager:: editSoundEffect(float soundVolume) {
    soundEffect += soundVolume;
}

void AudioManager::editBGM(float soundVolume) {
    backgroundSound += soundVolume;
}