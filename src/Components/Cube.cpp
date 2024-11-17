#include <Components/Cube.h>
#include <Core/Graphics.h>
#include <array>

static std::array<sf::Vector3f, 8> cubeVertices = {{
        sf::Vector3f( -0.5, -0.5, -0.5 ),
        sf::Vector3f( +0.5, -0.5, -0.5 ),
        sf::Vector3f( -0.5, +0.5, -0.5 ),
        sf::Vector3f( +0.5, +0.5, -0.5 ),
        sf::Vector3f( -0.5, -0.5, +0.5 ),
        sf::Vector3f( +0.5, -0.5, +0.5 ),
        sf::Vector3f( -0.5, +0.5, +0.5 ),
        sf::Vector3f( +0.5, +0.5, +0.5 ),
}};

static std::array<sf::Vector2f, 8> cubeTextureCoords = {{
        sf::Vector2f( 0, 0 ),
        sf::Vector2f( 0, 0 ),
        sf::Vector2f( 0, 0 ),
        sf::Vector2f( 0, 0 ),
        sf::Vector2f( 0, 0 ),
        sf::Vector2f( 0, 0 ),
        sf::Vector2f( 0, 0 ),
        sf::Vector2f( 0, 0 ),
}};

enum cubeIndex {
        BACK = 0b000, 
        FRONT = 0b100,

        BOTTOM = 0b000, 
        TOP = 0b010,

        LEFT = 0b000, 
        RIGHT = 0b001
};

static std::array<std::size_t, 14> cubeIndices = {
    BACK | TOP | RIGHT,
    BACK | TOP | LEFT,
    BACK | BOTTOM | RIGHT,
    BACK | BOTTOM | LEFT,
    FRONT | BOTTOM | LEFT,
    BACK | TOP | LEFT,
    FRONT | TOP | LEFT,
    BACK | TOP | RIGHT,
    FRONT | TOP | RIGHT,
    BACK | BOTTOM | RIGHT,
    FRONT | BOTTOM | RIGHT,
    FRONT | BOTTOM | LEFT,
    FRONT | TOP | RIGHT,
    FRONT | TOP | LEFT,
};


Cube::Cube() :
        verticesArray(sf::TriangleStrip, cubeIndices.size()),
        texture(nullptr),
        Transformable3D()
{}

void Cube::init(
        std::shared_ptr <sf::RenderTarget> window,
        std::shared_ptr <const sf::Texture> textureAtlas,
        bool viewedFromOutside
) {
        texture = textureAtlas;

        if (!viewedFromOutside)
                std::reverse(cubeIndices.begin(), cubeIndices.end());

        for (const size_t index : cubeIndices) {
                verticesArray.append( Graphics::Vertex3D(
                        window,
                        cubeVertices.at(index),
                        textureAtlas,
                        cubeTextureCoords.at(index)
                ));
        }
}

void Cube::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.texture = texture.get();
        target.draw(verticesArray, states);
}
