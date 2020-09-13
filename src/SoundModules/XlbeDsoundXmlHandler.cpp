#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeDsound.h"
#include "XlbeDsoundManager.h"
#include "XlbeDsoundXmlHandler.h"

////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////
const std::string DSound_Xml_Handler::sound_element_( "Sound" );
const std::string DSound_Xml_Handler::sound_name_attribute( "Name" );
const std::string DSound_Xml_Handler::sound_soundfile_attribute( "Soundfile" );

////////////////////////////////////////////////////////////////////////////////////////////
DSound_Xml_Handler::DSound_Xml_Handler(const std::string& filename, const std::string& resource_group, DSound_Manager *mgr)
:sound_(0),
sound_manager_(mgr),
resource_group_(resource_group)
{
    Root::singleton()->xml_parser()->parse_xml_file(*this, filename, resource_group);
}

DSound_Xml_Handler::~DSound_Xml_Handler()
{
}

void DSound_Xml_Handler::element_start(const std::string& element, const Xml_Attributes& attributes)
{
    if (element == sound_element_)
        element_sound_start(attributes);
}

void DSound_Xml_Handler::element_end(const std::string& element)
{
    if (element == sound_element_)
        element_sound_end();
}

void DSound_Xml_Handler::element_sound_start(const Xml_Attributes& attributes)
{
    const std::string name(attributes.get_value_as_string(sound_name_attribute));
    const std::string filename(attributes.get_value_as_string(sound_soundfile_attribute));

    sound_ = new DSound(name, filename, resource_group_, sound_manager_);
}

void DSound_Xml_Handler::element_sound_end()
{
}

const std::string& DSound_Xml_Handler::get_object_name() const
{
    return sound_->get_name();
}

DSound& DSound_Xml_Handler::get_object() const
{
    return *sound_;
}

////////////////////////////////////////////////////////////////////////////////////////////
}