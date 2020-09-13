#ifndef __XLBE_CONFIG_XML_HANDLER_H__
#define __XLBE_CONFIG_XML_HANDLER_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"

////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Config_Xml_Handler : public Xml_Handler
{
public:
	Config_Xml_Handler();
	virtual ~Config_Xml_Handler();

	virtual void element_start(const std::string& element, const Xml_Attributes& attributes);
	virtual void element_end(const std::string& element);

	virtual void text(const std::string& text);

private:
	void handle_root_element(const Xml_Attributes& attributes);
	void handle_render_element(const Xml_Attributes& attributes);
	void handle_sound_element(const Xml_Attributes& attributes);
	void handle_music_element(const Xml_Attributes& attributes);

public:
	static const std::string xlbe_config_element_;
	static const std::string xlbe_root_element_;
	static const std::string xlbe_render_element_;
	static const std::string xlbe_sound_element_;
	static const std::string xlbe_music_element_;
	static const std::string Config_Xml_Handler::fps_attribute_;
	static const std::string Config_Xml_Handler::width_attribute_;
	static const std::string Config_Xml_Handler::height_attribute_;
	static const std::string Config_Xml_Handler::geometry_width_attribute_;
	static const std::string Config_Xml_Handler::geometry_height_attribute_;
	static const std::string Config_Xml_Handler::deactivated_attribute_;
	static const std::string Config_Xml_Handler::hidemouse_attribute_;
	static const std::string Config_Xml_Handler::zbuffer_attribute_;
	static const std::string Config_Xml_Handler::texturefilter_attribute_;
	static const std::string Config_Xml_Handler::caption_attribute_;
	static const std::string Config_Xml_Handler::value_attribute_;
	static const std::string Config_Xml_Handler::enable_attribute_;

};

////////////////////////////////////////////////////////////////////////////////////////////
}

#endif