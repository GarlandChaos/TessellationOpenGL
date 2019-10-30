#pragma once
#include "Mesh.h"
#include "Material.h"

class Object3D {

private:
	Mesh *mesh;
	Material *material;
	glm::mat4 trans;

public:

	Object3D();
	~Object3D();

	void setMesh(Mesh *mesh);
	Mesh* getMesh();

	void setMaterial(Material *material);
	Material* getMaterial();

	void setTrans(glm::mat4 trans);
	glm::mat4 getTrans();
};