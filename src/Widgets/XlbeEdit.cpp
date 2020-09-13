#include "XlbeException.h"
#include "XlbeEdit.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

#define	SINGLELINE	(flag_ & ES_SINGLELINE)

//////////////////////////////////////////////////////////////////////////////////////////////////////
Edit::Edit(const std::string &name) : Window(name)
{
	caret_pos_ = 0;
	caret_line_index_ = 0;			
    format_ = 0;
	text_pos_ = 0;
	limit_text_ = 1024;
}

Edit::~Edit() 
{
}

void Edit::update(float ftime, float dt)
{
	Window::update(ftime, dt);
}

void Edit::draw()
{
	if (!is_visible())
		return ;

	Point pt = get_absolute_position() ;

	if (format_ & ES_HAVE_FOCUS)
	{
		int caret_width = font_->get_string_width("©¦");
		int caret_height = font_->get_height();

		if (caret_pos_ == 0)
		{
		    font_->draw_string(pt.x_ - caret_width / 2.0f, pt.y_,  "©¦",  color_, 0);
		}
		else
		{
			font_->draw_string(pt.x_ - caret_width / 2.0f + font_->get_string_width(text_.substr(0, text_pos_).c_str()), pt.y_, 
				"©¦",  color_, 0);
		}
	}

	if (format_ & ES_MASK_CHARACTER)
	{
		if (mask_text_.size() != text_.size())
		{
			mask_text_.assign(text_.size(), '*');
		}

	   font_->draw_string(pt.x_, pt.y_,  mask_text_.c_str(), color_, 0);
	}
	else
	{
		font_->draw_string(pt.x_, pt.y_,  text_.c_str(), color_, 0);
	}

	Window::draw();
}

void Edit::on_got_focus()
{
	format_ |= ES_HAVE_FOCUS;
}

void Edit::on_lost_focus()
{
    format_ &= ~ES_HAVE_FOCUS;
}

void Edit::on_mouse_down(const Point &pt, Mouse_ButtonID button_id, int click_count)
{
	
}

void Edit::on_key_down(Key_Code key)
{
	if (key == KEYCODE_LEFT)
	{
		if (text_pos_)
		{
		    if (text_[text_pos_ - 1] < 0)
			{
				text_pos_ -= 2;
				caret_pos_--;
			}
			else
			{
			    text_pos_--;
				caret_pos_--;
			}

		}
	}

	else if (key == KEYCODE_RIGHT)
	{
		if (text_pos_ < text_.size())
		{
			if (text_[text_pos_] < 0)
			{
				text_pos_ += 2;
				caret_pos_++;
			}
			else
			{
				text_pos_ ++;
				caret_pos_++;
			}
		}
	}	
}

void Edit::on_key_char(int c)
{
	if ((format_ & ES_HAVE_FOCUS) && is_enabled())
	{
		insert_char(c);
	}
}


int Edit::insert_char(int c)
{
	if (c > 0x80)	
	{
		if (format_ & ES_IME_AVAILABLE)
		{
	       return (insert_char((char)(c & 0xff), (char)(c >> 8)));
		}
	}
	if (c == KEYCODE_BACK)	
	{
		if (text_pos_)
		{
			if (text_pos_ > 1 && text_[text_pos_ - 2] < 0)
			{
			    text_.erase(text_pos_ - 2, 2);
				text_pos_-= 2;
				caret_pos_--;
			}
			else
			{
				text_.erase(text_pos_ - 1, 1);
				text_pos_--;
				caret_pos_--;
			}

			return true;
		}
	}
	else if (c >= ' ' && c <= '~')
	{
		 return (insert_char((char)(c & 0xff), 0));
	}

	return false;
}

int	Edit::insert_char(char low, char high)
{
	int	len = high ? 2 : 1;

	if (text_.size() + len <= limit_text_)
	{
		if (high)
		{
			text_.insert(caret_pos_, 1, high);
			text_pos_ ++;
		}

		text_.insert(caret_pos_, 1, low);
		caret_pos_ ++;
		text_pos_ ++;
	}

	return 1;
}

void Edit::set_text(const std::string& text) 
{
	if (text.size() > limit_text_)
	{
		Window::set_text(text.substr(0, limit_text_));
	}
	else
	{
		Window::set_text(text);
	}	

	caret_pos_ = 0;
	text_pos_ = 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
}


