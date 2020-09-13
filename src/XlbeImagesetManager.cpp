#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeImageset.h"
#include "XlbeImagesetXmlHandler.h"
#include "XlbeImagesetManager.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

template<> Imageset_Manager* Singleton<Imageset_Manager>::singleton_ = 0;
Imageset_Manager* Imageset_Manager::singleton()
{
    return singleton_;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
Imageset_Manager::Imageset_Manager()
{
    resource_type_ = "imageset";
    file_pattern_ = "*.imageset";
}

Imageset_Manager::~Imageset_Manager()
{
}

Imageset* Imageset_Manager::get_imageset(const std::string& str)
{
    return static_cast<Imageset*>(get_resource(str));
}

Image* Imageset_Manager::string_to_image(const std::string& str)
{
    if (str.empty())
        return 0;

    char image_set[128];
    char image_name[128];

    sscanf(str.c_str(), " set:%127s image:%127s", image_set, image_name);

    Image* image;
    image = &(static_cast<Imageset*>(get_resource(image_set))->get_image(image_name));
   
    return image;
}

Resource *Imageset_Manager::create_resource_impl(const std::string &xml_file, const std::string &resource_group) 
{
    Imageset_Xml_Handler handler(xml_file, resource_group);

    return &handler.get_object();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
}
