#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeConfigXmlHandler.h"

////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////
const std::string Config_Xml_Handler::xlbe_config_element_("XlbeConfig");
const std::string Config_Xml_Handler::xlbe_root_element_("Root");
const std::string Config_Xml_Handler::xlbe_render_element_("Render");
const std::string Config_Xml_Handler::xlbe_sound_element_("Sound");
const std::string Config_Xml_Handler::xlbe_music_element_("Music");
const std::string Config_Xml_Handler::fps_attribute_("Fps");
const std::string Config_Xml_Handler::width_attribute_("Width");
const std::string Config_Xml_Handler::height_attribute_("Height");
const std::string Config_Xml_Handler::geometry_width_attribute_("GeometryWidth");
const std::string Config_Xml_Handler::geometry_height_attribute_("GeometryHeight");
const std::string Config_Xml_Handler::deactivated_attribute_("Deactivated");
const std::string Config_Xml_Handler::hidemouse_attribute_("Hidemouse");
const std::string Config_Xml_Handler::zbuffer_attribute_("Zbuffer");
const std::string Config_Xml_Handler::texturefilter_attribute_("TextureFilter");
const std::string Config_Xml_Handler::caption_attribute_("Caption");
const std::string Config_Xml_Handler::value_attribute_("Value");
const std::string Config_Xml_Handler::enable_attribute_("Enable");

////////////////////////////////////////////////////////////////////////////////////////////
Config_Xml_Handler::Config_Xml_Handler()
{
}

Config_Xml_Handler::~Config_Xml_Handler()
{
}

void Config_Xml_Handler::element_start(const std::string& element, const Xml_Attributes& attributes)
{
	if (element == xlbe_config_element_)
	{
	}
	else if (element == xlbe_root_element_)
	{
		handle_root_element(attributes);
	}
	else if (element == xlbe_render_element_)
	{
		handle_render_element(attributes);
	}
	else if (element == xlbe_sound_element_)
	{
		handle_sound_element(attributes);
	}
	else if (element == xlbe_music_element_)
	{
		handle_music_element(attributes);
	}
	else
	{
		throw_xml_error(element + " is element is not define in xlbe config.");
	}

}

void Config_Xml_Handler::element_end(const std::string& element)
{
}

void Config_Xml_Handler::text(const std::string& text)
{
}

void Config_Xml_Handler::handle_root_element(const Xml_Attributes& attributes)
{
	Root::singleton()->set_config_options(fps_attribute_, attributes.get_value_as_string(fps_attribute_, "30"));
}

void Config_Xml_Handler::handle_render_element(const Xml_Attributes& attributes)
{
    Render_System *render = Root::singleton()->render_system();

	render->set_config_options(width_attribute_, attributes.get_value_as_string(width_attribute_, "800"));
	render->set_config_options(height_attribute_, attributes.get_value_as_string(height_attribute_, "600"));
	render->set_config_options(geometry_width_attribute_, attributes.get_value_as_string(geometry_width_attribute_, "800"));
	render->set_config_options(geometry_height_attribute_, attributes.get_value_as_string(geometry_height_attribute_, "600"));
	render->set_config_options(deactivated_attribute_, attributes.get_value_as_string(deactivated_attribute_, "false"));
	render->set_config_options(hidemouse_attribute_, attributes.get_value_as_string(hidemouse_attribute_, "false"));
	render->set_config_options(zbuffer_attribute_, attributes.get_value_as_string(zbuffer_attribute_, "true"));
	render->set_config_options(texturefilter_attribute_, attributes.get_value_as_string(texturefilter_attribute_, "true"));
	render->set_config_options(caption_attribute_, attributes.get_value_as_string(caption_attribute_, "{0,0,0,30"));
}

void Config_Xml_Handler::handle_sound_element(const Xml_Attributes& attributes)
{
	//Sound_System *sound = Root::singleton()->sound_system();

	//sound->set_config_options(value_attribute_, attributes.get_value_as_string(value_attribute_, "1.0"));
	//sound->set_config_options(enable_attribute_, attributes.get_value_as_string(enable_attribute_, "true"));
	
}

void Config_Xml_Handler::handle_music_element(const Xml_Attributes& attributes)
{
	//Music_System *music = Root::singleton()->music_system();

	//music->set_config_options(value_attribute_, attributes.get_value_as_string(value_attribute_, "1.0"));
	//music->set_config_options(enable_attribute_, attributes.get_value_as_string(enable_attribute_, "true"));
}

////////////////////////////////////////////////////////////////////////////////////////////
}
