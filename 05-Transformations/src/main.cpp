/*
 * Study of OpenGL guided by https://learnopengl.com
 *
 * 2022
 * Author: KrzysiekGL webmaster@unexpectd.com; All rights reserved.
 */

#include <iostream>
#include <math.h>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ResourceManager.hpp"
#include "Resource.hpp"
#include "Context.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

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

	{
		std::cout << "----- GLM demo -----\n";
		glm::vec4 vec(1.f, 0.f, 0.f, 1.f);
		glm::mat4 transform = glm::mat4(1.f); // identity matrix
		transform = glm::translate(transform, glm::vec3(1.f, 1.f, 0.f));
		vec = transform * vec;
		std::cout << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << "\n";
		std::cout << "--------------------\n";
	}

	glfwInit();

	// Main (for now single) Resource Manager
	ResourceManager resMan;

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
	u64 tex1 = resMan.insert(new Texture("../texture/container.jpg", GL_TEXTURE_2D));
	u64 tex2 = resMan.insert(new Texture("../texture/face.png", GL_TEXTURE_2D));
	// -----------------------------------------------------------------------------------------------
	// Shader program
	u64 shad1 = resMan.insert(new Shader("../shader/transform.vert", "../shader/transform.frag"));
	std::static_pointer_cast<Shader>(resMan.find(shad1))->setInt("texture0", 0);
	std::static_pointer_cast<Shader>(resMan.find(shad1))->setInt("texture1", 1);
	// -----------------------------------------------------------------------------------------------
	// Transformations
	glm::mat4 trans = glm::mat4(1.f);
	trans = glm::rotate(trans, glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f));
	trans = glm::scale(trans, glm::vec3(.5f, .5f, .5f));
	std::static_pointer_cast<Shader>(resMan.find(shad1))->setMat4("transform", trans);
	// End of temp space for rendering stuff
	// -----------------------------------------------------------------------------------------------

	// Game loop/Render loop
	while(!context.shouldClose()) {
		// Input & Context state
		context.updateContextState();
		context.processInput();

		// Transformations in time
		glm::mat4 trans = glm::mat4(1.f);
		trans = glm::translate(trans, glm::vec3(.5f, -.5f, .0f));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(.0f, .0f, 1.f));

		// Rendering

		// Clrear color buffer
		glClear(GL_COLOR_BUFFER_BIT);

		// Render the rectangle
		glActiveTexture(GL_TEXTURE0);
		std::static_pointer_cast<Texture>(resMan.find(tex1))->activate();

		glActiveTexture(GL_TEXTURE1);
		std::static_pointer_cast<Texture>(resMan.find(tex2))->activate();

		std::static_pointer_cast<Shader>(resMan.find(shad1))->activate();
		std::static_pointer_cast<Shader>(resMan.find(shad1))->setMat4("transform", trans);

		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLuint), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glUseProgram(0);

		// Events & Swap buffers
		context.swapBuffers();
		glfwPollEvents();
	}

	// Clean-up
	glfwTerminate();

	return 0;
}

