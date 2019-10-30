#pragma once
#include "Mesh.h"
#include "Material.h"

using namespace std;


class ObjReader
{
private:
	//string materialLib;

public:

	ObjReader();
	~ObjReader();
	Mesh* ReadOBJ(string file);
	Material* ReadMTL(string materialLib);
	vector<glm::vec3> ReadCurve(string file);
};