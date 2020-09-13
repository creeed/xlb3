// xlbe - 2D硬件加速引擎
// 版权所有 (C) 2011-2012, 徐林炳
// 联系方式: 徐林炳 <creednew2000@163.com>

#ifndef __XLBE_FMOD_SOUND_MANAGER_H__
#define __XLBE_FMOD_SOUND_MANAGER_H__

////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeXmlHandler.h"
#include "XlbeSoundManager.h"
#include "XlbeFmodSound.h"
#include "XlbeFmodSoundResource.h"

////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Fmod_Sound_Manager : public Sound_Manager
{
public:
	Fmod_Sound_Manager() ;
	virtual ~Fmod_Sound_Manager() ;

public:
	virtual bool load_script(const std::string &xml_file, std::vector<Resource*> *resources);
	virtual Resource *create_resource(const std::string &name, int type);

	virtual Sound* sound_instance(const std::string &name) ;
	virtual void stop_all_sound();

	virtual float get_master_volume() { return master_volume_; }
	virtual void set_master_volume(float volume) ;

	
    void release_channels();

protected:
    int find_free_channel();
    void release_free_channels();

protected:
    float master_volume_;

    static const int MAX_CHANNELS = 32;
    Sound* playing_sounds_[MAX_CHANNELS];	

	uint32_t last_release_tick_;
};

////////////////////////////////////////////////////////////////////////////////////////////////

}
#endif