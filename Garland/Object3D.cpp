#include "Object3D.h"

Object3D::Object3D() {

}

Object3D::~Object3D() {

}

void Object3D::setMesh(Mesh *mesh) {

	this->mesh = mesh;
}

Mesh* Object3D::getMesh() {

	return mesh;
}

void Object3D::setMaterial(Material *material) {

	this->material = material;
}

Material* Object3D::getMaterial() {

	return material;
}

void Object3D::setTrans(glm::mat4 trans) {

	this->trans = trans;
}

glm::mat4 Object3D::getTrans() {

	return trans;
}