// xlbe - 2D硬件加速引擎
// 版权所有 (C) 2011-2012, 徐林炳
// 联系方式: 徐林炳 <creednew2000@163.com>

#ifndef __XLBE_FOMD_SOUND_H__
#define __XLBE_FOMD_SOUND_H__

///////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeSound.h"

struct FMUSIC_MODULE;
struct FSOUND_SAMPLE;
struct FSOUND_STREAM;

///////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

class Fmod_Sound_Resource;
class Fmod_Sound_Manager;

///////////////////////////////////////////////////////////////////////////////////////////////
class Fmod_Sound : public Sound
{
public:
    Fmod_Sound(int channel, Fmod_Sound_Resource *sound_res);
    virtual ~Fmod_Sound();

public:
	virtual void stop() ;
    virtual bool is_released() ;
    virtual void release() ;

    virtual void play(bool looping, bool auto_release) ;	
    virtual bool is_playing() ;

    virtual float get_volume() const { return volume_; }
    virtual void set_volume(float volume) ; 

	virtual float get_master_volume() const { return master_volume_; }	
    virtual void set_master_volume(float volume);

protected:
    bool played_;
    bool released_;
    bool auto_release_;

    float volume_;	
	float master_volume_;
	int channel_;
	Fmod_Sound_Resource *sound_res_;
};

///////////////////////////////////////////////////////////////////////////////////////////////

}
#endif