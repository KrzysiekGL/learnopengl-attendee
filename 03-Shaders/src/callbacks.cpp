#include "callbacks.hpp"

void clbck::framebufferSize(GLFWwindow * window, int width, int height) {
	glViewport(0, 0, width, height);
}

void clbck::error(int code, const char *description) {
	std::cerr << "ERROR: (clbck::error) GLFW error code " << code \
						<< "\nError message:\n" << description << '\n';
}

