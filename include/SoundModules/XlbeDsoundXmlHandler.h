// xlbe - 2D硬件加速引擎
// 版权所有 (C) 2011-2012, 徐林炳
// 联系方式: 徐林炳 <creednew2000@163.com>

#ifndef __XLBE_DSOUND_XML_HANDLER_H__
#define __XLBE_DSOUND_XML_HANDLER_H__

////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeXmlHandler.h"

////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

class DSound;
class DSound_Manager;

////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export DSound_Xml_Handler : public Xml_Handler
{
public:
	DSound_Xml_Handler(const std::string& filename, const std::string& resource_group, DSound_Manager *mgr);
	virtual ~DSound_Xml_Handler();

	const std::string& get_object_name() const;
    DSound& get_object() const;

	virtual void element_start(const std::string& element, const Xml_Attributes& attributes);
	virtual void element_end(const std::string& element);

private:
    void element_sound_start(const Xml_Attributes& attributes);
    void element_sound_end();

    static const std::string sound_element_;
    static const std::string sound_name_attribute;
    static const std::string sound_soundfile_attribute;

    DSound* sound_;
    DSound_Manager *sound_manager_;
	std::string resource_group_;
};

////////////////////////////////////////////////////////////////////////////////////////////
}

#endif