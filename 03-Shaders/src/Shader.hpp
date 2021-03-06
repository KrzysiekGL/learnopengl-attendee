/*
 * This class allows to create a OpenGL's Shader Program object.
 * The process of creation involves:
 * 1) creating Vertex & Fragment shaders (reading source, compilation),
 * 2) linking the Shaders inside a Shader Program,
 * 3) cleanup of excess resources (Shaders no longer required on their own).
 * Along that, there are messages with errors displayed if they occur.
 *
 * The class allows to:
 * - create a shader program
 * - use a shader program
 * - set uniforms inside shaders
 *
 * Author: KrzysiekGL webmaster@unexpectd.com
 * 06/2022
 */

#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <iostream>
#include <cassert>

#include <glad/glad.h>

#include "utils.hpp"

class Shader {
public:
	// Create a shader program from given shaders source files
	// Convention used:
	// .vert for a vertex shader
	// .frag for a fragment shader
	Shader(const char* vertexPath, const char* fragmentPath);

	// Delete copy and assignment constructors
	Shader (const Shader &) = delete;
	Shader & operator=(const Shader &) = delete;

	// Activate and return ID of the previusly activated, if there was any (including 0)
	GLint activate() const;
	// Deactivate only if is activated
	void deactivate() const;
	// Get ID of the currently activated shader program
	static GLint currentlyActivated();

	// Setters for uniforms in shaders
	void setFloat(const char* uniformName, float value) const;
	void setInt(const char* uniformName, int value) const;
	void setBool(const char* uniformName, bool value) const;

private:
	// Shader types enum
	enum Type {
		Vertex,
		Fragment
	};

	GLuint ID;

	// Create and complie a shader
	GLuint buildShader(std::string source, Type type);
};

#endif /* SHADER_HPP */

