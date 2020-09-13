#include "XlbeException.h"
#include "XlbeDsound.h"
#include "XlbeDsoundInstance.h"
#include "XlbeDsoundManager.h"

////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////////////////////
DSound_Instance::DSound_Instance(DSound_Manager* manager, DSound *source_sound)
:sound_(source_sound),
sound_manager_(manager),
sound_buffer_(0),
auto_release_(false),
played_(false),
released_(false),
pan_(0),
volume_(1.0),	
default_frequency_(44100)
{
    HRESULT hr;

	if (sound_manager_->get_direct_sound())
	{
        hr = sound_manager_->get_direct_sound()->DuplicateSoundBuffer(sound_->get_sound_buffer(), &sound_buffer_);
		if (hr != DS_OK)
		{
			initialised_ = false;
			sound_buffer_ = 0;
		}
		else
		{
			initialised_ = true;

			sound_buffer_->GetFrequency(&default_frequency_);

			rehup_volume();
			rehup_pan();
		}
	}
	else
	{
		initialised_ = false;
		sound_buffer_ = 0;
	}
}

DSound_Instance::~DSound_Instance()
{
    if (sound_buffer_ != 0)
        sound_buffer_->Release();
}

bool DSound_Instance::is_released() 
{
	if ((!released_) && (auto_release_) && (played_) && (!is_playing()))	
		release();	

	return released_;
}

void DSound_Instance::stop() 
{
	if (sound_buffer_ != 0)
	{
		sound_buffer_->Stop();
		sound_buffer_->SetCurrentPosition(0);

		auto_release_ = false;
	}
}

void DSound_Instance::release() 
{
    stop();
    released_ = true;	
}

bool DSound_Instance::is_playing() 
{
    if (!played_)
        return false;

    if (sound_buffer_ == 0)
        return false;

    DWORD status;

    if (sound_buffer_->GetStatus(&status) == DS_OK)
        return ((status & DSBSTATUS_PLAYING) != 0);
    else
        return false;
}

void DSound_Instance::play(bool looping, bool auto_release)
{
    stop();

    played_ = true;	
    auto_release_ = auto_release;	

    if (sound_buffer_ == 0)
    {
        throw_sound_error("sound buffer is null");
    }

    if (looping)
    {
        if (sound_buffer_->Play(0, 0, DSBPLAY_LOOPING) != DS_OK)
            throw_sound_error("sound buffer play is failure");
    }
    else
    {
        if (sound_buffer_->Play(0, 0, 0) != DS_OK)
        {
            throw_sound_error("sound buffer play is failure");
        }
    }
}

void DSound_Instance::set_volume(double volume)
{
    volume_ = volume;
    rehup_volume();	
}

void DSound_Instance::set_pan(int position)
{
    pan_ = position;
    rehup_pan();
}

void DSound_Instance::rehup_volume()
{
    if (sound_buffer_ != 0)
        sound_buffer_->SetVolume(sound_manager_->volume_to_db(sound_->get_volume() * volume_ * sound_manager_->get_volume()));
}

void DSound_Instance::rehup_pan()
{
    if (sound_buffer_ != 0)
        sound_buffer_->SetPan(sound_->get_pan() + pan_  + sound_manager_->get_pan());
}

////////////////////////////////////////////////////////////////////////////////////////////////
}

