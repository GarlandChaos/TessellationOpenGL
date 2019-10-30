#include "Material.h"

Material::Material() {

}

Material::~Material() {
	
}

void Material::loadTexture() {
	//TEXTURE
	// texture 1
	// ---------
	glEnable(GL_TEXTURE_2D);
	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

	glGenTextures(1, &texture1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);

	const char * nameT = nameTexture.c_str();

	unsigned char *data = stbi_load(nameT, &width, &height, &nrChannels, 0);
	if (data)
	{

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
	//END TEXTURE
}

void Material::useTexture(GLuint shaderProg) {
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(shaderProg, "texture1"), 0);
}

void Material::setNameMaterial(string nameMaterial) {

	this->nameMaterial = nameMaterial;
}

string Material::getNameMaterial(){

	return nameMaterial;
}

void Material::setKa(glm::vec3 Ka) {

	this->Ka = Ka;
}

glm::vec3 Material::getKa() {

	return Ka;
}

void Material::setKd(glm::vec3 Kd) {

	this->Kd = Kd;
}

glm::vec3 Material::getKd() {

	return Kd;
}

void Material::setKs(glm::vec3 Ks) {

	this->Ks = Ks;
}

glm::vec3 Material::getKs() {

	return Ks;
}

void Material::setTf(glm::vec3 Tf) {

	this->Tf = Tf;
}

glm::vec3 Material::getTf() {

	return Tf;
}

void Material::setNs(float Ns) {

	this->Ns = Ns;
}

float Material::getNs() {

	return Ns;
}

void Material::setNameTexture(string nameTexture) {

	this->nameTexture = nameTexture;
}

string Material::getNameTexture() {

	return nameTexture;
}