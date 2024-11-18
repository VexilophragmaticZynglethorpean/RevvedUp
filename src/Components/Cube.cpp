#include "SFML/Graphics/PrimitiveType.hpp"
#include <glad/gl.h>
#include <Components/Cube.h>
#include <Core/Graphics.h>
/*#include <array>*/

/*static std::array<sf::Vector3f, 8> cubeVertices = {{*/
/*        sf::Vector3f( -0.5, -0.5, -0.5 ),*/
/*        sf::Vector3f( +0.5, -0.5, -0.5 ),*/
/*        sf::Vector3f( -0.5, +0.5, -0.5 ),*/
/*        sf::Vector3f( +0.5, +0.5, -0.5 ),*/
/*        sf::Vector3f( -0.5, -0.5, +0.5 ),*/
/*        sf::Vector3f( +0.5, -0.5, +0.5 ),*/
/*        sf::Vector3f( -0.5, +0.5, +0.5 ),*/
/*        sf::Vector3f( +0.5, +0.5, +0.5 ),*/
/*}};*/
/**/
/*static std::array<sf::Vector2f, 8> cubeTextureCoords = {{*/
/*        sf::Vector2f( 0, 0 ),*/
/*        sf::Vector2f( 0, 0 ),*/
/*        sf::Vector2f( 0, 0 ),*/
/*        sf::Vector2f( 0, 0 ),*/
/*        sf::Vector2f( 0, 0 ),*/
/*        sf::Vector2f( 0, 0 ),*/
/*        sf::Vector2f( 0, 0 ),*/
/*        sf::Vector2f( 0, 0 ),*/
/*}};*/
/**/
/*enum cubeIndex {*/
/*        BACK = 0b000, */
/*        FRONT = 0b100,*/
/**/
/*        BOTTOM = 0b000, */
/*        TOP = 0b010,*/
/**/
/*        LEFT = 0b000, */
/*        RIGHT = 0b001*/
/*};*/
/**/
/*static std::array<std::size_t, 14> cubeIndices = {*/
/*    BACK | TOP | RIGHT,*/
/*    BACK | TOP | LEFT,*/
/*    BACK | BOTTOM | RIGHT,*/
/*    BACK | BOTTOM | LEFT,*/
/*    FRONT | BOTTOM | LEFT,*/
/*    BACK | TOP | LEFT,*/
/*    FRONT | TOP | LEFT,*/
/*    BACK | TOP | RIGHT,*/
/*    FRONT | TOP | RIGHT,*/
/*    BACK | BOTTOM | RIGHT,*/
/*    FRONT | BOTTOM | RIGHT,*/
/*    FRONT | BOTTOM | LEFT,*/
/*    FRONT | TOP | RIGHT,*/
/*    FRONT | TOP | LEFT,*/
/*};*/

/*static std::array<std::size_t, 36> cubeIndices = {*/
/*    0, 1, 2, 2, 1, 3, // Back face*/
/*    4, 5, 6, 6, 5, 7, // Front face*/
/*    0, 2, 4, 4, 2, 6, // Left face*/
/*    1, 3, 5, 5, 3, 7, // Right face*/
/*    0, 1, 4, 4, 5, 1, // Bottom face*/
/*    2, 6, 3, 3, 6, 7  // Top face*/
/*};*/

Cube::Cube() :
        verticesArray(8),
        /*verticesArray(cubeIndices.size()),*/
        buffer(sf::PrimitiveType::Points),
        Transformable3D()
{}

void Cube::init (bool viewedFromOutside) {
        /*if (!viewedFromOutside)*/
        /*        std::reverse(cubeIndices.begin(), cubeIndices.end());*/
        /**/
        /*size_t i = 0;*/
        /*for (const size_t index : cubeIndices) {*/
        /*        verticesArray.at(i++) = Vertex3D(*/
        /*                cubeVertices.at(index),*/
        /*                cubeTextureCoords.at(index)*/
        /*        );*/
        /*}*/

	verticesArray.emplace_back(sf::Vector3f(-0.45f,  0.45f, -0.45f), sf::Vector2f(0.0f, 0.0f));
	verticesArray.emplace_back(sf::Vector3f( 0.45f,  0.45f, -0.45f), sf::Vector2f(1.0f, 0.0f));
	verticesArray.emplace_back(sf::Vector3f( 0.45f, -0.45f, -0.45f), sf::Vector2f(1.0f, 1.0f));
	verticesArray.emplace_back(sf::Vector3f(-0.45f, -0.45f, -0.45f), sf::Vector2f(0.0f, 1.0f));
	verticesArray.emplace_back(sf::Vector3f(-0.45f,  0.45f,  0.45f), sf::Vector2f(0.0f, 0.0f));
	verticesArray.emplace_back(sf::Vector3f( 0.45f,  0.45f,  0.45f), sf::Vector2f(1.0f, 0.0f));
	verticesArray.emplace_back(sf::Vector3f( 0.45f, -0.45f,  0.45f), sf::Vector2f(1.0f, 1.0f));
	verticesArray.emplace_back(sf::Vector3f(-0.45f, -0.45f,  0.45f), sf::Vector2f(0.0f, 1.0f));

        buffer.create();
        buffer.update(verticesArray);
}

void Cube::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        buffer.bind();
        sf::Texture::bind(states.texture);
        sf::Shader::bind(states.shader);

        /*glDrawArrays(GL_TRIANGLE_STRIP, 0, cubeIndices.size());*/

        glDrawArrays(GL_POINTS, 0, 8);
}
