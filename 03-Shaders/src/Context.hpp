#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#define WIDTH 800
#define HEIGHT 600

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Context {
public:
	// Glfw context creation along with OpenGL initialization
	Context(std::string windowName, int width = WIDTH, int height = HEIGHT);

	// Should this context be closed
	bool shouldClose() const;

	// Process input from the game loop (may be changed in the future)
	void processInput() const;

	// Updates width & height of the context
	void updateContextState();

	// Swap buffers for context
	void swapBuffers() const;

	// Poll events for GLFW
	static void pollEvents();

private:
	GLFWwindow * window;
	int width;
	int height;

	// Sets glViewport when window resizes
	static void framebufferSizeCallback(GLFWwindow * window, int width, int height);
};

#endif /* CONTEXT_HPP */

