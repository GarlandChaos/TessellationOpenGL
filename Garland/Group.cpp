#include "Group.h"

Group::Group() {

}

Group::~Group() {

}

void Group::setFaces(vector<Face> faces) {

	this->faces = faces;
}

vector<Face>& Group::getFaces() {

	return faces;
}

void Group::setName(string name) {

	this->name = name;
}

string Group::getName() {

	return name;
}

void Group::setMaterialID(string materialID) {

	this->materialID = materialID;
}

string Group::getMaterialID() {

	return materialID;
}
