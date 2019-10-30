#include "Normal.h"

Normal::Normal() {

}

Normal::~Normal() {

}

void Normal::setNormals(glm::vec3 normals) {

	this->normals = normals;
}

glm::vec3 Normal::getNormals() {

	return normals;
}