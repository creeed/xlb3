#ifndef __XLBE_IMAGESET_XML_HANDLER_H__
#define __XLBE_IMAGESET_XML_HANDLER_H__

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

class Imageset;

////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Imageset_Xml_Handler : public Xml_Handler
{
public:
	Imageset_Xml_Handler(const std::string& filename, const std::string& resource_group);
	virtual ~Imageset_Xml_Handler();

	const std::string& get_object_name() const;
    Imageset& get_object() const;

	virtual void element_start(const std::string& element, const Xml_Attributes& attributes);
	virtual void element_end(const std::string& element);

private:
    void element_imageset_start(const Xml_Attributes& attributes);
    void element_image_start(const Xml_Attributes& attributes);
    void element_imageset_end();

    static const std::string imageset_element_;
    static const std::string image_element_;
    static const std::string imageset_name_attribute;
    static const std::string imageset_imagefile_attribute;
    static const std::string imageset_nativehorzres_attribute;
    static const std::string imageset_nativevertres_attribute;
    static const std::string image_name_attribute;
    static const std::string image_xpos_attribute;
    static const std::string image_ypos_attribute;
    static const std::string image_width_attribute;
    static const std::string image_height_attribute;

    Imageset* imageset_;
	std::string resource_group_;
    mutable bool object_read_;

};

////////////////////////////////////////////////////////////////////////////////////////////
}

#endif