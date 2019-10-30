#include "Face.h"

Face::Face() {

}

Face::~Face() {

}

void Face::setVertices(vector<int> vertices) {

	this->vertices = vertices;
}

vector<int>& Face::getVertices() {

	return vertices;
}

void Face::setTextures(vector<int> textures) {

	this->textures = textures;
}

vector<int>& Face::getTextures() {

	return textures;
}

void Face::setNormals(vector<int> normals) {

	this->normals = normals;
}

vector<int>& Face::getNormals() {

	return normals;
}