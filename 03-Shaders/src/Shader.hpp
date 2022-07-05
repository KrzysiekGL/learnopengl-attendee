#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <cassert>

#include <glad/glad.h>

class Shader {
public:
	// Create a shader program from given shaders source files
	// Convention used:
	// .vert for a vertex shader
	// .frag for a fragment shader
	Shader(const char* vertexPath, const char* fragmentPath);

	// Force Activate
	void activate() const;
	// Force Deactivate
	void deactivate() const;
	// Check if is Activated or not
	bool isActive() const;

	void setFloat(const char* uniformName, float value) const;

private:
	// Shader types enum
	enum Type {
		Vertex,
		Fragment
	};

	// Reads a file into a std::string
	void readFile(std::string path, std::string & readBuf);

	// Create and complie a shader
	GLuint buildShader(std::string source, Type type);

	GLuint ID;
	bool active;
};

#endif /* SHADER_HPP */

