#ifndef CALLBACKS_HPP
#define CALLBACKS_HPP

#include <iostream>

#include <GLFW/glfw3.h>

namespace clbck {
	// GLFW sets glViewport when window resizes
	void framebufferSize(GLFWwindow * window, int width, int height);

	// GLFW error handling
	void error(int code, const char * description);
}

#endif /* CALLBACKS_HPP */

