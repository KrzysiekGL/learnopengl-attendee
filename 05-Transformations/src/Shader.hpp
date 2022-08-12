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
 * 2022
 * Author: KrzysiekGL webmaster@unexpectd.com; All rights reserved.
 */

#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <iostream>
#include <cassert>
#include <atomic>

#include <glad/glad.h>

#include "utils.hpp"
#include "Resource.hpp"

class Shader: public Resource {
public:
	// Create a shader program from given shaders source files
	// Convention used:
	// .vert for a vertex shader
	// .frag for a fragment shader
	Shader(const char* vertexPath, const char* fragmentPath);

	// Delete copy and assignment constructors
	Shader(const Shader &) = delete;
	Shader & operator=(const Shader &) = delete;

	// Activate this Shader
	void activate() const { glUseProgram(ID); }

	// Setters for uniforms in shaders
	void setFloat(const char* uniformName, float value) const;
	void setInt(const char* uniformName, int value) const;
	void setBool(const char* uniformName, bool value) const;

	// Get OpenGL specific ID of this type of resource
	GLuint getGLID() const { return ID; };

private:
	// Shader types enum
	enum Type {
		Vertex,
		Fragment
	};

	// OpenGL object ID
	GLuint ID;

	// Shader info
	std::string vertexPath;
	std::string fragmentPath;

	// Create and complie a shader
	GLuint buildShader(std::string source, Type type);

	// Print information about this Shader using the level of deatils
	virtual void print(std::ostream & os) const override;
};

#endif /* SHADER_HPP */

