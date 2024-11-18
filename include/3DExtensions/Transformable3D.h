#ifndef TRANSFORMABLE_3D_H
#define TRANSFORMABLE_3D_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Transformable3D {
public:
	Transformable3D();

	const glm::vec3& getPosition() const;
	const glm::quat& getRotation() const;
	const glm::vec3& getScale() const;
	const glm::vec3& getOrigin() const;

	void setOrigin(float x, float y, float z);
	void setOrigin(const glm::vec3& origin);
	void setPosition(float x, float y, float z);
	void setPosition(const glm::vec3& position);
	void setRotation(float angle, const glm::vec3& axis);
	void setRotation(const glm::quat& rotation);
	void setScale(float factorX, float factorY, float factorZ);
	void setScale(const glm::vec3& scale);

	void move(float offsetX, float offsetY, float offsetZ);
	void move(const glm::vec3& offset);
	void rotate(float angle, const glm::vec3& axis);
	void scale(float factorX, float factorY, float factorZ);
	void scale(const glm::vec3& factor);

	const glm::mat4& getTransform() const;
	const glm::mat4& getInverseTransform() const;

private:
	glm::vec3 m_position;
	glm::vec3 m_origin;
	glm::vec3 m_scale;
	glm::quat m_rotation;

	mutable glm::mat4 m_transform;
	mutable glm::mat4 m_inverseTransform;
	mutable bool m_transformNeedUpdate;
	mutable bool m_inverseTransformNeedUpdate;

	void updateTransform() const;
};

#endif // TRANSFORMABLE_3D_H

