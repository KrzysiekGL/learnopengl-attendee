/*
 * Abstract class for each object which should be managable by the ResoruceManger class.
 *
 * 2022
 * Author: KrzysiekGL webmaster@unexpectd.com; All rights reserved.
 */

#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <iostream>
#include <string>
#include <memory>

#include "utils.hpp"

class Resource {
public:
	virtual ~Resource() = default;

	// Resource type
	enum class Type {
		ResourceManager,
		Shader,
		Texture,
		Context,
		Camera
	};

	// Print information about a resource
	friend std::ostream & operator<<(std::ostream & os, const Resource & res) {
		res.print(os);
		return os;
	}

	std::string getFriendlyName() { return friendlyName; }

protected:
	Type type;
	u64 resID;
	std::string friendlyName;

	virtual void print(std::ostream & os) const = 0;

	// Freindship declaration with the Resourcemanager class
	// so that an Resourcemanager object could manipulate private
	// data of an Resource object
	friend class ResourceManager;
};

#endif /* RESOURCE_HPP */

