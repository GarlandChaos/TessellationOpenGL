#include "Texture.h"

Texture::Texture() {

}

Texture::~Texture() {

}

void Texture::setPosition(glm::vec2 position) {

	this->position = position;
}

glm::vec2 Texture::getPosition() {

	return position;
}

void Texture::setId(unsigned int id)
{
	this->id = id;
}

unsigned int Texture::getId()
{
	return id;
}

void Texture::setName(string name)
{
	this->name = name;
}

string Texture::getName()
{
	return name;
}