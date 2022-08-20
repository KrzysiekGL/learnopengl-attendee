#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

std::atomic<bool> Texture::imageFlipped(false);

Texture::Texture(const char * path, GLenum target) : target(target) {
	if(path==NULL)
		throw std::ios_base::failure("Texture path is NULL\n");
	texturePath = path;

	// One time switch for STBI settings, change in future if needed
	bool expected = false;
	if(imageFlipped.compare_exchange_strong(expected, true))
		stbi_set_flip_vertically_on_load(true);

	// Resource type
	type = Resource::Type::Texture;

	// Generate a texture object and set the parameters
	glGenTextures(1, &ID);
	activate();

	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load an image/texture
	unsigned char * data = stbi_load(path, &width, &height, &numberOfChannels, 0);
	if(data==NULL)
		throw std::runtime_error("Couldn't load image\n");

	// Generate texture
	GLenum format = (numberOfChannels==4 ? GL_RGBA : GL_RGB);
	glTexImage2D(target, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(target);

	// Cleanup
	stbi_image_free(data);
	glBindTexture(target, 0);
}

void Texture::print(std::ostream & os) const {
	os << "[type:Texture"
		 << "|resID:" << resID
		 << "|name:" << friendlyName
		 << "|OpenGL ID:" << ID
		 << "|OpenGL target:" << target
		 << "|width:" << width
		 << "|height:" << height
		 << "|number of channels:" << numberOfChannels
		 << "|path:" << texturePath
		 << "]";
}

