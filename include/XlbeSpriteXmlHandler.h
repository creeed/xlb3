#ifndef __XLBE_SPRITE_XML_HANDLER_H__
#define __XLBE_SPRITE_XML_HANDLER_H__

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

class Resource;

////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Sprite_Xml_Handler : public Xml_Handler
{
public:
	Sprite_Xml_Handler(const std::string& filename, std::vector<Resource*> *resources);
	virtual ~Sprite_Xml_Handler();

	virtual void element_start(const std::string& element, const Xml_Attributes& attributes);
	virtual void element_end(const std::string& element);

private:
    void element_sprite_start(const Xml_Attributes& attributes);
    void element_sprite_end();

	static const std::string sprite_element_;
	static const std::string sprite_name_attribute;
	static const std::string sprite_imagerect_attribute;
	static const std::string sprite_imagefile_attribute;
	static const std::string sprite_colorrect_attribute;
	static const std::string sprite_rotation_attribute;
	static const std::string sprite_hot_attribute;
	static const std::string sprite_blend_attribute;
	static const std::string sprite_flip_attribute;
	static const std::string sprite_srcrect_attribute;

private:
	std::string script_filename_;
    std::vector<Resource*> *resources_;
};

////////////////////////////////////////////////////////////////////////////////////////////
}

#endif