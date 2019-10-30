#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class Normal
{
private:

	glm::vec3 normals;

public:

	Normal();
	~Normal();
	
	void setNormals(glm::vec3 normals);
	glm::vec3 getNormals();
};