#include "XlbeException.h"
#include "XlbeSpriteResource.h"
#include "XlbeAnimationResource.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////////////
Animation_Resource::Animation_Resource(const std::string& name)
{
	resource_type_ = "animation";

    name_ = name;
}

Animation_Resource::~Animation_Resource()
{
	//由用户来卸载资源， 回避引用计数
	//remove_all_keframe();
}

void Animation_Resource::prepare()
{
	if (!is_prepared())
    {
       load_state_ = LOADSTATE_PREPARED;
    }
}

void Animation_Resource::unprepare()
{
	load_state_ = LOADSTATE_UNPREPARED;
}

void Animation_Resource::load()
{
    if (!is_loaded())
    {
        load_state_ = LOADSTATE_LOADED;
    }
}

void Animation_Resource::unload()
{
    load_state_ = LOADSTATE_UNLOADED;
}

void Animation_Resource::insert_keyframe(Animation_Keyframe* keyframe, int index)
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

void Animation_Resource::remove_keyframe(int index)
{
	if (index >= keyframes_.size())
		return;

	delete *(keyframes_.begin() + index);
	keyframes_.erase(keyframes_.begin() + index);
}

void Animation_Resource::remove_all_keyframe()
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
