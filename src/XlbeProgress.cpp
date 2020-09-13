#include "XlbePrereqs.h"
#include "XlbeColorRect.h"
#include "XlbeImageset.h"
#include "XlbeProgress.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////////
Progress::Progress(const std::string& name) : Widget(name)
{
    over_ = false;
    down_ = false;

    value_ = 0.0f;

    track_image_ = 0;
    step_image_ = 0;
}

Progress::~Progress() 
{
}

void Progress::set_image(const std::string &track_image, const std::string &step_image)
{
    track_image_ = Imageset_Manager::singleton()->string_to_image(track_image);
    step_image_ = Imageset_Manager::singleton()->string_to_image(step_image);
}

void Progress::set_value(double value)
{
    value_ = value;
    if (value_ < 0.0)
        value_ = 0.0;
    else if (value_ > 1.0)
        value_ = 1.0;
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
	over_ = true;
}
void Progress::on_mouse_exit(const Point &pt)
{
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
        /*(*slot_func_)(this);*/
	}
	else 
	{
		down_ = false;
	}
}

void Progress::draw()
{
    if (!is_visible() || !track_image_ || !step_image_)
        return;

    Point pt = get_absolute_position();
	Point pt_draw = pt;
	Point pt_src(0, 0);

    Size size = get_size();
	Size size_draw = size;
	Size size_src = size;

    pt_draw = pt;
    track_image_->draw(pt_draw, size);

    pt_draw = pt;
    size_draw = Size(value_ * size.width_, size.height_ );
    size_src = Size(value_ * step_image_->get_width(), step_image_->get_height());
    step_image_->draw(pt_draw, size_draw, pt_src, size_src);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

