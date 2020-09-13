#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeFmodMusic.h"
#include "XlbeFmodMusicManager.h"
#include "XlbeContainerFile.h"

#include "fmod/fmod.h"
#pragma comment(lib, "fmodvC.lib")

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////////
Fmod_Music::Fmod_Music(const std::string& name)
{
    name_ = name;
    size_ = 0;

    load_state_ = LOADSTATE_UNLOADED;

    stream_ = 0;
	channel_ = -1;
	volume_ = 1.0;
	master_volume_ = 1.0f;
	volume_add_ = 0.0;
	volume_cap_ = 1.0;
	stop_on_fade_ = false;
	repeats_ = false;
}

Fmod_Music::~Fmod_Music()
{
}

void Fmod_Music::prepare()
{
    load_state_ = LOADSTATE_PREPARED;
}

void Fmod_Music::unprepare()
{
    load_state_ = LOADSTATE_UNPREPARED;
}

void Fmod_Music::load()
{
    if (!is_loaded())
	{
		Root::singleton()->resource_provider()->load_raw_data_container(music_filename_, data_container_);

		stream_ = FSOUND_Stream_Open((char*)data_container_.get_data_ptr(), FSOUND_LOADMEMORY, 0, data_container_.get_size());
        load_state_ = LOADSTATE_LOADED;
    }
}

void Fmod_Music::unload()
{
    load_state_ = LOADSTATE_UNLOADED;

	if (stream_ )
	{
		FSOUND_Stream_Close(stream_);
		stream_ = 0;

		Root::singleton()->resource_provider()->unload_raw_data_container(data_container_);
	}
}

bool Fmod_Music::play_music(int offset, bool loop)
{
    //volume_ = volume_cap_;
    volume_add_ = 0.0;

    if (stream_ != NULL)
    {
        channel_ = FSOUND_Stream_Play(FSOUND_FREE, stream_);
		if (channel_ == -1)
			return false;

        FSOUND_SetVolume(channel_, (int) (master_volume_ * volume_ * 255));
        FSOUND_Stream_SetMode(stream_, loop ? FSOUND_LOOP_NORMAL: FSOUND_LOOP_OFF );

		return true;
    }

	return false;
}

void Fmod_Music::stop_music()
{
    if (channel_ != -1)
    {
        FSOUND_StopSound(channel_);		
    }
}

void Fmod_Music::pause_music()
{
    if (channel_ != -1)
    {
        FSOUND_SetPaused(channel_, true);	
    }
}

void Fmod_Music::resume_music()
{
    if (channel_ != -1)
    {
        FSOUND_SetPaused(channel_, false);		
    }
}
	
void Fmod_Music::fade_in(int offset, double speed, bool loop)
{
    volume_add_ = speed;

    if (channel_ != -1)
    {	
        FSOUND_SetVolume(channel_, (int) (master_volume_ * volume_ * 255));
        FSOUND_SetLoopMode(channel_, loop ? FSOUND_LOOP_NORMAL : FSOUND_LOOP_OFF);

        if (!FSOUND_IsPlaying(channel_))
            FSOUND_Stream_Play(channel_, stream_);

        //if (offset != -1)
        //    FSOUND_SetOrder(0, offset);

		return;
    }
}

void Fmod_Music::fade_out(bool stop, double speed)
{
    volume_add_ = -speed;
    stop_on_fade_ = stop;
}

void Fmod_Music::set_volume(float volume)
{
    volume_ = volume;

    if (channel_ != -1)
    {
        FSOUND_SetVolume(channel_, (int) (master_volume_ * volume_ * 255));
    }
}

void Fmod_Music::set_master_volume(float volume)
{
	master_volume_ = volume;

    if (channel_ != -1)
    {
        FSOUND_SetVolume(channel_, (int) (master_volume_ * volume_ * 255));
    }
}

bool Fmod_Music::is_playing()
{
    if (channel_ != -1)
    {
        return (FSOUND_IsPlaying(channel_) != 0);
    }

    return false;
}

void Fmod_Music::update()
{
    if (volume_add_ != 0.0)
    {
        volume_ += volume_add_;

        if (volume_ > volume_cap_)
        {
            volume_ = volume_cap_;
            volume_add_ = 0.0;
        }
        else if (volume_ < 0.0)
        {
            volume_ = 0.0;
            volume_add_ = 0.0;

            if (stop_on_fade_)
            {
                if (channel_ != -1)
                {
                    FSOUND_StopSound (channel_);
                }
            }
        }

        if (channel_ != -1)
        {
            FSOUND_SetVolume(channel_, (int) (master_volume_ * volume_ * 255));
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
}
