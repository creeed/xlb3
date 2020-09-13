#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeSpriteResource.h"
#include "XlbeSpriteXmlHandler.h"
#include "XlbeSpriteResourceManager.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

template<> Sprite_Resource_Manager* Singleton<Sprite_Resource_Manager>::singleton_ = 0;
Sprite_Resource_Manager* Sprite_Resource_Manager::singleton()
{
    return singleton_;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
Sprite_Resource_Manager::Sprite_Resource_Manager()
{
    resource_type_ = "sprite_resource";
    file_pattern_ = "*.sprite";
}

Sprite_Resource_Manager::~Sprite_Resource_Manager()
{
}

bool Sprite_Resource_Manager::load_script(const std::string &xml_file, std::vector<Resource*> *resources)
{
	Sprite_Xml_Handler handler(xml_file, resources);

	return true;
}

Resource *Sprite_Resource_Manager::create_resource(const std::string &name, int type)
{
	Sprite_Resource *spr_res  = (Sprite_Resource *)get_resource(name);
	if (spr_res == 0)
	    spr_res =  new Sprite_Resource(name);
	else
		throw_resource_error(name + ": sprite resource is created.");

	resources_[name] = spr_res;

	return spr_res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
}