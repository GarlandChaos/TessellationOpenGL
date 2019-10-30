#include "Vertex.h"

Vertex::Vertex() {

}

Vertex::~Vertex() {

}

void Vertex::setPosition(glm::vec3 position) {

	this->position= position;
}

glm::vec3 Vertex::getPosition() {

	return position;
}