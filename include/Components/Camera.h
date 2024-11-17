#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <SFML/Graphics.hpp>

enum class ProjectionType {
    Perspective,
    Orthographic
};

class Camera {
public:
	Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 5.0f),
		const glm::vec3& target = glm::vec3(0.0f, 0.0f, 0.0f),
		const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f),
		ProjectionType type = ProjectionType::Perspective);

	void setPosition(const glm::vec3& newPosition);
	void setTarget(const glm::vec3& newTarget);
	void setUp(const glm::vec3& newUp);
	void setProjection(const glm::mat4& newProjection);

	glm::mat4 getVP() const;
	void updateProjectionMatrix(ProjectionType type);

private:
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 up;
	glm::mat4 view;
	glm::mat4 projection;

	void updateViewMatrix();
};

#endif // CAMERA_H

