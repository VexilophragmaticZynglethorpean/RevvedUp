#include "3DExtensions/Transformable3D.h"

Transformable3D::Transformable3D()
  : m_position(0.0f)
  , m_origin(0.0f)
  , m_scale(1.0f)
  , m_rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f))
  , m_transformNeedUpdate(true)
  , m_inverseTransformNeedUpdate(true)
{
}

void
Transformable3D::setOrigin(float x, float y, float z)
{
    m_origin = glm::vec3(x, y, z);
    m_transformNeedUpdate = true;
}

void
Transformable3D::setOrigin(const glm::vec3& origin)
{
    m_origin = origin;
    m_transformNeedUpdate = true;
}

void
Transformable3D::setPosition(float x, float y, float z)
{
    m_position = glm::vec3(x, y, z);
    m_transformNeedUpdate = true;
}

void
Transformable3D::setPosition(const glm::vec3& position)
{
    m_position = position;
    m_transformNeedUpdate = true;
}

void
Transformable3D::setRotation(float angle, const glm::vec3& axis)
{
    m_rotation = glm::angleAxis(glm::radians(angle), glm::normalize(axis));
    m_transformNeedUpdate = true;
}

void
Transformable3D::setRotation(const glm::quat& rotation)
{
    m_rotation = rotation;
    m_transformNeedUpdate = true;
}

void
Transformable3D::setScale(float factorX, float factorY, float factorZ)
{
    m_scale = glm::vec3(factorX, factorY, factorZ);
    m_transformNeedUpdate = true;
}

void
Transformable3D::setScale(const glm::vec3& scale)
{
    m_scale = scale;
    m_transformNeedUpdate = true;
}

const glm::vec3&
Transformable3D::getPosition() const
{
    return m_position;
}

const glm::quat&
Transformable3D::getRotation() const
{
    return m_rotation;
}

const glm::vec3&
Transformable3D::getScale() const
{
    return m_scale;
}

const glm::vec3&
Transformable3D::getOrigin() const
{
    return m_origin;
}

void
Transformable3D::move(float offsetX, float offsetY, float offsetZ)
{
    m_position += glm::vec3(offsetX, offsetY, offsetZ);
    m_transformNeedUpdate = true;
}

void
Transformable3D::move(const glm::vec3& offset)
{
    m_position += offset;
    m_transformNeedUpdate = true;
}

void
Transformable3D::rotate(float angle, const glm::vec3& axis)
{
    glm::quat rotation =
      glm::angleAxis(glm::radians(angle), glm::normalize(axis));
    m_rotation = rotation * m_rotation;
    m_transformNeedUpdate = true;
}

void
Transformable3D::scale(float factorX, float factorY, float factorZ)
{
    m_scale *= glm::vec3(factorX, factorY, factorZ);
    m_transformNeedUpdate = true;
}

void
Transformable3D::scale(const glm::vec3& factor)
{
    m_scale *= factor;
    m_transformNeedUpdate = true;
}

const glm::mat4&
Transformable3D::getTransform() const
{
    if (m_transformNeedUpdate) {
        updateTransform();
    }
    return m_transform;
}

const glm::mat4&
Transformable3D::getInverseTransform() const
{
    if (m_inverseTransformNeedUpdate) {
        updateTransform();
    }
    return m_inverseTransform;
}

void
Transformable3D::updateTransform() const
{
    m_transform = glm::mat4(1.0f);
    m_transform = glm::scale(m_transform, m_scale);
    m_transform *= glm::mat4_cast(m_rotation);
    m_transform = glm::translate(m_transform, m_position - m_origin);
    m_inverseTransform = glm::inverse(m_transform);
    m_transformNeedUpdate = false;
    m_inverseTransformNeedUpdate = false;
}
