#include "XlbeException.h"
#include "XlbeAnimation.h"
#include "XlbeImagesetManager.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////////////
Animation::Animation(const std::string& name, float duration, int count)
{
    name_ = name;
    duration_ = duration;
}

Animation::~Animation()
{
}

void Animation::insert_keyframe(Animation_Keyframe* keyframe, int index)
{
	if (index == -1)
	{
        keyframes_.push_back(keyframe);
	}
	else if (index >= keyframes_.size())
	{
		keyframes_.push_back(keyframe);
	}
	else
	{
		keyframes_.insert(keyframes_.begin() + index, keyframe);
	}
}

void Animation::remove_keyframe(int index)
{
	if (index >= keyframes_.size())
		return;

	delete *(keyframes_.begin() + index);
	keyframes_.erase(keyframes_.begin() + index);
}

void Animation::remove_all_keyframe()
{
    Keyframes::iterator iend = keyframes_.end();
    for (Keyframes::iterator i = keyframes_.begin(); i != iend; ++i)
    {
        delete (*i);
    }

    keyframes_.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
}
