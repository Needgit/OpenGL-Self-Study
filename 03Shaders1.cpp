//#include <GL/glew.h>
//#include <GL/glfw3.h>
//
//#include <iostream>
//#include <math.h>
//
//static GLFWwindow* window;
//
//static GLuint shader_program;
//static GLuint VAO;
//static GLuint VBO;
//
//static GLfloat vertices[] = {
////  Vertex:					Color:
//    -0.5f, -0.5f, 0.0f, 	 1.0f,  0.0f,  0.0f,
//     0.5f, -0.5f, 0.0f,		 0.0f,  1.0f,  0.0f,
//     0.0f,  0.5f, 0.0f,		 0.0f,  0.0f,  1.0f,
//};
//
//
//GLuint compileShaders()
//{
//	GLuint vertex_shader, fragment_shader, program;
//
//	GLint  success;
//	GLchar infoLog[512];
//
//	static const GLchar* vertex_shader_source[] =
//	{
//		"#version 330 core										\n"
//		"layout (location = 0) in vec3 aPos;					\n"
//		"layout (location = 1) in vec3 aColor;					\n"
//		" 														\n"
//		"out vec3 vColor;										\n"
//		" 														\n"
//		"void main(void)										\n"
//		"{														\n"
//		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);	\n"
//		" 	vColor      = aColor;								\n"
//		"}														\n"
//	};
//
//	static const GLchar* fragment_shader_source[] =
//	{
//		"#version 330 core										\n"
//		" 														\n"
//		"in  vec3 vColor;										\n"
//		"out vec4 fColor;										\n"
//		" 														\n"
//		"void main(void)										\n"
//		"{														\n"
//		"	fColor = vec4(vColor, 1.0f);						\n"
//		"}														\n"
//	};
//
//
////	std::cout << glGetString(GL_VERSION) << "\n" << glGetString(GL_SHADING_LANGUAGE_VERSION) << infoLog << std::endl;
//
//	// Create and compile vertex shader:
//	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
//	glCompileShader(vertex_shader);
//
//	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
//	if(!success)
//	{
//	    glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
//	    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//
//	// Create and compile fragment shader:
//	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
//	glCompileShader(fragment_shader);
//
//	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
//	if(!success)
//	{
//	    glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
//	    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//
//	// Create program and linking:
//	program = glCreateProgram();
//	glAttachShader(program, vertex_shader);
//	glAttachShader(program, fragment_shader);
//	glLinkProgram(program);
//
//	// Clean up:
//	glDeleteShader(vertex_shader);
//	glDeleteShader(fragment_shader);
//
//	return program;
//}
//
//
//void onStart()
//{
//	shader_program = compileShaders();
//
//	glGenBuffers(1, &VBO);
//	glGenVertexArrays(1, &VAO);
//
//	// We want to use the VAO:
//	glBindVertexArray(VAO);
//
//	// Bind VBO and copy verticies data into buffer:
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	// Set vertex attribute (layout (location = 0) in vec3 aPos):
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	// Set vertex attribute (layout (location = 1) in vec3 aColor):
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//}
//
//void onShutdown()
//{
//	glDeleteProgram(shader_program);
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//}
//
//void display()
//{
//	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glUseProgram(shader_program);
//	glBindVertexArray(VAO);
//
//	glDrawArrays(GL_TRIANGLES, 0, 3);
//}
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
//	window = glfwCreateWindow(320, 240, "Shaders1", NULL, NULL);
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
//	glewExperimental = GL_TRUE; // Fixes a weird crash due to old GLEW version;
//	if(glewInit() != GLEW_OK)	// Version 1.13.0: glewGetString(GLEW_VERSION);
//		throw std::runtime_error("glewInit failed");
//
//	onStart();
//
//	while(!glfwWindowShouldClose(window))
//	{
//		// Get Inputs:
//		processInput(window);
//
//		// Rendering here:
//		display();
//
//		glfwPollEvents();
//		glfwSwapBuffers(window);
//	}
//
//	onShutdown();
//
//	glfwDestroyWindow(window);
//	glfwTerminate();
//
//    return GLFW_TRUE;
//}
