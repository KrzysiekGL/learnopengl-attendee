/*
 * Study of OpenGL guided by https://learnopengl.com
 *
 * 2022
 * Author: KrzysiekGL webmaster@unexpectd.com; All rights reserved.
 */

#include <iostream>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Context.hpp"
#include "Shader.hpp"

const float vertices[] = {
	// positions		// colors				// texture coordinates
   0.5f,	0.5f, 0.0f,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f,		// top right
	 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		// bottom right
	-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,		0.0f, 0.0f,		// bottom left
	-0.5f,	0.5f, 0.0f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f		// top left
};
const GLuint indices[] = {
	0, 1, 2,
	2, 3, 0,
};

int main(int argc, char ** argv, char ** eval) {
	std::cout << "05-Textures\n";

	std::cout << "----- GLM demo -----\n";
	glm::vec4 vec(1.f, 0.f, 0.f, 1.f);
	glm::mat4 transform = glm::mat4(1.f); // identity matrix
	transform = glm::translate(transform, glm::vec3(1.f, 1.f, 0.f));
	vec = transform * vec;
	std::cout << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << "\n";
	std::cout << "--------------------\n";

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
	// aPos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// aColor
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	// aTexCoord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2);

	// Bind to default buffers (VAO (!*), VBO, EBO)
	// *VAO keeps track of the last bound EBO while the VAO is bound.
	// So if the default EBO was bound before default VAO, then the
	// VAO would keep track of the default EBO, which is 0
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	// -----------------------------------------------------------------------------------------------
	// 2D Texture
	// Tell STBI (image lib) to flip images vertically (0.0 lands on the down-left corner instead of up-left)
	stbi_set_flip_vertically_on_load(true);
	// Create a texture object
	GLuint texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// Set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Loading an image/texture
	GLint width, height, nrChannels;
	const char * container = "../texture/container.jpg";
	unsigned char * data = stbi_load(container, &width, &height, &nrChannels, 0);
	if(data==NULL) std::cerr << "Image " << container << "  not loaded\n";
	std::cout << width << " " << height << " " << nrChannels << std::endl;
	// Generate texture (on the currently bound texture at the active texture unit)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	// Free the image data (unsigned char *) memory
	stbi_image_free(data);

	// Bind default 2D texture
	glBindTexture(GL_TEXTURE_2D, 0);
	// Second Texture
	GLuint texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	const char * face = "../texture/face.png";
	data = stbi_load(face, &width, &height, &nrChannels, 0);
	if(data==NULL) std::cerr << "Image " << face << " not loaded\n";
	std::cout << width << " " << height << " " << nrChannels << "\n";

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
	// -----------------------------------------------------------------------------------------------
	// Shader program
	Shader basic("../shader/texture.vert", "../shader/texture.frag");
	basic.setInt("texture0", 0);
	basic.setInt("texture1", 1);
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
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		basic.activate();
		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLuint), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		basic.deactivate();

		// Events & Swap buffers
		context.swapBuffers();
		glfwPollEvents();
	}

	// Clean-up
	glfwTerminate();

	return 0;
}

