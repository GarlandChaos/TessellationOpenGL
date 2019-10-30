#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <string>
#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "stb_image.h"

using namespace std;

class Material {
private:
	string nameMaterial;
	glm::vec3 Ka;
	glm::vec3 Kd;
	glm::vec3 Ks;
	glm::vec3 Tf;
	float Ns; //shiness
	string nameTexture;
	unsigned int texture1;

public:

	Material();
	~Material();

	void loadTexture();
	void useTexture(GLuint shaderProg);

	void setNameMaterial(string nameMaterial);
	string getNameMaterial();

	void setKa(glm::vec3 Ka);
	glm::vec3 getKa();

	void setKd(glm::vec3 Kd);
	glm::vec3 getKd();

	void setKs(glm::vec3 Ks);
	glm::vec3 getKs();

	void setTf(glm::vec3 Tf);
	glm::vec3 getTf();

	void setNs(float Ns);
	float getNs();

	void setNameTexture(string nameTexture);
	string getNameTexture();
};