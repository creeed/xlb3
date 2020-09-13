#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeFigure.h"
#include "XlbeFigureXmlHandler.h"
#include "XlbeFigureManager.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

template<> Figure_Manager* Singleton<Figure_Manager>::singleton_ = 0;
Figure_Manager* Figure_Manager::singleton()
{
    return singleton_;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
Figure_Manager::Figure_Manager()
{
    resource_type_ = "figure";
    file_pattern_ = "*.figure";
}

Figure_Manager::~Figure_Manager()
{
}

Figure* Figure_Manager::get_figure(const std::string& str)
{
    return static_cast<Figure*>(get_resource(str));
}

Resource *Figure_Manager::create_resource_impl(const std::string &xml_file, const std::string &resource_group) 
{
    Figure_Xml_Handler handler(xml_file, resource_group);

    return &handler.get_object();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
}