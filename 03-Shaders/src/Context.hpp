#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "callbacks.hpp"

class Context {
public:
	// Glfw context creation along with OpenGL initialization
	Context(std::string windowName, int width = 800, int height = 600);

	// Should this context be closed
	bool shouldClose() const;

	// Process input from the game loop (may be changed in the future)
	void processInput() const;

	// Updates width & height of the context
	void updateContextState();

	// Swap buffers for context
	void swapBuffers() const;

	// Make context current for OpenGL and set GLFW callbacks for this context
	void makeCurrent();

	// Check if OpenGL was mapped for this context
	bool isOpenGLMapped() const;

	// Get supported maximum number of atributes for shaders
	int getNumAttributes();

private:
	GLFWwindow * window;
	int width;
	int height;
	float backgroundColor[4];
	bool openglMapped = false;

	// Push OpenGL viewport according to this context
	void pushViewport() const;

	// Push OpenGL background clear color
	void pushBackgroundColor() const;

	// Map to the OpenGL function pointers with GLAD
	void mapOpenGL();

};

#endif /* CONTEXT_HPP */
