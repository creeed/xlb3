#include "XlbePrereqs.h"
#include "XlbeColorRect.h"
#include "XlbeButton.h"
#include "XlbeWidgetManager.h"
#include "XlbeSprite.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////////
Button::Button(const std::string &name) : Window(name)
{
    over_ = false;
    push_ = false;

    spr_normal_ = new Sprite(name + "_normal");
    spr_over_  = new Sprite(name + "_over");
    spr_push_ = new Sprite(name + "_push");
    spr_disabled_  = new Sprite(name + "_disabled");

	spr_normal_->set_hot(Point(0, 0));
	spr_over_->set_hot(Point(0, 0));
	spr_push_->set_hot(Point(0, 0));
	spr_disabled_->set_hot(Point(0, 0));
}

Button::~Button() 
{
	delete spr_normal_;
	delete spr_over_;
	delete spr_push_;
	delete spr_disabled_;
}

void Button::set_normal_image(const std::string &image)
{
	if (image.empty())
		return ;

	spr_normal_->set_sprite_resource(image);
}

void Button::set_over_image(const std::string &image)
{
	if (image.empty())
		return ;

	spr_over_->set_sprite_resource(image);
}

void Button::set_push_image(const std::string &image)
{
	if (image.empty())
		return ;

	spr_push_->set_sprite_resource(image);
}

void Button::set_disabled_image(const std::string &image)
{
	if (image.empty())
		return ;

	spr_disabled_->set_sprite_resource(image);
}

void Button::on_got_focus()
{
}

void Button::on_lost_focus()
{
    push_ = false;
	over_ = false;
}

void Button::on_mouse_enter(const Point &pt)
{
	Window::on_mouse_enter(pt);

	over_ = true;
}
void Button::on_mouse_exit(const Point &pt)
{
	Window::on_mouse_exit(pt);

    push_ = false;
	over_ = false;
}

void Button::on_mouse_down(const Point &pt, Mouse_ButtonID button_id, int click_count)
{
 if (!is_visible()|| !is_enabled())
        return ;

    push_ = true;
}

void Button::on_mouse_up(const Point &pt, Mouse_ButtonID button_id, int click_count)
{
	if (push_ && over_)
	{
		push_ = false;

		Widget_Manager::singleton()->send_notify(this, UI_MSGTYPE_CLICK, pt.x_ , pt.y_ , false);
	}
	else 
	{
		push_ = false;
	}
}

void Button::draw()
{
    if (!is_visible())
        return;

    Point pt = get_absolute_position();

    if (!is_enabled() && spr_disabled_->get_sprite_resource())
    {
		spr_disabled_->set_position(pt);
		spr_disabled_->set_size(get_size());
        spr_disabled_->draw();
    }
    else if (push_)
    {
        spr_push_->set_position(pt);
		spr_push_->set_size(get_size());
        spr_push_->draw();
    }
    else if (over_)
    {
        spr_over_->set_position(pt);
		spr_over_->set_size(get_size());
        spr_over_->draw();
    }
    else
    {
        spr_normal_->set_position(pt);
		spr_normal_->set_size(get_size());
        spr_normal_->draw();
    }

	Widget::draw();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

