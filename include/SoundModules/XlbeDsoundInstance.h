// xlbe - 2D硬件加速引擎
// 版权所有 (C) 2011-2012, 徐林炳
// 联系方式: 徐林炳 <creednew2000@163.com>

#ifndef __XLBE_DSOUND_INSTANCE_H__
#define __XLBE_DSOUND_INSTANCE_H__

///////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeSoundInstance.h"
#include "XlbeDsoundVersion.h"

///////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

class DSound;
class DSound_Manager;

///////////////////////////////////////////////////////////////////////////////////////////////
class DSound_Instance : public Sound_Instance
{
public:
    DSound_Instance(DSound_Manager* manager, DSound *source_sound);
    virtual ~DSound_Instance();

public:
	virtual bool is_initialised() { return initialised_; }

    virtual bool is_released() ;
    virtual void stop() ;
    virtual void release() ;

    virtual void play(bool looping, bool auto_release) ;	
    virtual bool is_playing() ;

    virtual double get_volume() const { return volume_; }
    virtual void set_volume(double volume) ; 

    virtual int get_pan() const { return pan_; }
    virtual void set_pan(int pan) ; 

    void rehup_volume();
    void rehup_pan();

    DSound *get_sound() const { return sound_; }

protected:
    bool played_;
    bool released_;
    bool auto_release_;
	bool initialised_;
    
    int pan_;
    double volume_;	
    DWORD default_frequency_;

    DSound *sound_;
    DSound_Manager* sound_manager_;
    LPDIRECTSOUNDBUFFER sound_buffer_;
};

///////////////////////////////////////////////////////////////////////////////////////////////

}
#endif