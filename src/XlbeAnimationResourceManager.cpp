#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeAnimationResource.h"
#include "XlbeAnimationXmlHandler.h"
#include "XlbeAnimationResourceManager.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

template<> Animation_Resource_Manager* Singleton<Animation_Resource_Manager>::singleton_ = 0;
Animation_Resource_Manager* Animation_Resource_Manager::singleton()
{
    return singleton_;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
Animation_Resource_Manager::Animation_Resource_Manager()
{
    resource_type_ = "animation_resource";
    file_pattern_ = "*.sprite";
}

Animation_Resource_Manager::~Animation_Resource_Manager()
{
}

bool Animation_Resource_Manager::load_script(const std::string &xml_file, std::vector<Resource*> *resources)
{
	Animation_Xml_Handler handler(xml_file, resources);

	return true;
}

Resource *Animation_Resource_Manager::create_resource(const std::string &name, int type)
{
	Animation_Resource *ani_res  = (Animation_Resource *)get_resource(name);
	if (ani_res == 0)
	    ani_res =  new Animation_Resource(name);
	else
		throw_resource_error(name + ": animation resource is created.");

	resources_[name] = ani_res;

	return ani_res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
}