/*
 * Study of OpenGL guided by https://learnopengl.com
 *
 * Author: KrzysiekGL webmaster@unexpectd.com
 * 06/2022
 */

#include <iostream>

/*
 * Be sure to include GLAD before GLFW. The include file
 * for GLAD includes the required OpenGL headers behind
 * the scenes (like GL/gl.h) so be sure to include GLAD
 * before other header files that require OpenGL (like GLFW).
 */
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#define WIDTH 800
#define HEIGHT 600

void framebufferSizeCallback(GLFWwindow * window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow * window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main(int argc, char ** argv, char ** eval) {
	std::cout << "01-Creating_a_window\n";

	// GLFW initialization
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
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Map to the OpenGL function pointers with GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize OpenGL context (GLAD)\n";
		return -1;
	}

	// GLFW callbacks
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	// OpenGL state machine settings
	glViewport(0, 0, WIDTH, HEIGHT);
	glClearColor(.2f, .3f, .3f, 1.f);

	// Game loop/Render loop
	while(!glfwWindowShouldClose(window)) {
		// Input
		processInput(window);

		// Rendering
		glClear(GL_COLOR_BUFFER_BIT);

		// Events & Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Clean-up
	glfwTerminate();
	return 0;
}

