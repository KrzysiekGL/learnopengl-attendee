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

u64 ResourceManager::insert(Resource * const res) {
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
	default:
		name = "Unknown-";
	}
	name += utls::randomName();

	return insert(name.c_str(), res);
}

u64 ResourceManager::insert(const char * name, Resource * const res) {
	return insert(std::string(name), res);
}

u64 ResourceManager::insert(const std::string name, Resource * const res) {
	// Generate Resource ID - take the ID of the latest element in the resources and increment it
	auto res_latest = --(resources.end());
	res->resID = (res_latest->first) + 1;

	res->friendlyName = name;

	const auto [it, success] = resources.insert(std::pair{res->resID, res});
	std::cout << "Insertion of " << *(it->second) << (success ? " succeeded\n" : " failed\n");

	if(success) return res->resID;
	else return 0;
}

// TODO: searching by name wil not work if there will be two the same named resources; fix it
std::shared_ptr<Resource> ResourceManager::find(const char * name) {
	return find(std::string(name));
 }

std::shared_ptr<Resource> ResourceManager::find(const std::string name) {
	std::shared_ptr<Resource> res = NULL;
	for(const auto & it : resources)
		if(it.second!=NULL && it.second->friendlyName == name)
			res = it.second;
	return res;
}

std::shared_ptr<Resource> ResourceManager::find(const u64 resID) {
	std::shared_ptr<Resource> res = NULL;
	const auto it = resources.find(resID);
	if(it!=resources.end()) res = it->second;
	return res;
}

void ResourceManager::print(std::ostream & os) const {
	os << "[type:ResourceManager"
		 << "|resID:"<< resID
		 << "|name:" << friendlyName
		 << "]";
}

