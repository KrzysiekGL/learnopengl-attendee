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
	GLFWwindow * window = glfwCreateWindow(800, 600, "learnopengl", NULL, NULL);
	if(window == NULL) {
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Map to the OpenGL function pointers with GLAD
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}

	return 0;
}

