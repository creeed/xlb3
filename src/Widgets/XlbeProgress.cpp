#include "XlbePrereqs.h"
#include "XlbeColorRect.h"
#include "XlbeWidgetManager.h"
#include "XlbeSprite.h"
#include "XlbeProgress.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////////
Progress::Progress(const std::string &name) : Window(name)
{
    over_ = false;
    down_ = false;

    value_ = 0.0f;

    spr_track_ = new Sprite(name + "_track");
    spr_step_  = new Sprite(name + "_step");

	spr_track_->set_hot(Point(0, 0));
    spr_step_->set_hot(Point(0, 0));
}

Progress::~Progress() 
{
	delete spr_track_;
	delete spr_step_;
}

void Progress::set_track_image(const std::string &image)
{
	if (image.empty())
		return ;

	spr_track_->set_sprite_resource(image);
}

void Progress::set_step_image(const std::string &image)
{
	if (image.empty())
		return ;

	spr_step_->set_sprite_resource(image);
}

void Progress::set_value(float value)
{
    value_ = value;
    if (value_ < 0.0)
        value_ = 0.0f;
    else if (value_ > 1.0f)
        value_ = 1.0f;
}

void Progress::on_got_focus()
{
}

void Progress::on_lost_focus()
{
    down_ = false;
	over_ = false;
}

void Progress::on_mouse_enter(const Point &pt)
{
	Window::on_mouse_enter(pt);
	over_ = true;
}
void Progress::on_mouse_exit(const Point &pt)
{
	Window::on_mouse_exit(pt);
    //down_ = false;
	over_ = false;
}

void Progress::on_mouse_down(const Point &pt, Mouse_ButtonID button_id, int click_count)
{
 if (!is_visible()|| !is_enabled())
        return ;

    down_ = true;
}

void Progress::on_mouse_up(const Point &pt, Mouse_ButtonID button_id, int click_count)
{
	if (down_ && over_)
	{
		down_ = false;
	}
	else 
	{
		down_ = false;
	}
}

void Progress::draw()
{
    if (!is_visible())
		return;

	Point pt = get_absolute_position();
	Point pt_draw = pt;
	Point pt_src(0, 0);

	Size size = get_size();
	Size size_draw = size;
	Size size_src = size;

	pt_draw = pt;

	if (spr_track_->get_sprite_resource())
	{
		spr_track_->set_position(pt_draw);
		spr_track_->set_size(size);
		spr_track_->draw();
	}

	pt_draw = pt;
	size_draw = Size(value_ * size.width_, size.height_ );
	//size_src = Size(value_ * step_image_->get_width(), step_image_->get_height());

	if (spr_step_->get_sprite_resource())
	{		
		spr_step_->set_position(pt_draw);
		spr_step_->set_src_rect(Rect(Point(0,0), size_draw));
		spr_step_->set_size(size_draw);  // Òª¸Ä src_rect
		spr_step_->draw();
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

