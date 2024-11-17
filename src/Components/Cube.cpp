#include <glad/gl.h>
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

/*static std::array<std::size_t, 36> cubeIndices = {*/
/*    0, 1, 2, 2, 1, 3, // Back face*/
/*    4, 5, 6, 6, 5, 7, // Front face*/
/*    0, 2, 4, 4, 2, 6, // Left face*/
/*    1, 3, 5, 5, 3, 7, // Right face*/
/*    0, 1, 4, 4, 5, 1, // Bottom face*/
/*    2, 6, 3, 3, 6, 7  // Top face*/
/*};*/

Cube::Cube() :
        verticesArray(cubeIndices.size()),
        buffer(sf::TriangleStrip),
        Transformable3D()
{}

void Cube::init (bool viewedFromOutside) {
        if (!viewedFromOutside)
                std::reverse(cubeIndices.begin(), cubeIndices.end());

        size_t i = 0;
        for (const size_t index : cubeIndices) {
                verticesArray.at(i++) = Graphics::Vertex3D(
                        cubeVertices.at(index),
                        cubeTextureCoords.at(index)
                );
        }

        buffer.create(cubeIndices.size());
        buffer.update(verticesArray.data());
}

void Cube::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        sf::Shader::bind(states.shader);
        sf::Texture::bind(states.texture);
        sf::VertexBuffer::bind(&buffer);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(sf::Vertex), (void*)offsetof(sf::Vertex, position)); // Position
        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(sf::Vertex), (void*)offsetof(sf::Vertex, color)); // Color
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(sf::Vertex), (void*)offsetof(sf::Vertex, texCoords)); // Texture Coordinates

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, cubeIndices.size());

        sf::VertexBuffer::bind(NULL);
        sf::Texture::bind(NULL);
        sf::Shader::bind(NULL);
}
