/*
 * Study of OpenGL guided by https://learnopengl.com
 *
 * Author: KrzysiekGL webmaster@unexpectd.com
 * 06/2022
 */

#include <iostream>
#include <math.h>

#include <glad/glad.h>

#include "Context.hpp"
#include "Shader.hpp"

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

int main(int argc, char ** argv, char ** eval) {
	std::cout << "03-Shaders\n";

	Context context("learnopengl");

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
	while(!context.shouldClose()) {
		// Input
		context.processInput();
		context.updateContextState();

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
		context.swapBuffers();
		Context::pollEvents();
	}

	// Clean-up
	glfwTerminate();
	return 0;
}

