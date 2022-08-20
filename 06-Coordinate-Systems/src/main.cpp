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
#include "Camera.hpp"
#include "utils.hpp"

// Coordinates; Texture Coordinates
float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
	glm::vec3( 0.0f,  0.0f,  0.0f),
	glm::vec3( 2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3( 2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,	3.0f, -7.5f),
	glm::vec3( 1.3f, -2.0f, -2.5f),
	glm::vec3( 1.5f,  2.0f, -2.5f),
	glm::vec3( 1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

int main(int argc, char ** argv, char ** eval) {
	std::cout << "06-Coordinate-Systems\n";

	glfwInit();

	// Main (for now single) Resource Manager
	ResourceManager resMan;

	std::weak_ptr<Resource> context = resMan.insert(new Context("learnopengl"));
	UTLS_WSCAST(Context, context)->makeCurrent();

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

	// Linking Vertex Attributes
	// aPos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// aTexCoord
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	// Bind to default buffers (VAO (!*), VBO, EBO)
	// *VAO keeps track of the last bound EBO while the VAO is bound.
	// So if the default EBO was bound before default VAO, then the
	// VAO would keep track of the default EBO, which is 0
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	// -----------------------------------------------------------------------------------------------
	// 2D Texture
	std::weak_ptr<Resource> tex1 = resMan.insert(new Texture("../texture/container.jpg", GL_TEXTURE_2D));

	std::weak_ptr<Resource> tex2 = resMan.insert(new Texture("../texture/face.png", GL_TEXTURE_2D));
	// -----------------------------------------------------------------------------------------------
	// Shader program
	std::weak_ptr<Resource> shad1 = resMan.insert(new Shader("../shader/coordinates.vert",
																												 "../shader/coordinates.frag"));

	UTLS_WSCAST(Shader, shad1)->setInt("texture0", 0);
	UTLS_WSCAST(Shader, shad1)->setInt("texture1", 1);
	// -----------------------------------------------------------------------------------------------
	// 3D Transformations - all coordinate systems pipeline
	glm::mat4 model = glm::mat4(1.f);
	model = glm::rotate(model, glm::radians(-55.f), glm::vec3(1.f, 0, 0));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.f), UTLS_WSCAST(Context, context)->getRatio(), .1f, 100.f);

	UTLS_WSCAST(Shader, shad1)->setMat4("model", model);
	UTLS_WSCAST(Shader, shad1)->setMat4("projection", projection);

	std::weak_ptr<Resource> cam = resMan.insert(new Camera(glm::vec3(0, 0, 3.f)));
	// End of temp space for rendering stuff
	// -----------------------------------------------------------------------------------------------

	glEnable(GL_DEPTH_TEST);

	// Time delta for movement/animation
	float timeDelta = 0.f;
	float lastFrameTime = 0.f;
	float currentTime = 0.f;

	// Game loop/Render loop
	while(!UTLS_WSCAST(Context, context)->shouldClose()) {
		// Time
		currentTime = glfwGetTime();
		timeDelta = currentTime - lastFrameTime;
		lastFrameTime = currentTime;

		// Input & Context state
		UTLS_WSCAST(Context, context)->updateContextState();
		UTLS_WSCAST(Context, context)->processInput(UTLS_WSCAST(Camera, cam), timeDelta);

		// Rendering

		// Clrear color buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render the rectangle
		glActiveTexture(GL_TEXTURE0);
		UTLS_WSCAST(Texture, tex1)->activate();

		glActiveTexture(GL_TEXTURE1);
		UTLS_WSCAST(Texture, tex2)->activate();

		UTLS_WSCAST(Shader, shad1)->activate();

		glBindVertexArray(VAO);

		glm::mat4 view = UTLS_WSCAST(Camera, cam)->getLookAt();

		UTLS_WSCAST(Shader, shad1)->setMat4("view", view);
		UTLS_WSCAST(Shader, shad1)->setMat4("projection", projection);

		for(u64 i = 0; i<10; ++i) {
			glm::mat4 model = glm::mat4(1.f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.f * i;
			if(!(i%3))
				model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1, 0, 0));
			else
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1, 0, 0));
			UTLS_WSCAST(Shader, shad1)->setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glUseProgram(0);

		// Events & Swap buffers
		std::static_pointer_cast<Context>(context.lock())->swapBuffers();
		glfwPollEvents();
	}

	// Clean-up
	glfwTerminate();

	return 0;
}

