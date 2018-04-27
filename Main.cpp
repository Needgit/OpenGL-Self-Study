#include <stdio.h>

#include <GL/glew.h>
#include <GL/glfw3.h>

#define LEN(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))

static GLint width, height;

GLfloat vertices[4][3] = {
	{-0.5f, -0.5f, 0.0f},
	{ 0.5f, -0.5f, 0.0f},
	{ 0.0f,  0.5f, 0.0f},
	{ 0.0f,  0.5f, 0.5f}
};

GLfloat colors[4][3] = {
	{ 1, 0, 0},
	{ 0, 1, 0},
	{ 0, 0, 1},
	{ 1, 1, 1}
};

static GLfloat angle = 0;


void errorCallback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}


void display(void)
{
    GLuint i;

    glViewport(0, 0, width, height);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, width/(GLfloat)height, 0.1, 500.0);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();

    angle--;

    if (angle > 360)
    	angle -= 360;
    else
	if (angle < 0)
		angle += 360;
    glPointSize(4);

    glPushMatrix();
    	glLoadIdentity();
    	glTranslatef(0,0,-2.2);
		glRotatef(angle, 0, 1, 0);
		glBegin(GL_POINTS);
			for(i = 0; i < LEN(vertices); i++)
			{
				//glColor3fv(colors[i]);
				glVertex3fv(vertices[i]);
			}
		glEnd();
    glPopMatrix();

    glFlush();
}


int main(int argc, char** argv)
{
	GLFWwindow* window;

	glfwSetErrorCallback(errorCallback);

	// Initialize GLFW:
	if (glfwInit() == GLFW_FALSE)
		return 0;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	window = glfwCreateWindow(320, 240, "Window", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return 0;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // VSync?

	while(!glfwWindowShouldClose(window))
	{
        glfwGetFramebufferSize(window, &width, &height);

        display();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}
