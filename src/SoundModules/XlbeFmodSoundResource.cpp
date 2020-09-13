#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeFmodSoundResource.h"
#include "XlbeFmodSoundManager.h"

#include "fmod/fmod.h"
#pragma comment(lib, "fmodvC.lib")

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////////
Fmod_Sound_Resource::Fmod_Sound_Resource(const std::string& name)
{
    name_ = name;
	sample_ = 0;
    load_state_ = LOADSTATE_UNLOADED;
}

Fmod_Sound_Resource::~Fmod_Sound_Resource()
{
}

void Fmod_Sound_Resource::prepare()
{
    load_state_ = LOADSTATE_PREPARED;
}

void Fmod_Sound_Resource::unprepare()
{
    load_state_ = LOADSTATE_UNPREPARED;
}

void Fmod_Sound_Resource::load()
{
    if (!is_loaded())
    {
		Root* root = Root::singleton();

		if (!root)
			throw_sound_error("root object has not been created!");

		Raw_Data_Container data_container;
		root->resource_provider()->load_raw_data_container(sound_filename_, data_container);

		sample_ = FSOUND_Sample_Load(FSOUND_FREE, (char*)data_container.get_data_ptr(), FSOUND_LOADMEMORY, 0, data_container.get_size());

		root->resource_provider()->unload_raw_data_container(data_container);

       load_state_ = LOADSTATE_LOADED;
    }
}

void Fmod_Sound_Resource::unload()
{
    load_state_ = LOADSTATE_UNLOADED;

	if (sample_ )
	{
		FSOUND_Sample_Free (sample_);
		sample_ = 0;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
}
