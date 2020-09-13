// xlbe - 2D硬件加速引擎
// 版权所有 (C) 2011-2012, 徐林炳
// 联系方式: 徐林炳 <creednew2000@163.com>

#ifndef __XLBE_DSOUND_MANAGER_H__
#define __XLBE_DSOUND_MANAGER_H__

////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeXmlHandler.h"
#include "XlbeSoundManager.h"
#include "XlbeDsound.h"
#include "XlbeDsoundInstance.h"
#include "XlbeDsoundVersion.h"

////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export DSound_Manager : public Sound_Manager
{
public:
	DSound_Manager() ;
	virtual ~DSound_Manager() ;

public:
	virtual Config_Option_Map &config_options() { return options_; }
    virtual void set_config_options(const std::string &name, const std::string &value) ;

    virtual Sound_Instance*	sound_instance(const std::string &name) ;
    //virtual void stop_all_sound();
    virtual void release_channels() ;

    virtual double get_volume() const { return volume_; }
    virtual void set_volume(double volume) ;

    virtual double get_pan() const { return pan_; }
    virtual void set_pan(int pan) { pan_ = pan; }

    virtual double get_master_volume() ;
    virtual void set_master_volume(double volume) ;

    int volume_to_db(double volume);
    LPDIRECTSOUND get_direct_sound() const { return direct_sound_; }

protected:
    int find_free_channel();
    void release_free_channels();

    virtual Resource *create_resource_impl(const std::string &xml_file, const std::string &resource_group) ;

protected:
	Config_Option_Map options_;

    double volume_;
    int pan_;

    uint32_t last_release_tick_;

    bool initialised_;
    HMODULE dsound_dll_;
    LPDIRECTSOUND direct_sound_;

    static const int MAX_CHANNELS = 32;
    DSound_Instance* playing_sounds_[MAX_CHANNELS];	

    
};

////////////////////////////////////////////////////////////////////////////////////////////////

}
#endif