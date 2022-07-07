/*
 * Study of OpenGL guided by https://learnopengl.com
 *
 * Author: KrzysiekGL webmaster@unexpectd.com
 * 06/2022
 */

#include <iostream>
#include <math.h>

// Include GLAD before GLFW
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "Shader.hpp"

#define WIDTH 800
#define HEIGHT 600

const float vertices[] = {
	.5,  .5, .0,		1.f, 0.f, 0.f,
	.5, -.5, .0,		0.f, 1.f, 0.f,
	-.5, -.5, .0,		0.f, 0.f, 1.f,
	-.5,  .5, .0,		1.f, 0.f, 1.f,
};

const GLuint indices[] = {
	0, 1, 3,
	1, 2, 3
};

void framebufferSizeCallback(GLFWwindow * window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow * window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main(int argc, char ** argv, char ** eval) {
	std::cout << "03-Shaders\n";

	// GLFW initializationf
	glfwInit();
	// OpenGL version and features
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Window features
	glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

	// GLFW window creation
	GLFWwindow * window = glfwCreateWindow(WIDTH, HEIGHT, "learnopengl", NULL, NULL);
	if(window == NULL) {
		std::cout << "ERROR: Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Map to the OpenGL function pointers with GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "ERROR: Failed to initialize OpenGL context (GLAD)\n";
		glfwTerminate();
		return -1;
	}

	// Maximum Vertex Attributes supported by the hardware (at least 16*vec4)
	{
		int numAttribs;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numAttribs);
		std::cout << "Maximum number of attributes supported: " << numAttribs << "\n";
	}

	// GLFW callbacks
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	// OpenGL state machine settings
	framebufferSizeCallback(window, WIDTH, HEIGHT);
	glClearColor(.2f, .3f, .3f, 1.f);

	// -----------------------------------------------------------------------------------------------
	// Temp space for rendering stuff
	// Vertex Array Object - a buffer to store data about VBO and it's corresponding Attributes.
	// It doesn't link or store connection to a shader program.
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Vertex Buffer Object - a rectangle made of 4 vertices
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Element Buffer Object - combination of the VBO vertices to form a rectangle
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Linking Vertex Attributes

	// Vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);

	// Colors
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));

	// Bind to default buffers (VAO (!*), VBO, EBO)
	// *VAO keeps track of the last bound EBO while the VAO is bound.
	// So if the default EBO was bound before default VAO, then the
	// VAO would keep track of the default EBO, which is 0
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// -----------------------------------------------------------------------------------------------

	// Shader program
	Shader basic("../shader/basic.vert", "../shader/basic.frag");

	// End of temp space for rendering stuff
	// -----------------------------------------------------------------------------------------------

	// Game loop/Render loop
	while(!glfwWindowShouldClose(window)) {
		// Input
		processInput(window);

		// Rendering

		//Clrear color buffer
		glClear(GL_COLOR_BUFFER_BIT);

		// Render rectangle
		basic.activate();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLuint), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		basic.deactivate();

		// Events & Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Clean-up
	glfwTerminate();
	return 0;
}

