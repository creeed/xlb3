#ifndef __XLBE_SOUND_INSTANCE_H__
#define __XLBE_SOUND_INSTANCE_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

//////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////
class Sound_Instance
{
public:
    virtual ~Sound_Instance() {}

    virtual bool is_released() = 0;
    virtual void stop() = 0;
    virtual void release() = 0;

    virtual void play(bool looping, bool auto_release) = 0;	
    virtual bool is_playing() = 0;

    virtual double get_volume() const = 0;
    virtual void set_volume(double volume) = 0;

    virtual int get_pan() const = 0;
    virtual void set_pan(int pan) = 0; 
};

//////////////////////////////////////////////////////////////////////////////////////////////
}
#endif