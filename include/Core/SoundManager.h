#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <queue>
#include <string>
#include <mutex>

enum class SoundID {
    THREE,
    TWO,
    ONE,
    GO,
    HOVER,
    SOUND_COUNT
};

class SoundManager {
public:
    static SoundManager& getInstance();
    void loadSound(SoundID id, const std::string& filePath);
    void clearQueue();

    void playSound(SoundID id);
    void resumeSound();
    void pauseSound();

    sf::Music& getMusic();

private:
    SoundManager();
    void playSounds();

    sf::Music music;
    std::vector<sf::SoundBuffer> soundBuffers;

    sf::Thread soundThread;

    std::mutex queueMutex;
    std::queue<SoundID> soundQueue;

    std::mutex isPlayingMutex;
    bool isPlaying;

    bool isPaused;
};

#endif // SOUNDMANAGER_H
