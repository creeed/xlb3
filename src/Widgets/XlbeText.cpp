#include "XlbePrereqs.h"
#include "XlbeColorRect.h"
#include "XlbeImageset.h"
#include "XlbeText.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////////
Text::Text(const std::string &name, Widget_Manager *creator) : Widget(name, "Text", creator)
{
    image_ = 0;
	slot_func_ = 0;
	format_ = 0;

}

Text::~Text() 
{
}

void Text::set_image(const std::string &image)
{
    image_ = Imageset_Manager::singleton()->string_to_image(image);
}

void Text::set_text(const std::string& text)
{
	if (text_ != text)
	{
		text_ = text;
	}
}

void Text::on_got_focus()
{
}

void Text::on_lost_focus()
{
    //down_ = false;
	//over_ = false;
}

void Text::on_mouse_enter(const Point &pt)
{
	__super::on_mouse_enter(pt);
	//over_ = true;
}
void Text::on_mouse_exit(const Point &pt)
{
	__super::on_mouse_exit(pt);
    //down_ = false;
	//over_ = false;
}

void Text::on_mouse_down(const Point &pt, Mouse_ButtonID button_id, int click_count)
{
    //if (!is_visible()|| !is_enabled())
    //    return ;

    //down_ = true;
}

void Text::on_mouse_up(const Point &pt, Mouse_ButtonID button_id, int click_count)
{
	//if (down_ && over_)
	//{
	//	down_ = false;
 //       /*(*slot_func_)(this);*/
	//}
	//else 
	//{
	//	down_ = false;
	//}
}

void Text::draw()
{
	if (!visible_)
		return;

	Point pt = get_absolute_position() ;

	if (image_)
        image_->draw(pt, get_size());

	if (font_)
	{
		font_->draw_string(pt, size_, text_.c_str(), color_, format_, 0);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

