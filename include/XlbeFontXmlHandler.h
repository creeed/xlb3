#ifndef __XLBE_FONT_XML_HANDLER_H__
#define __XLBE_FONT_XML_HANDLER_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeXmlHandler.h"

////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

class Font;

////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Font_Xml_Handler : public Xml_Handler
{
public:
	Font_Xml_Handler(const std::string& filename, std::vector<Resource*> *resources);
	virtual ~Font_Xml_Handler();

	virtual void element_start(const std::string& element, const Xml_Attributes& attributes);
	virtual void element_end(const std::string& element);

private:
    void element_font_start(const Xml_Attributes& attributes);
    void element_font_end();
    void element_letter_start(const Xml_Attributes& attributes);
    void element_letter_end();

    static const std::string font_element_;
    static const std::string font_name_attribute;
    static const std::string font_type_attribute;
    static const std::string font_width_attribute;
    static const std::string font_height_attribute;
    static const std::string font_filename_attribute;

    static const std::string letter_element_;
    static const std::string letter_id_attribute;
    static const std::string letter_imagerect_attribute;

    std::string type_;
	std::string script_filename_;
    std::vector<Resource*> *resources_;

	Font *font_;
};

////////////////////////////////////////////////////////////////////////////////////////////
}

#endif