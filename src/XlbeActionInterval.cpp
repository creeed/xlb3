#include "XlbeException.h"
#include "XlbeNode.h"
#include "XlbeActionInterval.h"

/////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

/////////////////////////////////////////////////////////////////////////////////////////
Action_Interval::Action_Interval(float d)
:stop_(false)
{
	duration_ = d;
}

Action_Interval::~Action_Interval()
{
}

void Action_Interval::reset() 
{
    elapsed_ = 0.0f;
    stop_ = false;
}

void Action_Interval::step(float dt)
{
    elapsed_ += dt;

    update(std::min(1.0f, (float)elapsed_/duration_));
}

void Action_Interval::update(float time)
{
}

void Action_Interval::start_with_target(Node *target)
{
    reset();

    __super::start_with_target(target);
}

/////////////////////////////////////////////////////////////////////////////////////////
Action_Fade_Out::Action_Fade_Out(float d)
:Action_Interval(d)
{
}

Action_Fade_Out::~Action_Fade_Out()
{
}

void Action_Fade_Out::update(float time)
{
    Color_Rect color_rect(target_->get_color_rect());

	color_rect.top_left_[3] = 255*(1-time);
    color_rect.top_right_[3]= 255*(1-time);
    color_rect.bottom_left_[3]= 255*(1-time);
    color_rect.bottom_right_[3]= 255*(1-time);

    target_->set_color_rect(color_rect);
}

/////////////////////////////////////////////////////////////////////////////////////////
Action_Fade_In::Action_Fade_In(float d)
:Action_Interval(d)
{
}

Action_Fade_In::~Action_Fade_In()
{
}

void Action_Fade_In::update(float time)
{
    Color_Rect color_rect(target_->get_color_rect());

	color_rect.top_left_[3] = 255*time;
    color_rect.top_right_[3]= 255*time;
    color_rect.bottom_left_[3]= 255*time;
    color_rect.bottom_right_[3]= 255*time;

    target_->set_color_rect(color_rect);
}

//////////////////////////////////////////////////////////////////////////////////////////////
Action_Move_To::Action_Move_To(float d, Point end)
:Action_Interval(d),
end_(end)
{
}

Action_Move_To::~Action_Move_To()
{
}

void Action_Move_To::start_with_target(Node *target)
{
    start_ = target->get_position();
    delta_ = end_ - start_;

    __super::start_with_target(target);
}

void Action_Move_To::update(float time)
{
    Point pt(start_.x_+delta_.x_*time, start_.y_+delta_.y_*time);

    target_->set_position(pt);
}

//////////////////////////////////////////////////////////////////////////////////////////////
Action_Move_By::Action_Move_By(float d, Point delta)
:Action_Move_To(d, Point(0,0))
{
    delta_ = delta;
}

Action_Move_By::~Action_Move_By()
{
}

void Action_Move_By::start_with_target(Node *target)
{
    Point temp = delta_;

    __super::start_with_target(target);
    delta_ = temp;
}

////////////////////////////////////////////////////////////////////////////////////////////
Action_Rorate_To::Action_Rorate_To(float d, float end)
:Action_Interval(d),
end_angle_(end)
{
}

Action_Rorate_To::~Action_Rorate_To()
{
}

void Action_Rorate_To::update(float time)
{
    target_->set_rotation(start_angle_+diff_angle_*time); 
}

void Action_Rorate_To::start_with_target(Node *target)
{
    __super::start_with_target(target);

    start_angle_ = target->get_rotation();

    if (start_angle_ > 0)
        start_angle_ = std::fmodf(start_angle_, M_PI);
    else
        start_angle_ = std::fmodf(start_angle_, -M_PI);

    diff_angle_ = end_angle_ - start_angle_;
    if (diff_angle_ > M_PI_2)
        diff_angle_ -= M_PI;
    if (diff_angle_ < -M_PI_2)
        diff_angle_ += M_PI;
}

////////////////////////////////////////////////////////////////////////////////////////////
Action_Rorate_By::Action_Rorate_By(float d, float angle)
:Action_Interval(d), diff_angle_(angle), start_angle_(0)
{
}

Action_Rorate_By::~Action_Rorate_By()
{
}

void Action_Rorate_By::update(float time)
{
    target_->set_rotation(start_angle_+diff_angle_*time); 
}

void Action_Rorate_By::start_with_target(Node *target)
{
    __super::start_with_target(target);

    start_angle_ = target->get_rotation();

    if (start_angle_ > 0)
        start_angle_ = std::fmodf(start_angle_, M_PI);
    else
        start_angle_ = std::fmodf(start_angle_, -M_PI);
}

////////////////////////////////////////////////////////////////////////////////////////////
Action_Scale_To::Action_Scale_To(float d, float scale)
:Action_Interval(d),
end_scale_x_(scale),
end_scale_y_(scale)
{
}

Action_Scale_To::Action_Scale_To(float d, float scalex, float scaley)
:Action_Interval(d),
end_scale_x_(scalex),
end_scale_y_(scaley)
{
}

Action_Scale_To::~Action_Scale_To()
{
}

void Action_Scale_To::update(float time)
{
    target_->set_scale(Size(start_scale_x_ + delta_x_ * time,  start_scale_y_ + delta_y_ * time )) ;
}

void Action_Scale_To::start_with_target(Node *target)
{
    __super::start_with_target(target);

    start_scale_x_ = target_->get_scale().width_;
    start_scale_y_ = target_->get_scale().height_;

    delta_x_ = end_scale_x_ - start_scale_x_;
    delta_y_ = end_scale_y_ - start_scale_y_;
}

////////////////////////////////////////////////////////////////////////////////////////////
Action_Scale_By::Action_Scale_By(float d, float scale_x, float scale_y)
:Action_Scale_To(d, scale_x, scale_y)
{
}

Action_Scale_By::~Action_Scale_By()
{
}

void Action_Scale_By::start_with_target(Node *target)
{
    __super::start_with_target(target);

    delta_x_ = end_scale_x_ ;
    delta_y_ = end_scale_y_ ;
}

////////////////////////////////////////////////////////////////////////////////////////////
Action_Delay::Action_Delay(float d)
:Action_Interval(d)
{
}

Action_Delay::~Action_Delay()
{
}

void Action_Delay::start_with_target(Node *target)
{
    __super::start_with_target(target);

}

////////////////////////////////////////////////////////////////////////////////////////////

}
