// xlbe - 2D硬件加速引擎
// 版权所有 (C) 2011-2012, 徐林炳
// 联系方式: 徐林炳 <creednew2000@163.com>

#ifndef __XLBE_FMOD_MUSIC_XML_HANDLER_H__
#define __XLBE_FMOD_MUSIC_XML_HANDLER_H__

////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeXmlHandler.h"

////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

class Fmod_Music;
class Fmod_Music_Manager;

////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Fmod_Music_Xml_Handler : public Xml_Handler
{
public:
	Fmod_Music_Xml_Handler(const std::string& filename, const std::string& resource_group, Fmod_Music_Manager *mgr);
	virtual ~Fmod_Music_Xml_Handler();

	const std::string& get_object_name() const;
    Fmod_Music& get_object() const;

	virtual void element_start(const std::string& element, const Xml_Attributes& attributes);
	virtual void element_end(const std::string& element);

private:
    void element_music_start(const Xml_Attributes& attributes);
    void element_music_end();

    static const std::string music_element_;
    static const std::string music_name_attribute;
    static const std::string music_musicfile_attribute;

    Fmod_Music* music_;
    Fmod_Music_Manager *music_manager_;
	std::string resource_group_;
};

////////////////////////////////////////////////////////////////////////////////////////////
}

#endif