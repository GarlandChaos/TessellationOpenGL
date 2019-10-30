#pragma once
#include "Group.h"
#include "Vertex.h"
#include "Texture.h"
#include "Normal.h"
#include <stdlib.h>
#include <vector>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "stb_image.h"
#include <string>

using namespace std;

class Mesh {

private:

	string name;
	vector<Group> groups;
	vector<glm::vec3> vertices;
	vector<Texture> textures;
	vector<Normal> normals;
	vector<GLuint> vaos;
	string materialLib;

	unsigned int verticesCount;


public:

	Mesh();
	~Mesh();

	void setupMesh();
	void Draw();
	void DrawPatches();

	void setGroups(vector<Group>);
	vector<Group>& getGroups();

	void setVertices(vector<glm::vec3> vertices);
	vector<glm::vec3>& getVertices();

	void setTextures(vector<Texture>);
	vector<Texture>& getTextures();

	void setNormals(vector<Normal>);
	vector<Normal>& getNormals();

	vector<glm::vec3> getVertices(Group group);
	vector<glm::vec3> getNormals(Group group);
	vector<glm::vec2> getTextureCoords(Group group);
	void setMaterialLib(string materialLib);
	string getMaterialLib();

	void increaseVerticesCount();

};