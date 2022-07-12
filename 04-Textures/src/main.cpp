/*
 * Study of OpenGL guided by https://learnopengl.com
 *
 * Author: KrzysiekGL webmaster@unexpectd.com
 * 06/2022
 */

#include <iostream>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Context.hpp"
#include "Shader.hpp"

const float vertices[] = {
	.5, .0, .0,
	-.5,.0, .0,
	.0, .5, .0,
};

const GLuint indices[] = {
	0, 1, 2,
};

const float texCoords[] = {
	.0f, .0f,
	1.f, .0f,
	.5f, 1.f,
};

int main(int argc, char ** argv, char ** eval) {
	std::cout << "03-Shaders\n";

	glfwInit();

	Context context("learnopengl");
	context.makeCurrent();

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

	// Bind to default buffers (VAO (!*), VBO, EBO)
	// *VAO keeps track of the last bound EBO while the VAO is bound.
	// So if the default EBO was bound before default VAO, then the
	// VAO would keep track of the default EBO, which is 0
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	// -----------------------------------------------------------------------------------------------
	// 2D Texture
	// Create a texture object
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// Set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Loading an image/texture
	GLint width, height, nrChannels;
	unsigned char * data = stbi_load("../texture/container.jpg", &width, &height, &nrChannels, 0);
	if(data==NULL) std::cerr << "Image not loaded\n";
	std::cout << width << " " << height << " " << nrChannels << std::endl;
	// Generate texture (on the currently bound texture at the active texture unit)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	// Free the image data (unsigned char *) memory
	stbi_image_free(data);
	// -----------------------------------------------------------------------------------------------
	// Shader program
	Shader basic("../shader/texture.vert", "../shader/texture.frag");
	// End of temp space for rendering stuff
	// -----------------------------------------------------------------------------------------------

	// Game loop/Render loop
	while(!context.shouldClose()) {
		// Input & Context state
		context.updateContextState();
		context.processInput();

		// Rendering

		// Clrear color buffer
		glClear(GL_COLOR_BUFFER_BIT);

		// Render rectangle
		basic.activate();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLuint), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		basic.deactivate();

		// Events & Swap buffers
		context.swapBuffers();
		glfwPollEvents();
	}

	// Clean-up
	glfwTerminate();

	return 0;
}

