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
class Xlbe_Export Resource_Load : public Singleton<Resource_Load>
{
public:
    typedef std::map<uint32_t, Resource_Manager*> Resource_Manager_Map;

public:
    Resource_Load();
    ~Resource_Load();

    static Resource_Load* singleton();

public:
    void load_script(const std::string &xml_file, std::vector<Resource*> *resources);

	int number_resource();
	bool is_all_loaded_resource();	
	void load_all_resource() ;
    void unload_all_resource() ;
    void destroy_all_resource();

private:

};

////////////////////////////////////////////////////////////////////////////////////////////////
} 

#endif	


