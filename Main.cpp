#include <GL/glew.h>
#include <GL/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLcamera.h"
#include "GLshader.h"
#include "GLmodel.h"


static GLFWwindow* window;
const  GLint windowWidth  = 320;
const  GLint windowHeight = 240;


static GLshader shader;
static GLcamera camera;

static GLmodel  model;
static GLmodel  light;

static GLfloat   rotation = 0;
static glm::vec3 lightPos;


void onStart()
{
	glEnable(GL_DEPTH_TEST);

	shader = GLshader("Shaders/Vertex.vs", "Shaders/Fragment.fs");
	camera = GLcamera(shader, glm::vec3(0, -5, -30), glm::vec3(0, 0, 0));
	camera.setWindowSize(windowWidth, windowHeight);

	model  = GLmodel("Models/Frog.fbx");
	light  = GLmodel("Models/01.fbx");
}


void onShutdown()
{

}


void display()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.use();
	shader.setAmbience(glm::vec3(0.5f, 0.5f, 0.5f));

	glm::mat4 world;
	world = glm::translate(world, lightPos);
	shader.setMat4("world", world);

	shader.setVec3("lightPos",    lightPos);
	shader.setVec3("lightColor",  glm::vec3(1.0f, 1.0f, 1.0f));
	light.Draw(shader); // Draw light source...


	camera.setRotation(glm::vec3(20,  rotation/*(float)glfwGetTime() * 50*/, 0));
	camera.update();

	world = glm::mat4();
	world = glm::rotate(world, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	shader.setMat4("world", world);

	// Draw objects:
	model.Draw(shader);
}


void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	camera.setWindowSize(width, height);
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    	rotation = rotation - 1;

    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    	rotation = rotation + 1;

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    	lightPos.y++;

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    	lightPos.y--;

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    	lightPos.z--;

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    	lightPos.z++;

    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    	lightPos = glm::vec3();
}


int main(int argc, char** argv)
{
	if (glfwInit() == GLFW_FALSE)
		return GLFW_FALSE;

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);



	window = glfwCreateWindow(windowWidth, windowHeight, "Texture", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return GLFW_FALSE;
	}

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	glewExperimental = GL_TRUE; // Fixes a weird crash due to old GLEW version;
	if(glewInit() != GLEW_OK)	// Version 1.13.0: glewGetString(GLEW_VERSION);
		throw std::runtime_error("glewInit failed");

	glfwSwapInterval(1);

	onStart();

	while(!glfwWindowShouldClose(window))
	{
		// Get Inputs:
		processInput(window);

		// Rendering here:
		display();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	onShutdown();

	glfwDestroyWindow(window);
	glfwTerminate();

    return GLFW_TRUE;
}
