/*
 * Camera class in a resource for generating the view matrix to imitate a camera object
 * in OpenGL.
 *
 * 2022
 * Author: KrzysiekGL webmaster@unexpectd.com; All rights reserved.
 */

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <iostream>

#include <glm/glm.hpp>

#include "Resource.hpp"

class Camera: public Resource {
public:
	Camera(glm::vec3 initialPosition = glm::vec3(0, 0, 0.f),
				 glm::vec3 initialTarget = glm::vec3(0, 0, 0));

	// Get the Look At matrix for the view matrix transformation
	glm::mat4 getLookAt();

	// Getters
	glm::vec3 getPosition() const { return position; }
	glm::vec3 getTarget() const { return target; }
	glm::vec3 getReverseDirection() const { return reverseDirection; }
	glm::vec3 getRight() const { return right; }
	float getSpeed() const { return speed; }

private:
	static const glm::vec3 worldUp;
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 reverseDirection;
	glm::vec3 right;
	glm::vec3 up;
	float speed;

	// Setters
	void setPosition(glm::vec3 position) { this->position = position; }
	void setTarget(glm::vec3 target) { this->target = target; }
	void setSpeed(float speed) { this->speed = speed; }

	// Calculate coordinate system of this camera for the view matrix
	// Gram-Schmidt linear algebra method
	void coordinatesCalculation();

	// Friendship declaration with the Context class
	// so that a context object can process input for a camera object
	friend class Context;

	// Print information aobut this camera
	virtual void print(std::ostream & os) const override;
};

#endif /* CAMERA_HPP */

