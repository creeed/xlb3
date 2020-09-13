#ifndef __XLBE_RESOURCE_MANAGER_H__
#define __XLBE_RESOURCE_MANAGER_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeResource.h"

////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Resource_Manager
{
public:
    typedef std::map< std::string, Resource*, xlbe_utility::fast_less_compare> Resources;
 
public:
    Resource_Manager();
    virtual ~Resource_Manager();

public:
    virtual bool load_script(const std::string &xml_file, std::vector<Resource*> *resources) = 0;

	int number_resource();
	bool is_all_loaded_resource();	
	void load_all_resource() ;
    void unload_all_resource() ;
    void destroy_all_resource();

    virtual Resource *create_resource(const std::string &name, int type) = 0;
	void load_resource(const std::string &name) ; //频繁调用效率问题， 使用Resource 的load
	void unload_resource(const std::string &name) ; //频繁调用效率问题， 使用Resource 的unload
	void destroy_resource(const std::string &name); 
    Resource *get_resource(const std::string &name); 	
	
protected:
    std::string resource_type_;
    std::string file_pattern_;

    Resources resources_;
};

////////////////////////////////////////////////////////////////////////////////////////////////
} 

#endif	