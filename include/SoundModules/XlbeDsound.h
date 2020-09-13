// xlbe - 2D硬件加速引擎
// 版权所有 (C) 2011-2012, 徐林炳
// 联系方式: 徐林炳 <creednew2000@163.com>

#ifndef __XLBE_DSOUND_H__
#define __XLBE_DSOUND_H__

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeSound.h"
#include "XlbeDsoundVersion.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

class DSound_Manager;

//////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export DSound : public Sound
{
public:
	DSound(const std::string& name, const std::string& filename, const std::string& resource_group, DSound_Manager *mgr);
    virtual ~DSound();

public:
	virtual void prepare();
	virtual void unprepare();
	virtual void load();
	virtual void unload();

public:
    virtual double get_volume() const { return volume_; }
    virtual void set_volume(double volume) { volume_ = volume; }

    virtual int get_pan() const { return pan_; }
    virtual void set_pan(int pan) { pan_ = pan; }

    LPDIRECTSOUNDBUFFER get_sound_buffer() const { return source_sound_; }

private:
    void load_sound(const std::string& file, const std::string& resource_group);

    bool load_ogg_sound(const std::string& file, const std::string& resource_group);
    bool load_fmod_sound(const std::string& file, const std::string& resource_group);
    bool load_wav_sound(const std::string& file, const std::string& resource_group);
    bool load_av_sound(const std::string& file, const std::string& resource_group);

private:
    double volume_;
    int pan_;

    std::string filename_;
    std::string resource_group_;
    DSound_Manager *sound_manager_;
    LPDIRECTSOUNDBUFFER source_sound_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif