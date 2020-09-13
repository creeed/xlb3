#include "XlbeException.h"
#include "XlbeAnimationKeyframe.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

/////////////////////////////////////////////////////////////////////////////////////////////////////
Animation_Keyframe::Animation_Keyframe(Sprite_Resource *res, float time)
:value_(res), 
time_(time)
{
}

Animation_Keyframe::Animation_Keyframe(const Animation_Keyframe &frame)
:value_(frame.value_), 
time_(frame.time_)
{
}

Animation_Keyframe::~Animation_Keyframe()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
}