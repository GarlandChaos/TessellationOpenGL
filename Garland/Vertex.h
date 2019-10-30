#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class Vertex {
private:
	glm::vec3 position;

public:

	Vertex();
	~Vertex();

	void setPosition(glm::vec3 position);
	glm::vec3 getPosition();
};