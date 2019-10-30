#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <iostream>
#include <vector>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

using namespace std;

class Curve {

private:
	float x0;
	float y0;

	vector<float> X;
	vector<float> Y;
	vector<glm::vec3> points;
	vector<glm::vec3> curvePoints;

	GLuint vao;
	GLuint vbo1;

public:
	Curve();
	~Curve();

	void capturePoints(float x, float y);
	void fillCurve();
	void drawCurve(GLuint shaderProg);
	void setupCurve();
	void fillPoints();
	void drawPoints(GLuint shaderProg);
};