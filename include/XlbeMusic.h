#ifndef __XLBE_MUSIC_H__
#define __XLBE_MUSIC_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeResource.h"

////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Music : public Resource 
{
public:
	Music() { resource_type_ = "muisc"; }
    virtual ~Music() {}

public:
	virtual bool play_music(int offset = 0, bool loop = false) = 0;
	virtual void stop_music() = 0;
	virtual void pause_music() = 0;
	virtual void resume_music() = 0;
	
	virtual void fade_in(int offset = -1, double speed = 0.002, bool loop = false) = 0;
	virtual void fade_out(bool stop = true, double speed = 0.004) = 0;

    virtual float get_volume() const = 0;
	virtual void set_volume(float volume) = 0;

	virtual float get_master_volume() const = 0;
    virtual void set_master_volume(float volume) = 0;

	virtual bool is_playing() = 0;
};

////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif 
