#include "XlbeException.h"
#include "XlbeRect.h"
#include "XlbeRoot.h"
#include "XlbeSprite.h"
#include "XlbeSpriteResource.h"
#include "XlbeSpriteResourceManager.h"
#include "XlbeMouseCursor.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {	

template<> Mouse_Cursor* Singleton<Mouse_Cursor>::singleton_ = 0;
Mouse_Cursor* Mouse_Cursor::singleton()
{
    return singleton_;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
Mouse_Cursor::Mouse_Cursor()
{
    Rect screen_area (Root::singleton()->render_system()->get_geometry_rect());

    position_.x_ = screen_area.get_width() / 2;
    position_.y_ = screen_area.get_height() / 2;

    set_constraint_area(&screen_area);

    visible_ = true;
	spr_cursor_ = new Sprite("MouseCursor");
	spr_cursor_->set_hot(Point(0, 0));
}

Mouse_Cursor::~Mouse_Cursor()
{
}

void Mouse_Cursor::set_cursor(const std::string& spr_res)
{
	if (spr_res.empty())
		return;

	Sprite_Resource *res = (Sprite_Resource *)Sprite_Resource_Manager::singleton()->get_resource(spr_res);
	spr_cursor_->set_sprite_resource(res);
}

void Mouse_Cursor::set_position(const Point& position)
{
    position_= position;
    
    constrain_position();
}

void Mouse_Cursor::offset_position(const Point& offset)
{
    position_ += offset;

    constrain_position();
}

Rect Mouse_Cursor::get_constraint_area() const
{
    return constraints_;
}

void Mouse_Cursor::set_constraint_area(const Rect* area)
{
	Rect screen_area (Root::singleton()->render_system()->get_geometry_rect());

    if (!area)
    {
        constraints_ = screen_area;
    }
    else 
    {
        constraints_ = *area;
    }

    constrain_position();
}

void Mouse_Cursor::constrain_position()
{
    Rect absarea(get_constraint_area());

    if (position_.x_ >= absarea.right_)
        position_.x_ = absarea.right_ -1;

    if (position_.y_>= absarea.bottom_)
        position_.y_= absarea.bottom_ -1;

    if (position_.y_< absarea.top_)
        position_.y_ = absarea.top_;

    if (position_.x_ < absarea.left_)
        position_.x_ = absarea.left_;
}

void Mouse_Cursor::draw() 
{
    if (visible_)
    {
		Point pt;
		pt = position_ - centrepoint_;

		if (spr_cursor_->get_sprite_resource())
		{
			spr_cursor_->set_position(pt);
			spr_cursor_->set_size(spr_cursor_->get_sprite_resource()->get_texture_size());
			spr_cursor_->draw();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////
}
