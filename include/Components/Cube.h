#ifndef CUBE_H
#define CUBE_H

#include "3DExtensions/Transformable3D.h"
#include "3DExtensions/VertexBuffer3D.h"
#include <SFML/Graphics.hpp>

class Cube
  : public sf::Drawable
  , public Transformable3D
{
  private:
    std::vector<Vertex3D> vertices;
    std::vector<GLuint> indices;

    VertexBuffer3D buffer;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  public:
    Cube();

    void init();
};

#endif // CUBE_H
