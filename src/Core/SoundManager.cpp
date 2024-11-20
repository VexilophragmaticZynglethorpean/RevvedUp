#include "Core/SoundManager.h"

SoundManager::SoundManager() 
    : soundBuffers(static_cast<std::size_t>(SoundID::SOUND_COUNT)), 
      soundThread(&SoundManager::playSounds, this),
      isPlaying(false) {}

SoundManager& SoundManager::getInstance() {
    static SoundManager instance;
    return instance;
}

void SoundManager::loadSound(SoundID id, const std::string& filePath) {
    soundBuffers.at(static_cast<std::size_t>(id)).loadFromFile(filePath);
}

void SoundManager::playSound(SoundID id) {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        soundQueue.push(id);
    }
    
    {
        std::lock_guard<std::mutex> lock(isPlayingMutex);
        if (!isPlaying) {
            isPlaying = true;
            soundThread.launch();
        }
    }
}

void SoundManager::playSounds() {
    while (true) {
        SoundID id;
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            if (!soundQueue.empty()) {
                id = soundQueue.front();
                soundQueue.pop();
            } else {
                {
                    std::lock_guard<std::mutex> lock(isPlayingMutex);
                    isPlaying = false;
                }
                return;
            }
        }

        sf::Sound sound;
        sound.setBuffer(soundBuffers.at(static_cast<size_t>(id)));
        sound.play();

        while (sound.getStatus() == sf::Sound::Playing) {
            sf::sleep(sf::milliseconds(100));
        }
    }
}
