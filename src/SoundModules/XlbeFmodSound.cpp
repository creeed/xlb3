#include "XlbeException.h"
#include "XlbeFmodSound.h"
#include "XlbeFmodSoundResource.h"
#include "XlbeFmodSoundManager.h"

#include "fmod/fmod.h"
#pragma comment(lib, "fmodvC.lib")

////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////////////////////
Fmod_Sound::Fmod_Sound(int channel, Fmod_Sound_Resource *sound_res)
:auto_release_(false),
played_(false),
released_(false),
volume_(1.0),
master_volume_(1.0f),
channel_(-1),
sound_res_(sound_res)
{
}

Fmod_Sound::~Fmod_Sound()
{
}

bool Fmod_Sound::is_released() 
{
	if ((!released_) && (auto_release_) && (played_) && (!is_playing()))	
		release();	

	return released_;
}

void Fmod_Sound::stop() 
{
	if (channel_ != -1)
	{
		FSOUND_StopSound(channel_);	
		channel_ = -1;
	}

	auto_release_ = false;
}

void Fmod_Sound::release() 
{
    stop();
    released_ = true;	
}

bool Fmod_Sound::is_playing() 
{
    if (!played_)
        return false;

	return FSOUND_IsPlaying(channel_);
}

void Fmod_Sound::play(bool looping, bool auto_release)
{
    stop();

	if (sound_res_ == 0)
		return ;

    played_ = true;	
    auto_release_ = auto_release;	

	channel_ = FSOUND_PlaySound (FSOUND_FREE, sound_res_->get_sample());
	if (channel_ == -1)
	{
		released_ = true;
		return;
	}

    FSOUND_SetVolume(channel_, (int) (master_volume_ * volume_ * 255));

    if (looping)
    {
        FSOUND_SetLoopMode(channel_, looping ? FSOUND_LOOP_NORMAL: FSOUND_LOOP_OFF );
    }
}

void Fmod_Sound::set_volume(float volume)
{
    volume_ = volume;

	if (channel_ != -1)
	{
		FSOUND_SetVolume(channel_, (int) (master_volume_ * volume_ * 255));
	}
}

void Fmod_Sound::set_master_volume(float volume)
{
	master_volume_ = volume;

    if (channel_ != -1)
    {
        FSOUND_SetVolume(channel_, (int) (master_volume_ * volume_ * 255));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
}

