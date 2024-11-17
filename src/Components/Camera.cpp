#include <Components/Camera.h>

Camera::Camera(
	const glm::vec3& position,
	const glm::vec3& target,
	const glm::vec3& up,
	ProjectionType type
) : position(position), target(target), up(up), projection(glm::mat4(1.0f)) {
	updateViewMatrix();
}

void Camera::setPosition(const glm::vec3& newPosition) {
	position = newPosition;
	updateViewMatrix();
}

void Camera::setTarget(const glm::vec3& newTarget) {
	target = newTarget;
	updateViewMatrix();
}

void Camera::setUp(const glm::vec3& newUp) {
	up = newUp;
	updateViewMatrix();
}

void Camera::setProjection(const glm::mat4& newProjection) {
	projection = newProjection;
}

glm::mat4 Camera::getVP() const {
	return projection * view;
}

void Camera::updateViewMatrix() {
	view = glm::lookAt(position, target, up);
}

void Camera::updateProjectionMatrix(ProjectionType type, std::shared_ptr <sf::RenderTarget> target) {

	if (type == ProjectionType::Perspective) {
		if (target == nullptr) {
			throw std::invalid_argument("Perspective projection selected but render target not provided.");
		}

		float fov = glm::radians(45.0f);
		float aspectRatio = 800.0f / 600.0f; // Example aspect ratio
		float nearPlane = 0.1f;
		float farPlane = 100.0f;

		projection = glm::perspective(fov, aspectRatio, nearPlane, farPlane);

	} else if (type == ProjectionType::Orthographic) {

		float left = -10.0f;
		float right = 10.0f;
		float bottom = -10.0f;
		float top = 10.0f;
		float nearPlane = -1.0f;
		float farPlane = 1.0f;

		projection = glm::ortho(left, right, bottom, top, nearPlane, farPlane);
	}
}
