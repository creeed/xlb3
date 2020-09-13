#include "XlbePrereqs.h"
#include "XlbeColorRect.h"
#include "XlbeSlider.h"
#include "XlbeSprite.h"
#include "XlbeWidgetManager.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////////
Slider::Slider(const std::string &name) : Window(name)
{
    over_ = false;
    down_ = false;

    value_ = 0;
    rel_x_ = 0;

    spr_track_ = new Sprite(name + "_track");
    spr_thumb_ = new Sprite(name + "_thumb");

	spr_thumb_->set_hot(Point(0, 0));
    spr_track_->set_hot(Point(0, 0));

}

Slider::~Slider() 
{
}

void Slider::set_track_image(const std::string &image)
{
	if (image.empty())
		return ;

	spr_track_->set_sprite_resource(image);
}

void Slider::set_thumb_image(const std::string &image)
{
	if (image.empty())
		return ;

	spr_thumb_->set_sprite_resource(image);
}

void Slider::set_value(float value)
{
    value_ = value;
    if (value_ < 0.0)
        value_ = 0.0;
    else if (value_ > 1.0)
        value_ = 1.0;
}

void Slider::on_got_focus()
{
}

void Slider::on_lost_focus()
{
    down_ = false;
	over_ = false;
}

void Slider::on_mouse_enter(const Point &pt)
{
	Window::on_mouse_enter(pt);

	over_ = true;
}

void Slider::on_mouse_exit(const Point &pt)
{
	Window::on_mouse_exit(pt);

    //down_ = false;
	over_ = false;
}

void Slider::on_mouse_down(const Point &pt, Mouse_ButtonID button_id, int click_count)
{
 if (!is_visible()|| !is_enabled())
        return ;

    Point pt_widget = pt - get_absolute_position();
    down_ = true;

    Size size = get_size();
	int thumb_x = (int) (value_ * (size.width_ - spr_thumb_->get_texture_size().width_));

    if ((pt_widget.x_ >= thumb_x) && (pt_widget.x_ < thumb_x + spr_thumb_->get_texture_size().width_))
    {
        rel_x_ = pt_widget.x_ - thumb_x;
    }
    else
    {
        float pos = pt_widget.x_ / size.width_;
        set_value(pos);
    } 
}

void Slider::on_mouse_up(const Point &pt, Mouse_ButtonID button_id, int click_count)
{
	if (down_)
	{
		down_ = false;
		Widget_Manager::singleton()->send_notify(this, UI_MSGTYPE_VALUECHANGED, pt.x_ , pt.y_ , false);
	}
	else 
	{
		down_ = false;
	}
}

void Slider::on_mouse_drag(const Point &pt)
{
	Point pt_widget = pt -get_absolute_position();

	double old_val = value_;
	Size size = get_size();

	value_ = (pt_widget.x_ - rel_x_) / (double) (size.width_ - spr_thumb_->get_texture_size().width_);

	if (value_ < 0.0)
		value_ = 0.0;
	if (value_ > 1.0)
		value_ = 1.0;
}

void Slider::draw()
{
    if (!is_visible())
        return;

    Point pt = get_absolute_position();
	Point pt_draw = pt;

    Size size = get_size();
	Size size_draw = size;

	spr_track_->set_size(size_draw);
	spr_track_->set_position(pt_draw);
	spr_track_->draw();

    size_draw.width_ = spr_thumb_->get_texture_size().width_ * (size.width_ / spr_track_->get_texture_size().width_);
    pt_draw = pt + Point((int) (value_ * (size.width_ - size_draw.width_)), 0);

	spr_thumb_->set_size(size_draw);
	spr_thumb_->set_position(pt_draw);
	spr_thumb_->draw();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

