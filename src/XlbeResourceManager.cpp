#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeResourceManager.h"

////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////////
Resource_Manager::Resource_Manager()
{
}

Resource_Manager::~Resource_Manager()
{

}

int Resource_Manager::number_resource()
{
	return resources_.size();
}

bool Resource_Manager::is_all_loaded_resource()
{
	bool loaded = false;
	Resources::iterator iend = resources_.end();
	for (Resources::iterator i = resources_.begin(); i != iend; ++i)
		loaded |= i->second->is_loaded();

	return loaded;
}	

void Resource_Manager::load_all_resource()
{
	Resources::iterator iend = resources_.end();
	for (Resources::iterator i = resources_.begin(); i != iend; ++i)
		i->second->load();
}

void Resource_Manager::unload_all_resource()
{
	Resources::iterator iend = resources_.end();
	for (Resources::iterator i = resources_.begin(); i != iend; ++i)
		i->second->unload();
}

void Resource_Manager::destroy_all_resource()
{
	Resources::iterator iend = resources_.end();
	for (Resources::iterator i = resources_.begin(); i != iend; ++i)
	{
		i->second->unload();
		delete i->second;
	}
    
	resources_.clear();	
}

void Resource_Manager::load_resource(const std::string &name)
{
	Resources::iterator ifind = resources_.find(name);
	if (ifind != resources_.end())
	{
		ifind->second->load();
	}
}

void Resource_Manager::unload_resource(const std::string &name)
{
	Resources::iterator ifind = resources_.find(name);
	if (ifind != resources_.end())
	{
		ifind->second->unload();
	}
}

void Resource_Manager::destroy_resource(const std::string &name)
{
	Resources::iterator ifind = resources_.find(name);
	if (ifind != resources_.end())
	{
		ifind->second->unload();
		resources_.erase(ifind);
	}
}

Resource *Resource_Manager::get_resource(const std::string &name)
{
	Resources::iterator ifind = resources_.find(name);
	if (ifind != resources_.end())
	{
		return ifind->second;
	}
	else
		return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////
} 