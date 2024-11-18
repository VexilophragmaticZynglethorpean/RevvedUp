#include <glad/gl.h>
#include <Components/Cube.h>
#include <Core/Graphics.h>

Cube::Cube() :
        vertices(8),
        indices(8),
        buffer(sf::PrimitiveType::Points),
        Transformable3D()
{}

void Cube::init () {
        float size = 1.0f; // Size of the cube
        vertices.push_back(Vertex3D(sf::Vector3f(-size, -size, -size), sf::Vector2f(0, 0))); // Vertex 0
        vertices.push_back(Vertex3D(sf::Vector3f(size, -size, -size), sf::Vector2f(1, 0)));  // Vertex 1
        vertices.push_back(Vertex3D(sf::Vector3f(size, size, -size), sf::Vector2f(1, 1)));   // Vertex 2
        vertices.push_back(Vertex3D(sf::Vector3f(-size, size, -size), sf::Vector2f(0, 1)));  // Vertex 3
        vertices.push_back(Vertex3D(sf::Vector3f(-size, -size, size), sf::Vector2f(0, 0)));   // Vertex 4
        vertices.push_back(Vertex3D(sf::Vector3f(size, -size, size), sf::Vector2f(1, 0)));    // Vertex 5
        vertices.push_back(Vertex3D(sf::Vector3f(size, size, size), sf::Vector2f(1, 1)));     // Vertex 6
        vertices.push_back(Vertex3D(sf::Vector3f(-size, size, size), sf::Vector2f(0, 1)));    // Vertex 7

        // Define the indices for the cube (two triangles per face)
        indices = {
        0, 1, 2, 0, 2, 3, // Back face
        4, 5, 6, 4, 6, 7, // Front face
        0, 1, 5, 0, 5, 4, // Bottom face
        3, 2, 6, 3, 6, 7, // Top face
        0, 3, 7, 0, 7, 4, // Left face
        1, 2, 6, 1, 6, 5  // Right face
        };

        buffer.create();
        buffer.update(vertices, indices);
}

void Cube::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        buffer.bind();
        sf::Texture::bind(states.texture);
        sf::Shader::bind(states.shader);

        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);
        glUseProgram(0);
}
