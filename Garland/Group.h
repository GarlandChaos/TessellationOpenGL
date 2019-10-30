#pragma once
#include "Face.h"

class Group {
private:
	vector<Face> faces;
	string name;
	string materialID;

public:

	Group();
	~Group();

	void setFaces(vector<Face>);
	vector<Face>& getFaces();

	void setName(string name);
	string getName();

	void setMaterialID(string materialID);
	string getMaterialID();
};