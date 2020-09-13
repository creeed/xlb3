#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeFmodSound.h"
#include "XlbeSoundXmlHandler.h"
#include "XlbeFmodSoundManager.h"

#include "fmod/fmod.h"
#pragma comment(lib, "fmodvC.lib")

///////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

#define MAX_SOUND_CHANNEL 64

///////////////////////////////////////////////////////////////////////////////////////////////////////
Fmod_Sound_Manager::Fmod_Sound_Manager()
{
    resource_type_ = "sound";
    file_pattern_ = "*.sound";

	FSOUND_Init (44100, 32, 0);

	master_volume_ = 1.0f;
	last_release_tick_ = 0;

	for (int i = 0; i < MAX_CHANNELS; i++)
    {
        playing_sounds_[i] = 0;
    }
}

Fmod_Sound_Manager::~Fmod_Sound_Manager()
{
	release_channels();
	FSOUND_Close ();
}

bool Fmod_Sound_Manager::load_script(const std::string &xml_file, std::vector<Resource*> *resources)
{
	Sound_Xml_Handler handler(xml_file, resources);
	return true;
}

Resource *Fmod_Sound_Manager::create_resource(const std::string &name, int type)
{
	Fmod_Sound_Resource *sound_res  = (Fmod_Sound_Resource *)get_resource(name);
	if (sound_res == 0)
	    sound_res =  new Fmod_Sound_Resource(name);
	else
		throw_sound_error(name + ": sound resource is created.");

	resources_[name] = sound_res;

	return sound_res;
}

Sound* Fmod_Sound_Manager::sound_instance(const std::string &name)
{      
    int channel = find_free_channel();

    if (channel >= MAX_CHANNELS)
		return 0;

	Fmod_Sound_Resource *sound_res = static_cast<Fmod_Sound_Resource*>(get_resource(name));
	if (sound_res == 0)
		return 0;

	Fmod_Sound* sound = new Fmod_Sound(channel, sound_res);
	sound->set_master_volume(master_volume_);
    playing_sounds_[channel] = sound;

    return playing_sounds_[channel];
}

void Fmod_Sound_Manager::stop_all_sound()
{
    for (int i = 0; i < MAX_CHANNELS; i++)
    {
        if (playing_sounds_[i] != 0 && !playing_sounds_[i]->is_released())
        {
            playing_sounds_[i]->stop();
        }
    }
}

void Fmod_Sound_Manager::release_channels()
{
    for (int i = 0; i < MAX_CHANNELS; i++)
    {
        if (playing_sounds_[i] != 0)
        {
            delete playing_sounds_[i];
            playing_sounds_[i] = 0;
        }
    }
}

int Fmod_Sound_Manager::find_free_channel()
{
    DWORD tick = GetTickCount();
    if (tick - last_release_tick_ > 1000)
    {
        release_free_channels();
        last_release_tick_ = tick;
    }

    for (int i = 0; i < MAX_CHANNELS; i++)
    {		
        if (playing_sounds_[i] == 0)
            return i;

        if (playing_sounds_[i]->is_released())
        {
            delete playing_sounds_[i];
            playing_sounds_[i] = 0;

            return i;
        }
    }

    return MAX_CHANNELS;
}

void Fmod_Sound_Manager::release_free_channels()
{
    for (int i = 0; i < MAX_CHANNELS; i++)
    {
        if (playing_sounds_[i] != 0 && playing_sounds_[i]->is_released())
        {
            delete playing_sounds_[i];
            playing_sounds_[i] = 0;
        }
    }
}

void Fmod_Sound_Manager::set_master_volume(float volume) 
{ 
	master_volume_ = volume; 

    for (int i = 0; i < MAX_CHANNELS; i++)
    {
        if (playing_sounds_[i] != 0 && !playing_sounds_[i]->is_released())
        {
            playing_sounds_[i]->set_master_volume(volume);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
}