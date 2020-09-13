#ifndef __XLBE_SOUND_H__
#define __XLBE_SOUND_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

//////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////
class Sound
{
public:
    virtual ~Sound() {}

    virtual bool is_released() = 0;
    virtual void stop() = 0;
    virtual void release() = 0;

    virtual void play(bool looping, bool auto_release) = 0;	
    virtual bool is_playing() = 0;

    virtual float get_volume() const = 0;
    virtual void set_volume(float volume) = 0;

	virtual float get_master_volume() const = 0;	
    virtual void set_master_volume(float volume) = 0;
};

//////////////////////////////////////////////////////////////////////////////////////////////
}

#endif