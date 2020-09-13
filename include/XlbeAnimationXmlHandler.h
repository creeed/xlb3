#ifndef __XLBE_ANIMATION_XML_HANDLER_H__
#define __XLBE_ANIMATION_XML_HANDLER_H__

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
class Animation_Resource;

////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Animation_Xml_Handler : public Xml_Handler
{
public:
	Animation_Xml_Handler(const std::string& filename, std::vector<Resource*> *resources);
	virtual ~Animation_Xml_Handler();

	virtual void element_start(const std::string& element, const Xml_Attributes& attributes);
	virtual void element_end(const std::string& element);

private:
    void element_animation_start(const Xml_Attributes& attributes);
    void element_keyframe_start(const Xml_Attributes& attributes);
    void element_animation_end();
    void element_keyframe_end();

	static const std::string animation_element_;
	static const std::string animation_name_attribute;
	static const std::string animation_duration_attribute;
	static const std::string keyframe_element_;
	static const std::string keyframe_value_attribute;
	static const std::string keyframe_time_attribute;

private:
	Animation_Resource *animation_;
    std::vector<Resource*> *resources_;
};

////////////////////////////////////////////////////////////////////////////////////////////
}

#endif