#pragma once
#include <vector>

using namespace std;

class Face {
private:

	vector<int> vertices;
	vector<int> normals;
	vector<int> textures;

public:

	Face();
	~Face();

	void setVertices(vector<int> vertices);
	vector<int>& getVertices();

	void setNormals(vector<int> normals);
	vector<int>& getNormals();

	void setTextures(vector<int> textures);
	vector<int>& getTextures();


};