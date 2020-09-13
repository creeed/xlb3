#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeResourceManager.h"
#include "XlbeResourceGroupManager.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

template<> Resource_Group_Manager* Singleton<Resource_Group_Manager>::singleton_ = 0;
Resource_Group_Manager* Resource_Group_Manager::singleton()
{
   return singleton_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Resource_Group_Manager::Resource_Group_Manager()
{
}

Resource_Group_Manager::~Resource_Group_Manager()
{
}

void Resource_Group_Manager::register_resource_manager(const std::string& resource_type, Resource_Manager* rm)
{
    resource_manager_map_[resource_type] = rm;
}

void Resource_Group_Manager::unregister_resource_manager(const std::string& resource_type)
{
    Resource_Manager_Map::iterator iter = resource_manager_map_.find(resource_type);

    if (iter != resource_manager_map_.end())
    {
        resource_manager_map_.erase(iter);
    }
}

void Resource_Group_Manager::declare_resource_group(const std::string &resource_group, const std::string &resource_directory)
{
    Root::singleton()->resource_provider()->set_resource_group_directory(resource_group, resource_directory);

    Resource_Manager_Map::iterator i = resource_manager_map_.begin();

    for (; i != resource_manager_map_.end(); ++i)
    {
        i->second->declare_resource_group(resource_group);
    }
}

void Resource_Group_Manager::undeclare_resource_group(const std::string &resource_group)
{
    Resource_Manager_Map::iterator i = resource_manager_map_.begin();

    for (; i != resource_manager_map_.end(); ++i)
    {
        i->second->undeclare_resource_group(resource_group);
    }
}

void Resource_Group_Manager::initialise_resource_group(const std::string &resource_group)
{
    Resource_Manager_Map::iterator i = resource_manager_map_.begin();

    for (; i != resource_manager_map_.end(); ++i)
    {
        i->second->initialise_resource_group(resource_group);
    }
}

void Resource_Group_Manager::destroy_resource_group(const std::string &resource_group)
{
    Resource_Manager_Map::iterator i = resource_manager_map_.begin();

    for (; i != resource_manager_map_.end(); ++i)
    {
        i->second->destroy_resource_group(resource_group);
    }
}

void Resource_Group_Manager::load_resource_group(const std::string &resource_group)
{
    start_load_resources(resource_group);

    while(load_next_resource())
    {
    }
}

void Resource_Group_Manager::unload_resource_group(const std::string &resource_group)
{
    Resource_Manager_Map::iterator i = resource_manager_map_.begin();

    for (; i != resource_manager_map_.end(); ++i)
    {
        i->second->unload_resource_group(resource_group);
    }
}

void Resource_Group_Manager::start_load_resources(const std::string &group)
{
    cur_resource_group_ = group;
    cur_resource_manager_ = resource_manager_map_.begin();

    if (cur_resource_manager_ != resource_manager_map_.end())
        cur_resource_manager_->second->start_load_resources(group);
}

bool Resource_Group_Manager::load_next_resource()
{
    if (cur_resource_manager_ == resource_manager_map_.end())
        return false;

    if (!cur_resource_manager_->second->load_next_resource())
    {
        cur_resource_manager_ ++;

        if (cur_resource_manager_ != resource_manager_map_.end())
        {
            cur_resource_manager_->second->start_load_resources(cur_resource_group_);
        }
    } 

    return true;
}

bool Resource_Group_Manager::is_declared_resource_group(const std::string &resource_group)
{
    bool declared = false;

    Resource_Manager_Map::iterator i = resource_manager_map_.begin();

    for (; i != resource_manager_map_.end(); ++i)
    {
        declared &= i->second->is_declared_resource_group(resource_group);
    }

    return declared;
}

bool Resource_Group_Manager::is_initialise_resource_group(const std::string &resource_group)
{
    bool initialised = false;

    Resource_Manager_Map::iterator i = resource_manager_map_.begin();

    for (; i != resource_manager_map_.end(); ++i)
    {
        initialised &= i->second->is_initialise_resource_group(resource_group);
    }

    return initialised;
}

bool Resource_Group_Manager::is_loaded_resource_group(const std::string &resource_group)
{
    bool loaded = false;

    Resource_Manager_Map::iterator i = resource_manager_map_.begin();

    for (; i != resource_manager_map_.end(); ++i)
    {
        loaded &= i->second->is_loaded_resource_group(resource_group);
    }

    return loaded;
}

int Resource_Group_Manager::number_resource(const std::string &resource_group)
{
    int count = 0;

    Resource_Manager_Map::iterator i = resource_manager_map_.begin();

    for (; i != resource_manager_map_.end(); ++i)
    {
        count += i->second->number_resource(resource_group);
    }

    return count;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
}