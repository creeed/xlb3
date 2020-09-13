#include "XlbeSprite.h"
#include "XlbeActionAnimation.h"
#include "XlbeAnimationResource.h"
#include "XlbeAnimationResourceManager.h"

///////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

///////////////////////////////////////////////////////////////////////////////////////////////
Action_Animation::Action_Animation(const std::string &str_animation, bool origin)
:Action_Interval(((Animation_Resource*)Animation_Resource_Manager::singleton()->get_resource(str_animation))->get_duration()),
animation_(((Animation_Resource*)Animation_Resource_Manager::singleton()->get_resource(str_animation))),
origin_(origin)
{
}

Action_Animation::Action_Animation(Animation_Resource *animation, bool origin)
:Action_Interval(animation->get_duration()),
animation_(animation),
origin_(origin)
{
	index_ = 0;
	first_frame_ = true;
    duration_ = animation->get_duration();
	origin_sprite_ = 0;
}

Action_Animation::~Action_Animation()
{
}

void Action_Animation::stop() 
{
	index_ = 0;

    if (origin_ && target_)
    {
        Sprite *sprite = static_cast<Sprite *>(target_) ; 
		if (origin_sprite_)
            sprite->set_sprite_resource(origin_sprite_);
    }

    __super::stop();
}

void Action_Animation::update(float time)
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
		sprite->set_sprite_resource(animation_->get_keyframe(index_)->get_value());
	}
}

void Action_Animation::start_with_target(Node *target)
{
    __super::start_with_target(target);

	index_ = 0;
	first_frame_ = true;
    Sprite *sprite = static_cast<Sprite *>(target_) ; 
    origin_sprite_ = sprite->get_sprite_resource();
}

///////////////////////////////////////////////////////////////////////////////////////////
}