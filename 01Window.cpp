//#include <GL/glew.h>
//#include <GL/glfw3.h>
//
//static GLFWwindow* window;
//
//
//void framebufferSizeCallback(GLFWwindow* window, int width, int height)
//{
//    glViewport(0, 0, width, height);
//}
//
//
//void processInput(GLFWwindow *window)
//{
//    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//}
//
//
//int main(int argc, char** argv)
//{
//	if (glfwInit() == GLFW_FALSE)
//		return GLFW_FALSE;
//
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//
//	window = glfwCreateWindow(320, 240, "Window", NULL, NULL);
//	if (!window)
//	{
//		glfwTerminate();
//		return GLFW_FALSE;
//	}
//
//	glfwMakeContextCurrent(window);
//
//	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
//
//	while(!glfwWindowShouldClose(window))
//	{
//		// Get Inputs:
//		processInput(window);
//
//		// Rendering here:
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//
//		glfwPollEvents();
//		glfwSwapBuffers(window);
//	}
//
//	glfwDestroyWindow(window);
//	glfwTerminate();
//
//    return GLFW_TRUE;
//}
