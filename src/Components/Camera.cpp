#include <Components/Camera.h>
#include <Core/Global.h>

Camera::Camera(
	const glm::vec3& position,
	const glm::vec3& target,
	const glm::vec3& up,
	ProjectionType type
) : position(position), target(target), up(up), projection(glm::mat4(1.0f)) {}

Camera& Camera::setPosition(const glm::vec3& newPosition) {
	position = newPosition;
	return *this;
}

Camera& Camera::setTarget(const glm::vec3& newTarget) {
	target = newTarget;
	return *this;
}

Camera& Camera::setUp(const glm::vec3& newUp) {
	up = newUp;
	return *this;
}

Camera& Camera::setFOV(float newFOV) {
	fov = newFOV;
	return *this;
}

Camera& Camera::setAspectRatio(float newAspect) {
	if (aspect == 0.0f) {
		auto size = Global::getWindow().getSize();
		aspect = static_cast<float>(size.y) / static_cast<float>(size.x);
	}

	aspect = newAspect;
	return *this;
}

Camera& Camera::setNearFar(float near, float far) {
	nearPlane = near;
	farPlane = far;
	return *this;
}

Camera& Camera::setProjection(ProjectionType type) {
	projectionType = type;
	return *this;
}

void Camera::updateProjectionMatrix() {
	if (projectionType == ProjectionType::Perspective) {
		projection = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
	} else {
		projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, nearPlane, farPlane);
	}
}

glm::mat4 Camera::getVP() const {
	return projection * view;
}

void Camera::updateViewMatrix() {
	view = glm::lookAt(position, target, up);
}

void Camera::update() {
	updateViewMatrix();
	updateProjectionMatrix();
}
