#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeFmodSoundResource.h"
#include "XlbeFmodSoundManager.h"
#include "XlbeFmodMusic.h"
#include "XlbeFmodMusicManager.h"
#include "XlbeSoundXmlHandler.h"

////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////
const std::string Sound_Xml_Handler::sound_element_( "Sound" );
const std::string Sound_Xml_Handler::sound_name_attribute( "Name" );
const std::string Sound_Xml_Handler::sound_file_attribute( "Soundfile" );

const std::string Sound_Xml_Handler::music_element_( "Music" );
const std::string Sound_Xml_Handler::music_name_attribute( "Name" );
const std::string Sound_Xml_Handler::music_file_attribute( "Musicfile" );

////////////////////////////////////////////////////////////////////////////////////////////
Sound_Xml_Handler::Sound_Xml_Handler(const std::string& filename, std::vector<Resource*> *resources)
{
	resources_ = resources;
	script_filename_ = filename;
    Root::singleton()->xml_parser()->parse_xml_file(*this, filename);
}

Sound_Xml_Handler::~Sound_Xml_Handler()
{
}

void Sound_Xml_Handler::element_start(const std::string& element, const Xml_Attributes& attributes)
{
    if (element == sound_element_)
        element_sound_start(attributes);

	else if (element == music_element_)
        element_music_start(attributes);
}

void Sound_Xml_Handler::element_end(const std::string& element)
{
    if (element == sound_element_)
        element_sound_end();

	else if (element == music_element_)
        element_music_end();
}

void Sound_Xml_Handler::element_sound_start(const Xml_Attributes& attributes)
{
    const std::string name(attributes.get_value_as_string(sound_name_attribute));
    const std::string filename(attributes.get_value_as_string(sound_file_attribute));

	Fmod_Sound_Resource *sound_res = (Fmod_Sound_Resource *)Root::singleton()->sound_manager()->create_resource(name, 0);

	if (!filename.empty())
	{
		char dir[_MAX_DIR];
		std::string sound_filename;

		_splitpath( script_filename_.c_str(), 0, dir, 0, 0 );
	    sound_filename = dir + filename;

		sound_res->set_sound_filename(sound_filename) ;
	}

	sound_res->prepare();
	if (resources_)
	    resources_->push_back(sound_res);
}

void Sound_Xml_Handler::element_sound_end()
{
}

void Sound_Xml_Handler::element_music_start(const Xml_Attributes& attributes)
{
    const std::string name(attributes.get_value_as_string(music_name_attribute));
    const std::string filename(attributes.get_value_as_string(music_file_attribute));

	Fmod_Music *music_res = (Fmod_Music *)Root::singleton()->music_manager()->create_resource(name, 0);

	if (!filename.empty())
	{
		char dir[_MAX_DIR];
		std::string music_filename;

	    _splitpath( script_filename_.c_str(), 0, dir, 0, 0 );
	    music_filename = dir + filename;

		music_res->set_music_filename(music_filename) ;
	}

	music_res->prepare();
	if (resources_)
	    resources_->push_back(music_res);
}

void Sound_Xml_Handler::element_music_end()
{
}

////////////////////////////////////////////////////////////////////////////////////////////
}