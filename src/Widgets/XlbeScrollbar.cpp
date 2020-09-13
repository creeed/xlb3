#include "XlbeException.h"
#include "XlbeButton.h"
#include "XlbeScrollbar.h"
#include "XlbeWidgetManager.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////////
Scrollbar::Scrollbar(const std::string &name, Widget_Manager *creator) : Widget(name, "Scrollbar", creator)
{
	track_image_ = 0;
	thumb_image_ = 0;

	slot_func_ = 0;

	invis_if_no_scroll_ = false;

	value_ = 0.0f;
	max_value_ = 0.0f;
	page_size_ = 0.0f;
	horizontal_ = false;

	pressed_on_thumb_ = false;
	mouse_down_thumb_pos_ = 0.0f;

	mouse_down_x_ = 0.0f;
	mouse_down_y_ = 0.0f;
	last_mouse_x_ = 0.0f;
	last_mouse_y_ = 0.0f;

	up_button_ = (Button*)creator->create_widget(name + "InnerUpButton", "Button");
	down_button_ = (Button*)creator->create_widget(name + "InnerDwonButton", "Button");

	up_button_->set_slot(rak::mem_fn(this, &Scrollbar::button_press));
	down_button_->set_slot(rak::mem_fn(this, &Scrollbar::button_press));

	
	add_widget(up_button_);
	add_widget(down_button_);

	set_movable(false);
}

Scrollbar::~Scrollbar() 
{
	//if (up_button_)
	//	delete up_button_;

	//if (down_button_)
	//	delete down_button_;
}

void Scrollbar::set_image(const std::string &track_image, const std::string &thumb_image)
{
	track_image_ = Imageset_Manager::singleton()->string_to_image(track_image);	
    thumb_image_ = Imageset_Manager::singleton()->string_to_image(thumb_image);
}

void Scrollbar::set_upbutton_image(const std::string &button_image, const std::string &over_image,
		const std::string &down_image, const std::string &disabled_image)
{
	up_button_->set_image(button_image, over_image, down_image, disabled_image);
	if (horizontal_)
	{
		up_button_->set_position(0, 0);
		up_button_->set_size (get_size().height_, get_size().height_);
	}
	else
	{
		up_button_->set_position(0, 0);
		up_button_->set_size (get_size().width_, get_size().width_);
	}

}

void Scrollbar::set_downbutton_image(const std::string &button_image, const std::string &over_image,
		const std::string &down_image, const std::string &disabled_image)
{
	down_button_->set_image(button_image, over_image, down_image, disabled_image);
	if (horizontal_)
	{
		down_button_->set_position(get_size().width_ - get_size().height_, 0);
		down_button_->set_size (get_size().height_, get_size().height_);
	}
	else
	{
		down_button_->set_position(0, get_size().height_ - get_size().width_);
		down_button_->set_size (get_size().width_, get_size().width_);
	}
}

void Scrollbar::set_invis_if_no_scroll(bool invis_if_no_scroll)
{
	invis_if_no_scroll_ = invis_if_no_scroll;

	if (invis_if_no_scroll_)
	{
		set_visible(false);
		up_button_->set_visible(false);
		down_button_->set_visible(false);
	}
}

void Scrollbar::set_value(float value)
{
	value_ = value;

	clamp_value();

	if (slot_func_)
        (*slot_func_)(this);

}

void Scrollbar::set_max_value(float max_value)
{
	max_value_ = max_value;

	clamp_value();
}

void Scrollbar::set_page_size(float page_size)
{
	page_size_ = page_size;

	clamp_value();
}
	
void Scrollbar::set_horizontal(bool horizontal)
{
	horizontal_ = horizontal;
}

float Scrollbar::get_track_size()
{
	if (horizontal_)
	{
		return size_.width_ - 2 * up_button_->get_size().width_;
	}
	else
	{
		return size_.height_ - 2 * up_button_->get_size().height_;
	}
}

float Scrollbar::get_thumb_size()
{
	if (page_size_ > max_value_)
	{
		return get_track_size();
	}
		
	float thumb_size =  ((get_track_size() * page_size_ / max_value_)) + 0.5;
	return std::max(8.0f, thumb_size);
}

float Scrollbar::get_thumb_position() 
{
	if (page_size_ > max_value_) return up_button_->get_size().width_;
	return (((value_ * (get_track_size() - get_thumb_size())) / (max_value_ - page_size_)) + 0.5) + up_button_->get_size().width_;
}

void Scrollbar::set_thumb_position(float position)
{
    set_value(((position - up_button_->get_size().width_) * (max_value_ - page_size_)) / (get_track_size() - get_thumb_size()));				
}

void Scrollbar::clamp_value()
{
	float value = value_;
		
	if (value_ > max_value_ - page_size_)
		value_ = max_value_ - page_size_;
	if (value_ < 0.0)
		value_ = 0.0;
		
	bool can_scroll = page_size_ < max_value_;
		
	set_enabled(can_scroll);
	up_button_->set_enabled(can_scroll);
	down_button_->set_enabled(can_scroll);
				
	if (invis_if_no_scroll_) 
	{
		set_visible(!can_scroll);
		up_button_->set_visible(!can_scroll);
		down_button_->set_visible(!can_scroll);
	}
		
	if (value != value_) 
	{
	    if (slot_func_)
            (*slot_func_)(this);
	}
}

int Scrollbar::thumb_compare(float x, float y)
{
	float track_position; 

	if (horizontal_)
		track_position = x;
	else
		track_position = y;
		
	if (track_position < get_thumb_position()) 
		return -1;

	if (track_position >= get_thumb_position() + get_thumb_size()) 
		return 1;

	return 0;
}

void Scrollbar::update(float dt)
{
	Widget::update(dt);
}

void Scrollbar::draw()
{
    if (!is_visible() || !track_image_ || !thumb_image_)
        return;

	Point pt = get_absolute_position();
	Size size = get_size();

	float thumb_size = get_thumb_size();
	float thumb_position = get_thumb_position();

	track_image_->draw(pt, size);
	
	if (horizontal_)
	{
        thumb_image_->draw(pt + Point(thumb_position, 0), Size(thumb_size, size.height_));
	}
	else
	{
        thumb_image_->draw(pt + Point(0, thumb_position), Size(size.width_, thumb_size));
	}

	Widget::draw();
}

void Scrollbar::on_got_focus()
{
}

void Scrollbar::on_lost_focus()
{
}

void Scrollbar::on_mouse_enter(const Point &pt)
{
	__super::on_mouse_enter(pt);
}

void Scrollbar::on_mouse_exit(const Point &pt)
{
	__super::on_mouse_exit(pt);
}

void Scrollbar::on_mouse_down(const Point &pt, Mouse_ButtonID button_id, int click_count)
{
	Widget::on_mouse_down(pt, button_id, click_count);

	if (!is_visible()|| !is_enabled())
		return ;

	Point pt_widget = pt - get_absolute_position();

	switch (thumb_compare(pt_widget.x_, pt_widget.y_))	
	{
	case -1:
		set_value(value_ - page_size_);
		break;
	case 0:
		pressed_on_thumb_ = true;
		mouse_down_thumb_pos_ = get_thumb_position();
		mouse_down_x_ = pt_widget.x_;
		mouse_down_y_ = pt_widget.y_;
		break;
	case 1:
		set_value(value_ + page_size_);
		break;
	}

	last_mouse_x_ = pt_widget.x_;
	last_mouse_x_ = pt_widget.y_;

}

void Scrollbar::on_mouse_up(const Point &pt, Mouse_ButtonID button_id, int click_count)
{
	Widget::on_mouse_up(pt, button_id, click_count);

	pressed_on_thumb_ = true;
}

void Scrollbar::on_mouse_drag(const Point &pt)
{
	Widget::on_mouse_drag(pt);

	Point pt_widget = pt - get_absolute_position();
	if (pressed_on_thumb_) 
	{
		if (horizontal_)
			set_thumb_position(mouse_down_thumb_pos_ + pt_widget.x_ - mouse_down_x_);
		else
			set_thumb_position(mouse_down_thumb_pos_ + pt_widget.y_ - mouse_down_y_);
	}
		
	last_mouse_x_ = pt_widget.x_;
	last_mouse_x_ = pt_widget.y_;
}

bool Scrollbar::button_press(Button* button) 
{		
	if (button == up_button_) 
		set_value(value_ - 1);
	else 
		set_value(value_ + 1);

	return true;
}
	

//////////////////////////////////////////////////////////////////////////////////////////////////////
}


