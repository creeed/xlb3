#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeFmodMusic.h"
#include "XlbeFmodMusicManager.h"
#include "XlbeSoundXmlHandler.h"

#include "fmod/Fmod.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

///////////////////////////////////////////////////////////////////////////////////////////////////////
Fmod_Music_Manager::Fmod_Music_Manager()
{
    resource_type_ = "music";
    file_pattern_ = "*.music";

    master_volume_ = 1.0;

    FSOUND_Init (44100, 32, 0);
}

Fmod_Music_Manager::~Fmod_Music_Manager()
{
	FSOUND_Close ();
}

bool Fmod_Music_Manager::load_script(const std::string &xml_file, std::vector<Resource*> *resources)
{
	Sound_Xml_Handler handler(xml_file, resources);
	return true;
}

Resource *Fmod_Music_Manager::create_resource(const std::string &name, int type)
{
	Fmod_Music *music_res  = (Fmod_Music *)get_resource(name);
	if (music_res == 0)
	    music_res =  new Fmod_Music(name);
	else
		throw_sound_error(name + ": music resource is created.");

	music_res->set_master_volume(master_volume_);
	resources_[name] = music_res;

	return music_res;
}

void Fmod_Music_Manager::stop_all_music()
{
	Resources::iterator iend = resources_.end();
	for (Resources::iterator i = resources_.begin(); i != iend; ++i)
	{
		Fmod_Music *fmusic = (Fmod_Music *)i->second;
		if (fmusic->is_loaded())
		{
			fmusic->stop_music();
		}
	}
}

float Fmod_Music_Manager::get_master_volume() const
{
    return master_volume_;
}

void Fmod_Music_Manager::set_master_volume(float volume)
{
    master_volume_ = volume;

	Resources::iterator iend = resources_.end();
	for (Resources::iterator i = resources_.begin(); i != iend; ++i)
	{
		Fmod_Music *fmusic = (Fmod_Music *)i->second;
		if (fmusic->is_loaded())
		{
			fmusic->set_master_volume(master_volume_);
		}
	}
}

void Fmod_Music_Manager::update()
{
	Resources::iterator iend = resources_.end();
	for (Resources::iterator i = resources_.begin(); i != iend; ++i)
	{
		Fmod_Music *fmusic = (Fmod_Music *)i->second;
		if (fmusic->is_loaded())
		{
			fmusic->update();
		}
	}
    
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
}