#include "XlbePrereqs.h"
#include "XlbeColorRect.h"
#include "XlbeImageset.h"
#include "XlbeCheckButton.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////////
Check_Button::Check_Button(const std::string &name, Widget_Manager *creator) : Widget(name, "CheckButton", creator)
{
    over_ = false;
    down_ = false;
	checked_ = false;

    button_image_ = 0;
    over_image_ = 0;
    down_image_ = 0;	
    disabled_image_ = 0;

    check_button_image_ = 0;
    check_over_image_ = 0;
    check_down_image_ = 0;	
    check_disabled_image_ = 0;

	slot_func_ = 0;
}

Check_Button::~Check_Button() 
{
}

void Check_Button::set_image(const std::string &button_image, const std::string &over_image,
		const std::string &down_image, const std::string &disabled_image,
		const std::string &check_button_image, const std::string &check_over_image,
		const std::string &check_down_image, const std::string &check_disabled_image)
{
    button_image_ = Imageset_Manager::singleton()->string_to_image(button_image);
    over_image_ = Imageset_Manager::singleton()->string_to_image(over_image);
    down_image_ = Imageset_Manager::singleton()->string_to_image(down_image);	
    disabled_image_ = Imageset_Manager::singleton()->string_to_image(disabled_image);
	check_button_image_ = Imageset_Manager::singleton()->string_to_image(check_button_image);
    check_over_image_ = Imageset_Manager::singleton()->string_to_image(check_over_image);
    check_down_image_ = Imageset_Manager::singleton()->string_to_image(check_down_image);	
    check_disabled_image_ = Imageset_Manager::singleton()->string_to_image(check_disabled_image);
}

void Check_Button::on_got_focus()
{
}

void Check_Button::on_lost_focus()
{
    down_ = false;
	over_ = false;
}

void Check_Button::on_mouse_enter(const Point &pt)
{
	__super::on_mouse_enter(pt);

	over_ = true;
}
void Check_Button::on_mouse_exit(const Point &pt)
{
	__super::on_mouse_exit(pt);

    //down_ = false;
	over_ = false;
}

void Check_Button::on_mouse_down(const Point &pt, Mouse_ButtonID button_id, int click_count)
{
 if (!is_visible()|| !is_enabled())
        return ;

    down_ = true;
}

void Check_Button::on_mouse_up(const Point &pt, Mouse_ButtonID button_id, int click_count)
{
	if (down_ && over_)
	{
		down_ = false;
		checked_ ^= 1; 

		if (slot_func_)
            (*slot_func_)(this);
	}
	else 
	{
		down_ = false;
	}
}

void Check_Button::draw()
{
    if (!is_visible() || !disabled_image_ || !down_image_ || !over_image_ || !button_image_
		|| !check_disabled_image_ || !check_down_image_ || !check_over_image_ || !check_button_image_)
        return;

    Point pt = get_absolute_position();

	if (checked_)
	{
		if (!is_enabled())
		{
			check_disabled_image_->draw(pt, get_size());
		}
		else if (down_)
		{
			check_down_image_->draw(pt, get_size());
		}
		else if (over_)
		{
			check_over_image_->draw(pt, get_size());
		}
		else
		{
			check_button_image_->draw(pt, get_size());
		}
	}
	else
	{
		if (!is_enabled())
		{
			disabled_image_->draw(pt, get_size());
		}
		else if (down_)
		{
			down_image_->draw(pt, get_size());
		}
		else if (over_)
		{
			over_image_->draw(pt, get_size());
		}
		else
		{
			button_image_->draw(pt, get_size());
		}

	}


	Font *font = get_font();

	if (font)
	{
		Point pt_draw;

		int width = font->get_string_width(get_text().c_str());
		int height = font->get_height();

		pt_draw.x_ = (get_size().width_ - width) / 2.0 + pt.x_;
		pt_draw.y_ = (get_size().height_ - height) / 2.0 + pt.y_;

		font->draw_string(pt_draw, get_size(), get_text().c_str(), Color_Rect(), LT_LEFT, 0);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

