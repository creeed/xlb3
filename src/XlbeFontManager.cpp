#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeFont.h"
#include "XlbeImageFont.h"
#include "XlbeTtfFont.h"
#include "XlbeFontXmlHandler.h"
#include "XlbeFontManager.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

template<> Font_Manager* Singleton<Font_Manager>::singleton_ = 0;
Font_Manager* Font_Manager::singleton()
{
    return singleton_;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
Font_Manager::Font_Manager()
{
    resource_type_ = "font";
    file_pattern_ = "*.font";
}

Font_Manager::~Font_Manager()
{
}

bool Font_Manager::load_script(const std::string &xml_file, std::vector<Resource*> *resources)
{
	Font_Xml_Handler handler(xml_file, resources);

	return true;
}

Resource *Font_Manager::create_resource(const std::string &name, int type)
{
	Font *font  = (Font *)get_resource(name);
	if (font == 0)
	{
		if (type == 0) //Pixmap
		{
			font = new Image_Font(name);
		}
		else if (type == 1) //FreeType
		{
			font = new Ttf_Font(name);
		}
		else
			throw_resource_error(name + ": no know font type");

	}
	else
		throw_resource_error(name + ": font resource is created.");

	resources_[name] = font;

	return font;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
}
