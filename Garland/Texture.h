#pragma once
#include <stdlib.h>
#include <string>
#include <glm\glm.hpp>

using namespace std;

class Texture
{
private:

	unsigned int id;
	string type;
	glm::vec2 position;
	string name;

public:

	Texture();
	~Texture();
	
	void setPosition(glm::vec2 position);
	glm::vec2 getPosition();

	void setId(unsigned int id);
	unsigned int getId();

	void setName(string name);
	string getName();
};