#ifndef __XLBE_RESOURCE_GROUP_MANAGER_H__
#define __XLBE_RESOURCE_GROUP_MANAGER_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeResourceManager.h"

////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Resource_Group_Manager : public Singleton<Resource_Group_Manager>
{
public:
    typedef std::map<std::string, Resource_Manager*, xlbe_utility::fast_less_compare> Resource_Manager_Map;

public:
    Resource_Group_Manager();
    ~Resource_Group_Manager();

    static Resource_Group_Manager* singleton();

public:
    void register_resource_manager(const std::string& resource_type, Resource_Manager* rm);
    void unregister_resource_manager(const std::string& resource_type);

    void declare_resource_group(const std::string &resource_group, const std::string &resource_directory);
    void undeclare_resource_group(const std::string &resource_group);

    void initialise_resource_group(const std::string &resource_group);
    void destroy_resource_group(const std::string &resource_group);

    void load_resource_group(const std::string &resource_group);
    void unload_resource_group(const std::string &resource_group);

    void start_load_resources(const std::string &group);
    bool load_next_resource();

    bool is_declared_resource_group(const std::string &resource_group);
    bool is_initialise_resource_group(const std::string &resource_group);
    bool is_loaded_resource_group(const std::string &resource_group);

    int number_resource(const std::string &resource_group);

private:
    std::string cur_resource_group_;

    Resource_Manager_Map resource_manager_map_;
    Resource_Manager_Map::iterator cur_resource_manager_;
};

////////////////////////////////////////////////////////////////////////////////////////////////
} 

#endif	


