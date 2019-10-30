#include "Curve.h"

Curve::Curve() {

}

Curve::~Curve() {

}

void Curve::capturePoints(float x, float y) {

	X.push_back(x);
	Y.push_back(y);

	cout << "X: " << X.back() << endl;
	cout << "Y: " << Y.back() << endl;

}

void Curve::fillCurve() {

	float inc = 0.1f;
	for (int i = 0; i < X.size()-3; i++) {
		for (float t = 0; t <= 1; t += inc) {
			float x = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1)*X[i] +
				(3 * pow(t, 3) - 6 * pow(t, 2) + 0 * t + 4)*X[i + 1] +
				(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1)*X[i + 2] +
				(1 * pow(t, 3) + 0 * pow(t, 2) + 0 * t + 0)*X[i + 3]) / 6);
			float y = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1)*Y[i] +
				(3 * pow(t, 3) - 6 * pow(t, 2) + 0 * t + 4)*Y[i + 1] +
				(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1)*Y[i + 2] +
				(1 * pow(t, 3) + 0 * pow(t, 2) + 0 * t + 0)*Y[i + 3]) / 6);

			glm::vec3 newPoint;
			newPoint.x = x;
			newPoint.y = y;
			newPoint.z = 0.0f;
			//cout << x << endl;
			curvePoints.push_back(newPoint);



			x0 = x; y0 = y;
		}
	}
}

void Curve::fillPoints() {
	for (int i = 0; i < X.size(); i++) {
		points.push_back(glm::vec3(X[i], Y[i], 0.0f));
	}
	/*points.push_back(glm::vec3(-0.5f, -0.5f, 0.0f));
	points.push_back(glm::vec3(0.5f, -0.5f, 0.0f));
	points.push_back(glm::vec3(0.0f, 0.5f, 0.0f));*/
	/*points.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
	points.push_back(glm::vec3(100.0f, 1.0f, 0.0f));
	points.push_back(glm::vec3(0.0f, 100.0f, 0.0f));*/
	/*points.push_back(glm::vec3(200.0f, 300.0f, 0.0f));
	points.push_back(glm::vec3(600.0f, 300.0f, 0.0f));
	points.push_back(glm::vec3(350.0f, 500.0f, 0.0f));*/


}

void Curve::setupCurve() {
		//cout << "Points size: " << points.size() << endl;

		//glGenVertexArrays(1, &vao);
		//glGenBuffers(1, &vbo1);

		//glBindVertexArray(vao);

		//glBindBuffer(GL_ARRAY_BUFFER, vbo1);
		//glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), &points[0], GL_STATIC_DRAW);

		//// vertex positions
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		//glEnableVertexAttribArray(0);

		//glBindVertexArray(0);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo1);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo1);
	glBufferData(GL_ARRAY_BUFFER, curvePoints.size() * sizeof(glm::vec3), &curvePoints[0], GL_STATIC_DRAW);

	// vertex positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

}

void Curve::drawPoints(GLuint shaderProg) {

		glBindVertexArray(vao);
		glDrawArrays(GL_LINE_STRIP, 0, points.size());
		//cout << "verts size: " << verts.size() << endl;
		glBindVertexArray(0);

}

void Curve::drawCurve(GLuint shaderProg) {
	glBindVertexArray(vao);
	glDrawArrays(GL_LINE_STRIP, 0, curvePoints.size());
	//cout << "verts size: " << verts.size() << endl;
	glBindVertexArray(0);
}