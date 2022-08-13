#include "Context.hpp"

Context::Context(std::string windowName, int width, int height) {
	// Resource type
	//type = Resource::Type::

	this->width = width;
	this->height = height;

	// OpenGL version and features
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Window features
	glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

	// GLFW window creation
	window = glfwCreateWindow(width, height, "learnopengl", NULL, NULL);
	if(window == NULL) {
		std::cerr << "ERROR: (Context::Context) Failed to create GLFW window\n";
		return;
	}

	// GLFW callbacks for this context
	glfwSetFramebufferSizeCallback(window, clbck::framebufferSize);

	// Set default background color for GL_COLOR_BUFFER_BIT
	backgroundColor[0] = .2f;
	backgroundColor[1] = .3f;
	backgroundColor[2] = .3f;
	backgroundColor[3] = 1.f;
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

void Context::makeCurrent() {
	// Set current GLFW context
	glfwMakeContextCurrent(window);

	// With the context set, map OpenGL functions
	mapOpenGL();

	// OpenGL settings
	pushViewport();
	pushBackgroundColor();
}

bool Context::isOpenGLMapped() const {
	return openglMapped;
}

void Context::mapOpenGL() {
	if(window != glfwGetCurrentContext()) {
		std::cerr << "ERROR: (Context::mapOpenGL) GLFW context is not set to this context\n";
		return;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
	 	std::cerr << "ERROR: (Context::mapOpenGL) Failed to initialize OpenGL context (GLAD)\n";
	 	return;
	}

	openglMapped = true;
}

int Context::getNumAttributes() const {
	// Maximum Vertex Attributes supported by the hardware (at least 16*vec4)
	if(!openglMapped) {
		std::cerr << "ERROR: (Context::getNumAttributes) OpenGL not mapped\n";
		return -1;
	}

	int numAttribs;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numAttribs);
	return numAttribs;
}

void Context::pushViewport() const {
	clbck::framebufferSize(window, width, height);
}

void Context::pushBackgroundColor() const {
	float r, g, b, a;
	r = backgroundColor[0];
	g = backgroundColor[1];
	b = backgroundColor[2];
	a = backgroundColor[3];
	glClearColor(r, g, b, a);
}

