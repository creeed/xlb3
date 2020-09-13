// xlbe - 2D硬件加速引擎
// 版权所有 (C) 2011-2012, 徐林炳
// 联系方式: 徐林炳 <creednew2000@163.com>

#ifndef __XLBE_SOUND_XML_HANDLER_H__
#define __XLBE_SOUND_XML_HANDLER_H__

////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeXmlHandler.h"

////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Sound_Xml_Handler : public Xml_Handler
{
public:
	Sound_Xml_Handler(const std::string& filename, std::vector<Resource*> *resources);
	virtual ~Sound_Xml_Handler();

	virtual void element_start(const std::string& element, const Xml_Attributes& attributes);
	virtual void element_end(const std::string& element);

private:
    void element_sound_start(const Xml_Attributes& attributes);
    void element_sound_end();

    void element_music_start(const Xml_Attributes& attributes);
    void element_music_end();

    static const std::string sound_element_;
    static const std::string sound_name_attribute;
    static const std::string sound_file_attribute;

    static const std::string music_element_;
    static const std::string music_name_attribute;
    static const std::string music_file_attribute;

private:
	std::string script_filename_;
    std::vector<Resource*> *resources_;
};

////////////////////////////////////////////////////////////////////////////////////////////
}

#endif