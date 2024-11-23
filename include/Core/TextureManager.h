#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "SFML/Graphics/RenderTexture.hpp"
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <vector>

enum class TextureID
{
    ATLAS0,
    ATLAS1,
    ATLAS2,
    GHOST,
    CAR0,
    MENU_BACKGROUND,
    TEXTURE_COUNT
};

class TextureManager
{
  private:
    TextureManager();
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;
    std::vector<sf::Texture> textures;
    sf::RenderTexture renderTexture;

  public:
    sf::Texture& getTexture(TextureID id);
    void loadTexture(const TextureID id, const std::filesystem::path& filePath);
    sf::RenderTexture& getRenderTexture();

    static TextureManager& getInstance();
};

#endif // TEXTURE_MANAGER_H
