#include "XlbeException.h"
#include "XlbeFont.h"
#include "XlbeLabel.h"

////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////
Label::Label(const std::string& name) 
: Node(name)
{
    format_ = 0;
    font_ = 0;

	spr_bk_ = new Sprite(name + "_Bk");
	spr_bk_->set_hot(Point(0, 0));
}

Label::~Label() 
{
}

Font *Label::get_font() const 
{
    return font_;
}

void Label::set_font(const std::string &font)
{
	if (font.empty())
		return;

    font_ = (Font *)Font_Manager::singleton()->get_resource(font);
}

void Label::set_bk_image(const std::string &image) 
{
	if (!image.empty())
        spr_bk_->set_sprite_resource(image);
}

void Label::set_text(const std::string &text)
{
	if (text_ != text)
	{
		text_ = text;
	}
}

void Label::draw()
{
	if (!visible_)
		return;

	Node::draw();

	float x = 0.0f, y = 0.0f;
	Point pt = get_absolute_position() ;

	if (spr_bk_->get_sprite_resource())
	{
		spr_bk_->set_position(get_absolute_position());
		spr_bk_->set_size(get_size());
		spr_bk_->draw();
	}

	if (font_)
	{
		std::string c(text_, 0, 1);
		int clen = font_->get_width();
		int len = font_->get_string_width(text_.c_str());
		int height = font_->get_height();

		if ((format_ & LT_CENTER) != 0)
		{
			if (rotation_ == M_PI)
			{
			    x = (size_.width_ + len) / 2.0f - clen;
			}
			else
			{
				x = (size_.width_ - len) / 2.0f ;
			}
		}
		if ((format_ & LT_RIGHT) != 0)
		{
			x = size_.width_ - len;
		}
		if ((format_ & LT_VCENTER) != 0)
		{
			y = (size_.height_ - height) / 2.0f;
		}
		if ((format_ & LT_BOTTOM) != 0)
		{
			y = size_.height_ - height ;
		}

		font_->draw_string(x + pt.x_, y + pt.y_, text_.c_str(), color_, rotation_);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
}
