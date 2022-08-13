/*
 * This class allows to create a OpenGL's Texture object.
 * Along with that, it also handles the process of loading an image,
 * binding it as a GL's texture, and setting texture's parameters.
 * The process is as follows:
 *
 * 1) Generate new texture object OpenGL buffer
 * 2) Set it's parameters
 * 3) Load an image with STBI lib
 * 4) Generate the texture and mipmaps
 * 5) Free unused data from the memory
 *
 * Note that currently only 2D textures are supported. If 3D texture used,
 * behavior of the class is not defined.
 *
 * 2022
 * Author: KrzysiekGL webmaster@unexpectd.com; All rights reserved.
 */

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>
#include <cassert>
#include <atomic>
#include <exception>

#include <glad/glad.h>

#include "Resource.hpp"

class Texture: public Resource {
public:
	Texture(const char * path, GLenum target);

	// Delete copy and assignment constructors
	Texture(const Texture &) = delete;
	Texture & operator=(const Texture &) = delete;

	// Bind this texture to the GL target
	void activate() const { glBindTexture(target, ID); }

	// Get the GL target of this texture
	GLenum getTarget() const { return target; }

	// Get OpenGL specific ID of this type of resource
	GLuint getGLID() const { return ID; };

private:
	// OpenGL object ID
	GLuint ID;
	GLenum target;

	// Texture parameters
	GLenum textureDimension;
	GLint width;
	GLint height;
	GLint numberOfChannels;
	std::string texturePath;

	// STBI imagage global settings
	static std::atomic<bool> imageFlipped;

	// Elevate this Texture if not active. Thread safe.
	void elevate();
	void deelevate();

	virtual void print(std::ostream & os) const override;
};

#endif /* TEXTURE_HPP */

