#include "XlbePrereqs.h"
#include "XlbeColorRect.h"
#include "XlbeStatic.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////////
Static::Static(const std::string &name) : Window(name)
{
	align_ = 0;
	text_changed_ = false;
}

Static::~Static() 
{
}

void Static::set_font(const std::string &font) 
{
	if (font.empty())
		return;

	Font *afont = (Font*)Font_Manager::singleton()->get_resource(font); 

	if (font_ != afont)
	{
		Window::set_font(font);
		text_changed_ = true;
	}
}

void Static::set_size(const Size &size) 
{
	if (size_ != size)
	{
		Window::set_size(size);
		text_changed_ = true;
	}
}

void Static::set_text(const std::string& text)
{
	if (text_ != text)
	{
		Window::set_text(text);
        text_changed_ = true;
	}
}

void Static::adjust_text()
{
	if (!text_changed_)
		return;

	if (!font_ || size_.width_ == 0.0f
		|| size_.height_ == 0.0f || text_.empty())
		return ;

	text_rows_.clear();

	int length;
	std::string subn, subl;
	std::string::size_type pos, last_pos = 0;

	do
	{
		pos = text_.find("\n", last_pos);

		if (pos != std::string::npos)
		{
			length = pos - last_pos;
		}
		else
		{
			length = text_.size() - last_pos;
		}

		subn = text_.substr(last_pos, length);

		if ((align_ & LT_CENTER) != 0)
		{
			int row = std::ceil( (float)(font_->get_string_width(subn.c_str())) / size_.width_ );
			int step = std::ceil( (float)subn.size() / (float)row );

			for (int i = 0; i < row; i++)
			{
				subl = subn.substr(i * step, step);
				text_rows_.push_back(subl);
			}
		}
		else
		{
			text_rows_.push_back(subn);
		}

		last_pos = pos + 1;

	} while (pos != std::string::npos);

	text_changed_ = false;
}

void Static::on_got_focus()
{
}

void Static::on_lost_focus()
{

}

void Static::on_mouse_enter(const Point &pt)
{
	Window::on_mouse_enter(pt);

}
void Static::on_mouse_exit(const Point &pt)
{
	Window::on_mouse_exit(pt);

}

void Static::on_mouse_down(const Point &pt, Mouse_ButtonID button_id, int click_count)
{
 
}

void Static::on_mouse_up(const Point &pt, Mouse_ButtonID button_id, int click_count)
{

}

void Static::draw()
{
	Window::draw();

    if (!is_visible())
        return;

	float x = 0.0f, y = 0.0f;
    Point pt = get_absolute_position() ;

	if (!font_ || text_.empty())
		return ;

	adjust_text();

	if (text_rows_.size() == 1)
	{
		float len = font_->get_string_width(text_.c_str());
		float height = font_->get_height();
		
		if ((align_ & LT_CENTER) != 0)
		{
			x = (size_.width_ - len) / 2.0f;
		}

		if ((align_ & LT_RIGHT) != 0)
		{
			x = size_.width_ - len;
		}

		if ((align_ & LT_VCENTER) != 0)
		{
		
			y = (size_.height_ - height) / 2.0f;
		}

		if ((align_ & LT_BOTTOM) != 0)
		{
			y = size_.height_ - height ;
		}

        font_->draw_string(x + pt.x_ , y + pt.y_ , text_.c_str(), color_);
	}
	else
	{
		for (Text_Rows::iterator i = text_rows_.begin(); i != text_rows_.end(); ++i)
		{
			font_->draw_string(x + pt.x_ , y + pt.y_ , (*i).c_str(), color_);
			y += font_->get_height();
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

