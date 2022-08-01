/*
 * This is a small Resource manager for all of the other classes that
 * are required to be manged somehow so there is something which keeps track of them.
 *
 * Each time a Resource is added, a resID (resource ID) is generated for it.
 * resID equal 0 (zero) is reserved for the ResourceManager object itself.
 *
 * 2022
 * Author: KrzysiekGL webmaster@unexpectd.com; All rights reserved.
 */

#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <memory>
#include <map>

#include "Resource.hpp"
#include "utils.hpp"

class ResourceManager: public Resource {
public:
	ResourceManager();
	ResourceManager(const char * name);

	// Delete copy and assignment constructors
	ResourceManager(const ResourceManager &) = delete;
	ResourceManager & operator=(const ResourceManager &) = delete;

	// Add a resrorce; return resID if success, otherwise return 0
	u64 add(Resource * const res);
	u64 add(const char * name, Resource * const res);

	// Get a resource; return reference to the object, otherwise reuturn NULL
	//Resource * get(const char * name);
	//Resource * get(const u64 resID);

private:
	std::map<u64, std::shared_ptr<Resource>> resources;

	virtual void print(std::ostream & os) const override;
};

#endif /* RESOURCE_MANAGER_HPP */

