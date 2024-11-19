#include "Core/TextureManager.h"
#include "Util/Path.h"
#include <iostream>

TextureManager::TextureManager()
{
    loadTexture(Util::getExecutablePath() / "assets/atlas0.png");
    loadTexture(Util::getExecutablePath() / "assets/atlas1.png");
    loadTexture(Util::getExecutablePath() / "assets/atlas2.png");
    loadTexture(Util::getExecutablePath() / "assets/jeep0.png");
}

TextureManager&
TextureManager::getInstance()
{
    static TextureManager instance;
    return instance;
}

sf::Texture&
TextureManager::getTexture(TextureID id)
{
    if (id < 0 || id >= textures.size()) {
        throw std::out_of_range("Invalid texture ID");
    }
    return textures[id];
}

void
TextureManager::loadTexture(const std::string& filePath)
{
    sf::Texture texture;
    if(!texture.loadFromFile(filePath)) std::cerr << "Err";
    textures.push_back(std::move(texture));
}
