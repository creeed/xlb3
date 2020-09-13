#ifndef __XLBE_COLOR_RECT_H__
#define __XLBE_COLOR_RECT_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

///////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbeColor.h"

///////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

///////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Color_Rect 
{
public:
    Color_Rect() {}
    Color_Rect(const Color& col) { top_left_ = top_right_= bottom_left_ = bottom_right_ = col; }
    Color_Rect(const Color& top_left, const Color& top_right, const Color& bottom_left, const Color& bottom_right)
    { top_left_  = top_left; top_right_= top_right; bottom_left_ = bottom_left; bottom_right_ = bottom_right;}

public:
    void set_alpha(int alpha) { top_left_[3] = top_right_[3] = bottom_left_[3] = bottom_right_[3] = alpha;}
    void set_color(const Color& col) { top_left_ = top_right_= bottom_left_ = bottom_right_ = col; }

public:
    Color top_left_;
    Color top_right_;
    Color bottom_left_;
    Color bottom_right_;
};

///////////////////////////////////////////////////////////////////////////////////////////////
}
#endif
