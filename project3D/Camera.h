#pragma once

#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Camera
{
public:

	glm::vec3 getPos();

	Camera() : theta(0), phi(-20), position(-10, 4, 0)
	{

	}

	glm::mat4 GetProjectionMatrix(float w, float h);

	glm::mat4 GetViewMatrix();

	void Update();
	
private:
	int lastMouseX;
	int lastMouseY;
	float theta;
	float phi;
	const float deg2Rad = 3.14159f / 180.0f;
	glm::vec3 position;
};

