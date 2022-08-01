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

u64 ResourceManager::add(Resource * const res) {
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

	return add(name.c_str(), res);
}

u64 ResourceManager::add(const char * name, Resource * const res) {
	// Generate Resource ID - take the ID of the latest element in the resources and increment it
	auto res_latest = --(resources.end());
	res->resID = (res_latest->first) + 1;

	res->friendlyName = name;

	const auto [it, success] = resources.insert(std::pair{res->resID, res});
	std::cout << "Insertion of " << *(it->second) << (success ? " succeeded\n" : " failed\n");

	if(success) return res->resID;
	else return 0;
}

// Resource * ResourceManager::get(const char * name) {
// 	for(const std::pair<u64, Resource *> & p : resources)
// 		if(p.second->getFriendlyName().c_str() == name)
// 			return p.second;
// 	return NULL;
// }

// Resource & ResourceManager::get(const u64 resID) {
// 	std::pair<u64, Resource *> p = resources.find(resID);
// 	if(p!=resources.end()) return *(p->second);
// 	else return NULL;
// }


void ResourceManager::print(std::ostream & os) const {
	os << "[type:ResourceManager"
		 << "|resID:"<< resID
		 << "|name:" << friendlyName
		 << "]";
}

