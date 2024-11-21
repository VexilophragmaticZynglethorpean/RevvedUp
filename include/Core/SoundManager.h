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
    SOUND_COUNT
};

class SoundManager {
public:
    static SoundManager& getInstance();
    void loadSound(SoundID id, const std::string& filePath);
    void playSound(SoundID id);
    sf::Music& getMusic();

private:
    SoundManager();
    void playSounds();

    sf::Music music;
    std::vector<sf::SoundBuffer> soundBuffers;
    std::queue<SoundID> soundQueue;
    sf::Thread soundThread;
    std::mutex queueMutex;
    std::mutex isPlayingMutex; // Mutex for isPlaying
    bool isPlaying;
};

#endif // SOUNDMANAGER_H
