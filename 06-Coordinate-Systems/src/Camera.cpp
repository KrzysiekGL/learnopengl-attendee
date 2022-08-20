#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

const glm::vec3 Camera::worldUp = glm::vec3(0.f, 1.f, 0.f);

Camera::Camera(glm::vec3 initialPosition,
							 glm::vec3 initialTarget) :
	position(initialPosition),
	target(initialTarget)
{
	// Resource type
	type = Resource::Type::Camera;

	coordinatesCalculation();
}

glm::mat4 Camera::getLookAt() {
	return glm::lookAt(position, target, up);
}

void Camera::coordinatesCalculation() {
	// Camera direction (reverse direction)
	reverseDirection = glm::normalize(position - target);

	// Camera right
	right = glm::normalize(glm::cross(worldUp, reverseDirection));

	// Camera up
	up = glm::cross(reverseDirection, right);
}

void Camera::print(std::ostream & os ) const {
	os << "[type:Camera"
		 << "|resID:" << resID
		 << "|name:" << friendlyName
		 << "|camera_pos:"
		 << position.x << ","
		 << position.y << ","
		 << position.z
		 << "]";
}

