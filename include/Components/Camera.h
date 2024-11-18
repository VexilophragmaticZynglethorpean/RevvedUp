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
	Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
		const glm::vec3& target = glm::vec3(0.0f, 0.0f, 0.0f),
		const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f),
		ProjectionType type = ProjectionType::Perspective);

	Camera& setPosition(const glm::vec3& newPosition);
	Camera& setTarget(const glm::vec3& newTarget);
	Camera& setUp(const glm::vec3& newUp);
	Camera& setFOV(float fov);
	Camera& setAspectRatio(float aspect = 0.0f);
	Camera& setNearFar(float near, float far);
	Camera& setProjection(ProjectionType type);

	glm::mat4 getVP() const;

	void updateProjectionMatrix();
	void updateViewMatrix();
	void update();

private:
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 up;
	glm::mat4 view;
	glm::mat4 projection;
	float fov;
	float aspect;
	float nearPlane;
	float farPlane;
	ProjectionType projectionType;

};

#endif // CAMERA_H

