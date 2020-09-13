#include "XlbeResourceProvider.h"

////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////////
void Resource_Provider::set_resource_group_directory(const std::string& resource_group, const std::string& directory)
{
    if (directory.length() == 0)
        return;

	const std::string separators("\\/");

    if (std::string::npos == separators.find(directory[directory.size() - 1]))
        resource_groups_[resource_group] = directory + '/';
    else
        resource_groups_[resource_group] = directory;
}

const std::string& Resource_Provider::get_resource_group_directory(const std::string& resource_group)
{
    return resource_groups_[resource_group];
}

void Resource_Provider::clear_resource_group_directory(const std::string& resource_group)
{
	Resource_Group_Map::iterator iter = resource_groups_.find(resource_group);

    if (iter != resource_groups_.end())
        resource_groups_.erase(iter);
}

////////////////////////////////////////////////////////////////////////////////////////////////
} 
