#ifndef __XLBE_ANIMATION_H__
#define __XLBE_ANIMATION_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeAnimationKeyFrame.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Animation 
{
public:
    typedef std::vector<Animation_Keyframe *> Keyframes;

public:
    Animation(const std::string& name, float duration, int count);
    virtual ~Animation();

public:
    const std::string& get_name() const { return name_; }
    void set_name(const std::string &name) { name_ = name; } 

    float get_duration() const { return duration_; }
    void set_duration(float duration) { duration_ = duration; }

	int number_of_keyframe() const { return keyframes_.size(); }
	Animation_Keyframe *get_keyframe(int index) const { return  keyframes_.at(index); }
    void insert_keyframe(Animation_Keyframe *keyframe, int index = -1);
    void remove_keyframe(int index);
    void remove_all_keyframe();

private:
    std::string name_;
	float duration_;
	Keyframes keyframes_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif