#include "XlbeException.h"
#include "XlbeRect.h"

///////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

///////////////////////////////////////////////////////////////////////////////////////////////
Rect::Rect()
:top_(0),
bottom_(0),
left_(0),
right_(0)
{
}

Rect::Rect(const Point &point, const Size &size)
:top_(point.y_),
bottom_(point.y_ + size.height_),
left_(point.x_),
right_(point.x_ + size.width_)
{
}

Rect::Rect(float left, float top, float right, float bottom)
:top_(top),
bottom_(bottom),
left_(left),
right_(right)
{
}

Rect::Rect(const Rect& rect)
:top_(rect.top_),
bottom_(rect.bottom_),
left_(rect.left_),
right_(rect.right_)
{
}

void Rect::set_position(const Point& pt)
{
	Size sz(get_size());

	left_ = pt.x_;
    top_  = pt.y_;

	set_size(sz);
}

void Rect::set_rect(float left, float top, float right, float bottom)
{
    top_ = top;
    bottom_ = bottom;
    left_ = left;
    right_ = right;
} 

void Rect::set_rect(const Point &point, const Size &size)
{
    top_ = point.y_;
    bottom_ = point.y_ + size.height_;
    left_ = point.x_;
    right_ = point.x_ + size.width_;
} 

void Rect::offset_rect(float x, float y)
{
    top_ += y;
    bottom_ += y;
    left_ += x;
    right_ += x;
}

void Rect::offset_rect(const Size &size)
{
    top_ += size.height_;
    bottom_ += size.height_;
    left_ += size.width_ ;
    right_ += size.width_ ;
}

bool Rect::pt_in_rect(const Point& point) const
{
	if ((left_ > point.x_) ||
		(right_ <= point.x_) ||
		(top_ > point.y_) ||
		(bottom_ <= point.y_))
	{
		return false;
	}

	return true;
}

Rect Rect::intersection_rect(const Rect& rect) const
{
	if ((right_ > rect.left_) &&
		(left_ < rect.right_) &&
		(bottom_ > rect.top_) &&
		(top_ < rect.bottom_))
	{
		Rect temp;

		temp.left_ = (left_ > rect.left_) ? left_ : rect.left_;
		temp.right_ = (right_ < rect.right_) ? right_ : rect.right_;
		temp.top_ = (top_ > rect.top_) ? top_ : rect.top_;
		temp.bottom_ = (bottom_ < rect.bottom_) ? bottom_ : rect.bottom_;

		return temp;
	}
	else
	{
		return Rect(0.0f, 0.0f, 0.0f, 0.0f);
	}

}

//Rect Rect::union_rect(const Rect& rect) const 
//{
//}
//
//Rect Rect::subtract_rect(const Rect& rect) const 
//{
//}




	

///////////////////////////////////////////////////////////////////////////////////////////////
}