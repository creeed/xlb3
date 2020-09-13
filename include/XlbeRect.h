#ifndef __XLBE_RECT_H__
#define __XLBE_RECT_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

///////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePoint.h"
#include "XlbeSize.h"

///////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

///////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Rect 
{
public:
    Rect();
    Rect(const Point &point, const Size &size);
    Rect(float left, float top, float right, float bottom);
    Rect(const Rect& rect);

    Point get_position() const { return Point(left_, top_); }
    void set_position(const Point& pt);

    float get_width() const { return right_ - left_; }
    void set_width(float width) { right_ = left_ + width; }

    float get_height() const {return bottom_ - top_; }
    void set_height(float height) { bottom_ = top_ + height;}

    Size get_size() const { return Size(get_width(), get_height());}
    void set_size(const Size& size)	{ set_width(size.width_); set_height(size.height_); }

    void set_rect(float left, float top, float right, float bottom); 
    void set_rect(const Point &point, const Size &size); 

    void offset_rect(float x, float y);
    void offset_rect(const Size &size);

    bool pt_in_rect(const Point& point) const;
    bool is_empty() const { return (get_width() == 0.0f && get_height() == 0.0f); }

    Rect intersection_rect(const Rect& rect) const;
    //Rect union_rect(const Rect& rect) const ;
    //Rect subtract_rect(const Rect& rect) const ;

    Rect& operator = (const Rect& rhs) 
    {
	    left_ = rhs.left_;
	    top_ = rhs.top_;
	    right_ = rhs.right_;
	    bottom_ = rhs.bottom_;

	    return *this;
    }

    bool operator == (const Rect& rhs) const 	
    {
		return ((left_ == rhs.left_) && (right_ == rhs.right_) && (top_ == rhs.top_) && (bottom_ == rhs.bottom_));
	}
    bool operator != (const Rect& rhs) const { return !operator==(rhs); }

public:
    float left_, top_, right_, bottom_;
};

///////////////////////////////////////////////////////////////////////////////////////////////
}
#endif