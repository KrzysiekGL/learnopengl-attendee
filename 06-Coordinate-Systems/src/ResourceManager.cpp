#include "ResourceManager.hpp"

ResourceManager::ResourceManager() :
	ResourceManager(std::string("ResourceManager-"+utls::randomName()).c_str()) {}

ResourceManager::ResourceManager(const char * name) {
	this->type = Resource::Type::ResourceManager;
	this->resID = 0;
	this->friendlyName = name;
	// Initialize the resources map with an empty element occupying resID 0
	resources.insert(std::pair<u64, std::shared_ptr<Resource>>{0, NULL});
}

std::weak_ptr<Resource> ResourceManager::insert(Resource * const res) {
	// Generate random name with a prefix specifying of what type is the new resource
	std::string name;
	switch(res->type) {
	case Resource::Type::ResourceManager:
		name = "ResourceManager-";
		break;
	case Resource::Type::Shader:
		name = "Shader-";
		break;
	case Resource::Type::Texture:
		name = "Texture-";
		break;
	case Resource::Type::Context:
		name = "Context-";
		break;
	case Resource::Type::Camera:
		name = "Camera-";
		break;
	default:
		name = "Unknown-";
	}
	name += utls::randomName();

	return insert(name.c_str(), res);
}

std::weak_ptr<Resource> ResourceManager::insert(const char * name, Resource * const res) {
	return insert(std::string(name), res);
}

std::weak_ptr<Resource> ResourceManager::insert(const std::string name, Resource * const res) {
	// Generate Resource ID - take the ID of the latest element in the resources and increment it
	auto res_latest = --(resources.end());
	res->resID = (res_latest->first) + 1;

	res->friendlyName = name;

	const auto [it, success] = resources.insert(std::pair{res->resID, res});
	std::cout << "Insertion of " << *(it->second) << (success ? " succeeded\n" : " failed\n");

	if(success) return it->second;
	else return std::weak_ptr<Resource>();
}

// TODO: searching by name wil not work if there will be two the same named resources; fix it
std::weak_ptr<Resource> ResourceManager::find(const char * name) {
	return find(std::string(name));
 }

std::weak_ptr<Resource> ResourceManager::find(const std::string name) {
	for(const auto & it : resources)
		if(it.second!=NULL && it.second->friendlyName == name)
			return it.second;
	return std::weak_ptr<Resource>();
}

std::weak_ptr<Resource> ResourceManager::find(const u64 resID) {
	const auto it = resources.find(resID);
	if(it!=resources.end()) return it->second;
	return std::weak_ptr<Resource>();
}

void ResourceManager::print(std::ostream & os) const {
	os << "[type:ResourceManager"
		 << "|resID:"<< resID
		 << "|name:" << friendlyName
		 << "]";
}

