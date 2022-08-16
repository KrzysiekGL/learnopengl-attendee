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

typedef unsigned long long u64;

class Resource {
public:
	virtual ~Resource() = default;

	// Resource type
	enum class Type {
		ResourceManager,
		Shader,
		Texture,
		Context
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

	friend class ResourceManager;
};

#endif /* RESOURCE_HPP */

