#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class TextureManager
{
  public:
    enum TextureID
    {
        ATLAS0,
        ATLAS1,
        ATLAS2,
        JEEP0
    };

    sf::Texture& getTexture(TextureID id);
    void loadTexture(const std::string& filePath);

    static TextureManager& getInstance();

  private:
    TextureManager();
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;
    std::vector<sf::Texture> textures;
};

#endif // TEXTURE_MANAGER_H
