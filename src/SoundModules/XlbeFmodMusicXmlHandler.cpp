#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeFmodMusic.h"
#include "XlbeFmodMusicManager.h"
#include "XlbeFmodMusicXmlHandler.h"

////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////
const std::string Fmod_Music_Xml_Handler::music_element_( "Music" );
const std::string Fmod_Music_Xml_Handler::music_name_attribute( "Name" );
const std::string Fmod_Music_Xml_Handler::music_musicfile_attribute( "Musicfile" );

////////////////////////////////////////////////////////////////////////////////////////////
Fmod_Music_Xml_Handler::Fmod_Music_Xml_Handler(const std::string& filename, const std::string& resource_group, Fmod_Music_Manager *mgr)
:music_(0),
music_manager_(mgr),
resource_group_(resource_group)
{
    Root::singleton()->xml_parser()->parse_xml_file(*this, filename, resource_group);
}

Fmod_Music_Xml_Handler::~Fmod_Music_Xml_Handler()
{
}

void Fmod_Music_Xml_Handler::element_start(const std::string& element, const Xml_Attributes& attributes)
{
    if (element == music_element_)
        element_music_start(attributes);
}

void Fmod_Music_Xml_Handler::element_end(const std::string& element)
{
    if (element == music_element_)
        element_music_end();
}

void Fmod_Music_Xml_Handler::element_music_start(const Xml_Attributes& attributes)
{
    const std::string name(attributes.get_value_as_string(music_name_attribute));
    const std::string filename(attributes.get_value_as_string(music_musicfile_attribute));

    static int channel = 0;

    music_ = new Fmod_Music(name, filename, resource_group_, channel, music_manager_);

	channel ++;
}

void Fmod_Music_Xml_Handler::element_music_end()
{
}

const std::string& Fmod_Music_Xml_Handler::get_object_name() const
{
    return music_->get_name();
}

Fmod_Music& Fmod_Music_Xml_Handler::get_object() const
{
    return *music_;
}

////////////////////////////////////////////////////////////////////////////////////////////
}