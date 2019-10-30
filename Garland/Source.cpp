#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Mesh.h"
#include "ObjReader.h"
#include "Curve.h"
#include "Object3D.h"
#include "Shader.h"

#define PI 3.14159265

using namespace std;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float fov = 45.0f;

int screenWidth = 800;
int screenHeight = 600;

bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = (float)screenWidth / 2.0;
float lastY = (float)screenHeight / 2.0;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float heightLevel = 0.1f; //displacement deformation level

void processInput(GLFWwindow *window) {

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	float cameraSpeed = 0.9 * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPos += cameraSpeed * cameraFront;
	}
		
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos -= cameraSpeed * cameraFront;
	}
		
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
		
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}

	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		heightLevel -= 0.01f;
	}

	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		heightLevel += 0.01f;
	}
		
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.5f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}

int main() {

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Bernardo/Garland's 3D World", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		system("pause");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glewExperimental = GL_TRUE;
	glewInit();

	printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));
	int max_patch_vertices = 0;
	glGetIntegerv(GL_MAX_PATCH_VERTICES, &max_patch_vertices);
	cout << "Quantidade máxima de vértices por patch: " << max_patch_vertices << endl;
	
	glViewport(0, 0, screenWidth, screenHeight);

	ObjReader objR;

	Shader shaderSimple("vertexShaderSimple.vs", "fragmentShaderSimple.fs");
	Shader shaderTess("vertexShaderTess.vs", "tesselatorControlTess.tc", "tesselatorEvaluationTess.te", "fragmentShaderTess.fs");
	
	Mesh *mesh1;
	mesh1 = new Mesh();
	mesh1 = objR.ReadOBJ("astronaut2.obj");
	mesh1->setupMesh();

	Object3D obj1;
	obj1.setMesh(mesh1);

	Material *material1;
	material1 = new Material();
	material1 = objR.ReadMTL(obj1.getMesh()->getMaterialLib());
	obj1.setMaterial(material1);

	Mesh *mesh2;
	mesh2 = new Mesh();
	mesh2 = objR.ReadOBJ("sphere_blender_textured.obj");
	mesh2->setupMesh();

	Object3D obj2;
	obj2.setMesh(mesh2);

	Material *material2;
	material2 = new Material();
	material2 = objR.ReadMTL(obj2.getMesh()->getMaterialLib());
	obj2.setMaterial(material2);

	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, -0.99f));
	trans = glm::scale(trans, glm::vec3(0.1f, 0.1f, 0.1f));
	obj1.setTrans(trans);

	glm::mat4 trans2;
	obj2.setTrans(trans2);

	glm::vec3 lightPos(0.0f, 0.0f, -0.2f);
	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
	glm::vec3 viewPos(0.0f, 0.0f, 0.0f);

	shaderSimple.use();
	string texture1Simple = obj1.getMaterial()->getNameTexture();
	shaderSimple.generateTexture(texture1Simple);
	unsigned int texture1SimpleID;
	shaderSimple.getTextureID(texture1Simple, texture1SimpleID);
	shaderSimple.setInt("textureSimple", 0);

	shaderTess.use();
	string texture1 = obj2.getMaterial()->getNameTexture();
	shaderTess.generateTexture(texture1);
	unsigned int texture1ID;
	shaderTess.getTextureID(texture1, texture1ID);
	shaderTess.setInt("texture1", 0);

	string displacement = "displacement.jpg";
	shaderTess.generateTexture(displacement);
	unsigned int terrainID;
	shaderTess.getTextureID(displacement, terrainID);
	shaderTess.setInt("terrain", 1);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	glPatchParameteri(GL_PATCH_VERTICES, 3);

	while (!glfwWindowShouldClose(window)) {

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(fov), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);

		glm::mat4 view;
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		shaderSimple.use();
		shaderSimple.activateTextures();
		shaderSimple.setMatrix("transform", obj1.getTrans());
		shaderSimple.setMatrix("view", view);
		shaderSimple.setMatrix("projection", projection);
		shaderSimple.setVec3("lightPos", lightPos);
		shaderSimple.setVec3("lightColor", lightColor);
		shaderSimple.setVec3("viewPos", viewPos);
		shaderSimple.setVec3("Ka", obj1.getMaterial()->getKa());
		shaderSimple.setVec3("Kd", obj1.getMaterial()->getKd());
		shaderSimple.setVec3("Ks", obj1.getMaterial()->getKs());
		shaderSimple.setFloat("Ns", obj1.getMaterial()->getNs());
		obj1.getMesh()->Draw();

		shaderTess.use();
		shaderTess.activateTextures();
		shaderTess.setMatrix("transform", obj2.getTrans());
		shaderTess.setMatrix("view", view);
		shaderTess.setMatrix("projection", projection);
		shaderTess.setFloat("tess_fac_outer", 4.0);
		shaderTess.setFloat("tess_fac_inner", 1.0);
		shaderTess.setFloat("heightLevel", heightLevel);
		obj2.getMesh()->DrawPatches(); 

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteProgram(shaderSimple.getId());
	glDeleteProgram(shaderTess.getId());
	glfwTerminate();

	return 0;
}