#include <GL/glew.h>
#include <GL/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <iostream>
#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLshader.h"


static GLFWwindow* window;

static GLshader shader;

static GLuint VAO;
static GLuint VBO;

static GLuint texture1, texture2;

static GLfloat vertices[] = {
//  Vertex:					Color:				   Tex Coord:
    -0.5f, -0.5f, 0.0f, 	 1.0f,  0.0f,  0.0f,	0.1f,  0.1f,
     0.5f, -0.5f, 0.0f,		 0.0f,  1.0f,  0.0f,	0.9f,  0.1f,
     0.0f,  0.5f, 0.0f,		 0.0f,  0.0f,  1.0f,	0.51f, 0.925f,
};


void loadImage(const GLchar* path, GLuint &TBO)
{
	// Flip y-axis so positive is upwards:
	stbi_set_flip_vertically_on_load(true);

	// Load Image Data using STB Library:
	int width, height, nrChannels;
	unsigned char *image = stbi_load(path, &width, &height, &nrChannels, 0);
	if (image)
	{
		// Create OpenGL Texture Obejct:
		glGenTextures(1, &TBO);
		glBindTexture(GL_TEXTURE_2D, TBO);

		// Load Image Data into Object:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D); // Generate a Mipmap of texture;
	}
	else
	{
		 std::cout << "Failed to load texture..." << std::endl;
	}

	// Cleanup Image Data:
	stbi_image_free(image);
}


void onStart()
{
	glEnable(GL_DEPTH_TEST);

	shader = GLshader("Shaders/05Transform.vs", "Shaders/05Transform.fs");

	// Texture Repeat:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Use Nearest Neighbor Filtering (pixelated):
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	loadImage("Textures/Container.jpg",  texture1);
	loadImage("Textures/Illuminati.jpg", texture2);

	shader.use();
	shader.setInt("uTexture1", 0);
	shader.setInt("uTexture2", 1); // or with shader class

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	// We want to use the VAO:
	glBindVertexArray(VAO);

	// Bind VBO and copy verticies data into buffer:
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Set vertex attribute (layout (location = 0) in vec3 aPos):
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	// Set vertex attribute (layout (location = 1) in vec3 aColor):
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Set vertex attribute (layout (location = 1) in vec3 aTexCoord):
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
}

void onShutdown()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void display()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.use();

	// Move Camera:
	glm::mat4 view;
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));
	view = glm::rotate(view, (float)glfwGetTime() * glm::radians(25.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int uView = glGetUniformLocation(shader.ID, "view");
	glUniformMatrix4fv(uView, 1, GL_FALSE, glm::value_ptr(view));

    // Do Perspective:
	static GLint width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glm::mat4 projection = glm::perspective<GLfloat>(glm::radians(45.0f), width / (GLfloat)height, 0.1f, 100.0f);
	unsigned int transformLoc = glGetUniformLocation(shader.ID, "projection");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// Draw objects:

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glBindVertexArray(VAO);

	// Draw 3 triangles and position them accordingly to index:
	for (GLint i = 0; i < 3; i++)
	{
		glm::mat4 world;
		world = glm::rotate(world, glm::radians(i * 120.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		world = glm::translate(world, glm::vec3(0.0f, 0.0f, 0.145f));
		world = glm::rotate(world, glm::radians(-16.75f), glm::vec3(1.0f, 0.0f, 0.0f));

		unsigned int uWorld = glGetUniformLocation(shader.ID, "world");
		glUniformMatrix4fv(uWorld, 1, GL_FALSE, glm::value_ptr(world));

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}


void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


int main(int argc, char** argv)
{
	if (glfwInit() == GLFW_FALSE)
		return GLFW_FALSE;

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	window = glfwCreateWindow(320, 240, "Texture", NULL, NULL);
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
