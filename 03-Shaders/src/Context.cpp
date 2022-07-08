#include "Context.hpp"

Context::Context(std::string windowName, int width, int height) {
	this->width = width;
	this->height = height;

	// GLFW initializationf
	glfwInit();

	// OpenGL version and features
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Window features
	glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

	// GLFW window creation
	window = glfwCreateWindow(width, height, "learnopengl", NULL, NULL);
	if(window == NULL) {
		std::cout << "ERROR: Failed to create GLFW window\n";
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	// Map to the OpenGL function pointers with GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "ERROR: Failed to initialize OpenGL context (GLAD)\n";
		glfwTerminate();
		return;
	}

	// Maximum Vertex Attributes supported by the hardware (at least 16*vec4)
	int numAttribs;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numAttribs);
	std::cout << "Maximum number of attributes supported: " << numAttribs << "\n";

	// GLFW callbacks
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	// OpenGL state machine settings
	framebufferSizeCallback(window, width, height);
	glClearColor(.2f, .3f, .3f, 1.f);
}

bool Context::shouldClose() const {
	return glfwWindowShouldClose(window);
}

void Context::processInput() const {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void Context::updateContextState() {
	glfwGetWindowSize(window, &width, &height);
}

void Context::swapBuffers() const {
	glfwSwapBuffers(window);
}

void Context::pollEvents() {
	glfwPollEvents();
}

void Context::framebufferSizeCallback(GLFWwindow * window, int width, int height) {
	glViewport(0, 0, width, height);
}

