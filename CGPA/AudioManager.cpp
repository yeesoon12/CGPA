#include "AudioManager.h"
void AudioManager::InitializeAudio()
{
    result = FMOD::System_Create(&system);
    result = system->init(32, FMOD_INIT_NORMAL, extraDriverData);
    result = system->createChannelGroup(channelGroup, &bgmGroup);
    result = system->createChannelGroup(channelGroup, &seGroup);
    backgroundSound=1.f;
    soundEffect=1.f;
    bgmGroup->setVolume(backgroundSound);
    LoadSounds();
}

void AudioManager::setBgmVolume(float volume) {
    backgroundSound = volume;
    bgmGroup->setVolume(backgroundSound);
}

void AudioManager::setSeVolume(float volume) {
    soundEffect = volume;
    seGroup->setVolume(soundEffect);
}

void AudioManager::PlayLevelExBGM()
{
    result = system->playSound(levelExBGM, bgmGroup, false, &channel);
   
}

void AudioManager::PlayLevel1BGM()
{
    result = system->playSound(Level1BGM, bgmGroup, false, &channel);
    

}

void AudioManager::PlayEvoSound()
{
    result = system->playSound(EvoSound, seGroup, false, &channel);
    channel->setVolume(soundEffect);
}

void AudioManager::PlayPowerUp()
{
    result = system->playSound(PowerUpSound, seGroup, false, &channel);

    channel->setVolume(soundEffect);
  
}


void AudioManager::PlayEnemyBulletShoot1()
{
    result = system->playSound(enemyBulletShoot1, seGroup, false, &channel);

    channel->setVolume(soundEffect);
}
void AudioManager::PlayEnemyBulletShoot2()
{
    result = system->playSound(enemyBulletShoot2, seGroup, false, &channel);

    channel->setVolume(soundEffect);
}

void AudioManager::PlayPlayerShoot()
{
    result = system->playSound(playerShoot, seGroup, false, &channel);

    channel->setVolume(soundEffect);
}
void AudioManager::PlayGunShoot()
{
    result = system->playSound(GunShoot, seGroup, false, &channel);

    channel->setVolume(soundEffect);
}

void AudioManager::PlayUltiSound()
{
    result = system->playSound(UltiSound, seGroup, false, &channel);

    channel->setVolume(soundEffect);

}

void AudioManager::PlayDeathSound()
{
    result = system->playSound(deathSound, seGroup, false, &channel);
    channel->setVolume(soundEffect);

}
void AudioManager::PlayExploSound() {
    result = system->playSound(exploSound, seGroup, false, &channel);

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
    result = EvoSound->setMode(FMOD_DEFAULT);

    result = system->createStream("Asset/GunShoot.mp3", FMOD_DEFAULT, 0, &playerShoot);
    result = playerShoot->setMode(FMOD_DEFAULT);
}

void AudioManager::UpdateSound()
{
    result = system->update();

}
void AudioManager::stopBGM() {
    bgmGroup->stop();
}

float AudioManager::getBgmVolume() {
    return backgroundSound;
}
float AudioManager::getSeVolume() {
    return soundEffect;
}

AudioManager::AudioManager() {

}

AudioManager::~AudioManager() {

}
// The value of sound volume should not be more than 1 and less than 0