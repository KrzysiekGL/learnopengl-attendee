/*
 * Study of OpenGL guided by https://learnopengl.com
 *
 * Author: KrzysiekGL webmaster@unexpectd.com
 * 06/2022
 */

#include <iostream>
#include <math.h>

// Include GLAD before GLFW
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#define WIDTH 800
#define HEIGHT 600

const float vertices[] = {
	.5, .5, .0,
	.5, -.5, .0,
	-.5, -.5, .0,
	-.5, .5, .0,
};

const GLuint indices[] = {
	0, 1, 3,
	1, 2, 3
};

const char * vertexSahderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos\n;"
	"void main() {\n"
	"	gl_Position = vec4(aPos, 1.f);\n"
	"}\n";

const char * fragmentShaderSource = "#version 330 core\n"
	"out vec4 fragColor;\n"
	"uniform vec4 ourColor;\n"
	"void main() {\n"
	"	fragColor = ourColor;\n"
	"}\n";

void framebufferSizeCallback(GLFWwindow * window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow * window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main(int argc, char ** argv, char ** eval) {
	std::cout << "01-Creating_a_window\n";

	// GLFW initializationf
	glfwInit();
	// OpenGL version and features
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Window features
	glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

	// GLFW window creation
	GLFWwindow * window = glfwCreateWindow(WIDTH, HEIGHT, "learnopengl", NULL, NULL);
	if(window == NULL) {
		std::cout << "ERROR: Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Map to the OpenGL function pointers with GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "ERROR: Failed to initialize OpenGL context (GLAD)\n";
		glfwTerminate();
		return -1;
	}

	// Maximum Vertex Attributes supported by the hardware (at least 16*vec4)
	{
		int numAttribs;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numAttribs);
		std::cout << "Maximum number of attributes supported: " << numAttribs << "\n";
	}

	// GLFW callbacks
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	// OpenGL state machine settings
	framebufferSizeCallback(window, WIDTH, HEIGHT);
	glClearColor(.2f, .3f, .3f, 1.f);

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

	// Vertex shader
	unsigned int vertexShader;
	if(!(vertexShader = glCreateShader(GL_VERTEX_SHADER))) {
		std::cout << "ERROR: Failed to create vertex shader object\n";
		glfwTerminate();
		return -1;
	}
	glShaderSource(vertexShader, 1, &vertexSahderSource, NULL);
	glCompileShader(vertexShader);
	{
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if(!success) {
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR: Vertex shader compilation failed\n" << infoLog << std::endl;
		}
	}

	// Fragment shader
	unsigned int fragmentShader;
	if(!(fragmentShader = glCreateShader(GL_FRAGMENT_SHADER))) {
		std::cout << "ERROR: Failed to create fragment shader object\n";
		glfwTerminate();
		return -1;
	}
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	{
		int success;
		char infoLog[512];
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if(!success) {
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR: Fragment shader compilation failed\n" << infoLog << std::endl;
		}
	}

	// Shader program
	unsigned int shaderProgram;
	if(!(shaderProgram = glCreateProgram())) {
		std::cout << "ERROR: Failed to create shader program object\n";
		glfwTerminate();
		return -1;
	}
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	{
		int success;
		char infoLog[512];
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if(!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR: Shader program linking failed\n" << infoLog << std::endl;
		}
	}

	// Uniforms
	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2.f) + .5f;
	int uniformOurColor = glGetUniformLocation(shaderProgram, "ourColor");
	std::cout << "ourColor location: " << uniformOurColor << "\n";
	glUseProgram(shaderProgram);
	glUniform4f(uniformOurColor, 0.f, greenValue, 0.f, 1.f);
	glUseProgram(0);

	// Setup OpneGL to use the shader program and clean-up unneccesary now shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glUseProgram(shaderProgram);

	// End of temp space for rendering stuff
	// -----------------------------------------------------------------------------------------------

	// Game loop/Render loop
	while(!glfwWindowShouldClose(window)) {
		// Input
		processInput(window);

		// Rendering

		//Clrear color buffer
		glClear(GL_COLOR_BUFFER_BIT);

		// Chagne uniform value
		greenValue = (sin(glfwGetTime())/2.f)+.5f;
		glUseProgram(shaderProgram);
		glUniform4f(uniformOurColor, 0.f, greenValue, 0.f, 1.f);
		glUseProgram(0);

		// Render rectangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLuint), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glUseProgram(0);

		// Events & Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Clean-up
	glfwTerminate();
	return 0;
}

