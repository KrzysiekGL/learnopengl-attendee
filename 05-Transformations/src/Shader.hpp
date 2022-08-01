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
 * Changes can be issued to the OpenGL state machine (glProgram domain)
 * by a thread only if `occupantShaderID` is set to *this* ID.
 * After a thread finishes it's job, it is obliged to set `occupantShaderID` to 0.
 * This is for thread safety reasons.
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

	// Try to activate this Shader and return 0 if succeeded.
	// If the occupying Texture object is not using the same target (e.g. GL_TEXTURE_2D)
	// then it's is safe to proceed.
	// Thread safe, if couldn't activate, return ID of the currently activated.
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

	// OpenGL object ID
	GLuint ID;

	// Thread safety
	static std::atomic<GLuint> occupantShaderID;

	// Create and complie a shader
	GLuint buildShader(std::string source, Type type);

	// Print information about this Shader using the level of deatils
	virtual void print(std::ostream & os) const override;
};

#endif /* SHADER_HPP */

