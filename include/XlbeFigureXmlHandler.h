#ifndef __XLBE_FIGURE_XML_HANDLER_H__
#define __XLBE_FIGURE_XML_HANDLER_H__

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

class Figure;
class Animation;

////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Figure_Xml_Handler : public Xml_Handler
{
public:
	Figure_Xml_Handler(const std::string& filename, const std::string& resource_group);
	virtual ~Figure_Xml_Handler();

	const std::string& get_object_name() const;
    Figure& get_object() const;

	virtual void element_start(const std::string& element, const Xml_Attributes& attributes);
	virtual void element_end(const std::string& element);

private:
    void element_figure_start(const Xml_Attributes& attributes);
    void element_plate_start(const Xml_Attributes& attributes);
    void element_animation_start(const Xml_Attributes& attributes);
    void element_keyframe_start(const Xml_Attributes& attributes);
    void element_figure_end();
    void element_plate_end();
    void element_animation_end();
    void element_keyframe_end();

    static const std::string figure_element_;
    static const std::string plate_element_;
    static const std::string animation_element_;
    static const std::string keyframe_element_;
    static const std::string figure_name_attribute;
    static const std::string figure_width_attribute;
    static const std::string figure_height_attribute;
    static const std::string plate_name_attribute;
    static const std::string plate_value_attribute;
    static const std::string animation_name_attribute;
    static const std::string animation_duration_attribute;
    static const std::string animation_count_attribute;
    static const std::string keyframe_value_attribute;
    static const std::string keyframe_time_attribute;

    Figure* figure_;
    Animation *animation_;
	std::string resource_group_;
};

////////////////////////////////////////////////////////////////////////////////////////////
}

#endif