#include "Mesh.h"
#include <iostream>

Mesh::Mesh() 
{

}

Mesh::~Mesh() 
{

}

void Mesh::increaseVerticesCount()
{
	verticesCount++;
}

vector<glm::vec3> Mesh::getVertices(Group group)
{
	vector<glm::vec3> verts;
	for (int i = 0; i < group.getFaces().size(); i++) 
	{
		for (int j = 0; j < group.getFaces()[i].getVertices().size(); j++) 
		{
			verts.push_back(vertices[group.getFaces()[i].getVertices()[j]]);
		}
	}

	return verts;
}

vector<glm::vec3> Mesh::getNormals(Group group)
{
	vector<glm::vec3> norms;
	for (int i = 0; i < group.getFaces().size(); i++) {
		for (int j = 0; j < group.getFaces()[i].getNormals().size(); j++) {
			norms.push_back(normals[group.getFaces()[i].getNormals()[j]].getNormals());
		}
	}
	
	return norms;
}

vector<glm::vec2> Mesh::getTextureCoords(Group group)
{
	vector<glm::vec2> textCoords;
	for (int i = 0; i < group.getFaces().size(); i++)
	{
		for (int j = 0; j < group.getFaces()[i].getTextures().size(); j++)
		{
			textCoords.push_back(textures[group.getFaces()[i].getTextures()[j]].getPosition());
		}
	}

	return textCoords;
}

void Mesh::setupMesh() {

	for (int i = 0; i < groups.size(); i++) {

		vector<glm::vec3> verts = getVertices(groups[i]);
		vector<glm::vec3> norms = getNormals(groups[i]);
		GLuint vao, vbo1, vbo2, vbo3;

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo1);

		glBindVertexArray(vao);

		vaos.push_back(vao);

		//VBO 1: vertex
		glBindBuffer(GL_ARRAY_BUFFER, vbo1);
		glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(glm::vec3), &verts[0], GL_STATIC_DRAW);

		// vertex positions
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);

		//VBO 2: normal
		glGenBuffers(1, &vbo2);
		glBindBuffer(GL_ARRAY_BUFFER, vbo2);
		glBufferData(GL_ARRAY_BUFFER, norms.size() * sizeof(glm::vec3), &norms[0], GL_STATIC_DRAW);

		// vertex normals
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(1);

		if (textures.size() > 0) 
		{
			vector<glm::vec2> textCoords = getTextureCoords(groups[i]);

			//VBO 3: texture coord
			glGenBuffers(1, &vbo3);
			glBindBuffer(GL_ARRAY_BUFFER, vbo3);
			glBufferData(GL_ARRAY_BUFFER, textCoords.size() * sizeof(glm::vec2), &textCoords[0], GL_STATIC_DRAW);

			// vertex texture coords
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
			glEnableVertexAttribArray(2);
		}
		

		glBindVertexArray(0);

	}
}

void Mesh::Draw() {
	
	for (int i = 0; i < vaos.size(); i++) {

		glBindVertexArray(vaos[i]);
		glDrawArrays(GL_TRIANGLES, 0, verticesCount);
		//glDrawElements(GL_TRIANGLES, verticesCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

}

void Mesh::DrawPatches() {

	for (int i = 0; i < vaos.size(); i++) {

		glBindVertexArray(vaos[i]);
		glDrawArrays(GL_PATCHES, 0, verticesCount);
		glBindVertexArray(0);
	}
}


void Mesh::setGroups(vector<Group> groups) {

	this->groups = groups;
}

vector<Group>& Mesh::getGroups() {

	return groups;
}

void Mesh::setVertices(vector<glm::vec3> vertices) {

	this->vertices = vertices;
}

vector<glm::vec3>& Mesh::getVertices() {

	return vertices;
}

void Mesh::setTextures(vector<Texture> textures){

	this->textures = textures;
}

vector<Texture>& Mesh::getTextures() {

	return textures;
}

void Mesh::setNormals(vector<Normal> normals) {

	this->normals = normals;
}

vector<Normal>& Mesh::getNormals() {

	return normals;
}

void Mesh::setMaterialLib(string materialLib) 
{
	this->materialLib = materialLib;
}

string Mesh::getMaterialLib() 
{
	return materialLib;
}