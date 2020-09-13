#include "XlbeSprite.h"
#include "XlbeAnimationInstance.h"

///////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

///////////////////////////////////////////////////////////////////////////////////////////////
Animation_Instance::Animation_Instance(Animation *animation, bool origin)
:Action_Interval(animation->get_duration()),
animation_(animation),
origin_(origin)
{
	index_ = 0;
	first_frame_ = true;
	origin_image_ = 0;
    duration_ = animation->get_duration();
}

Animation_Instance::~Animation_Instance()
{
}

void Animation_Instance::stop() 
{
	index_ = 0;

    if (origin_ && target_)
    {
        Sprite *sprite = static_cast<Sprite *>(target_) ; 
        sprite->set_displayed_image(origin_image_);
    }

    __super::stop();
}

void Animation_Instance::update(float time)
{
	int index = index_;
	int result = index_;
	int keyframe_count = animation_->number_of_keyframe();
    float animation_time = time * animation_->get_duration();

	for (result = index_; result < keyframe_count; result++)
	{
		if (animation_time >= animation_->get_keyframe(result)->get_time() )
		{
			index_ = result;
        }
		else
			break;
	}

	if ((index != index_) || (index_ == 0 && first_frame_))
	{
		first_frame_ = false;
        Sprite *sprite = static_cast<Sprite *>(target_); 
	    sprite->set_displayed_image(animation_->get_keyframe(index_)->get_value());
	}

}

void Animation_Instance::start_with_target(Entity *target)
{
    __super::start_with_target(target);

    Sprite *sprite = static_cast<Sprite *>(target_) ; 

	index_ = 0;
	first_frame_ = true;
    origin_image_ = sprite->get_displayed_plate();

}

///////////////////////////////////////////////////////////////////////////////////////////
}