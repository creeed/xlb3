#ifndef __XLBE_IMAGE_H__
#define __XLBE_IMAGE_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

/////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"

#include "XlbeRect.h"
#include "XlbeColorRect.h"
#include "XlberenderPrimitive.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

class Imageset;

/////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Image
{
public:
    Image();
    Image(Imageset *owner, const std::string &name, const Rect &area);
    Image(const Image &image);
    ~Image();

public:
    const std::string &get_name() const { return name_; }
    void set_name(const std::string &name) { name_ = name; } 

    std::string imageset_name() const ;
    const Imageset*	get_imageset(void) const ;

    Rect get_area() const { return area_; }
    void set_area(const Rect &area)  { area_ = area; }

	Size get_size() const { return area_.get_size(); }
    float get_width() const { return area_.get_width(); }
    float get_height() const { return area_.get_height(); }

    void draw(const Point &pos);
    void draw(const Point &pos, const Color_Rect& colors);
    void draw(const Point &pos, const Color_Rect& colors, Render_Blend blend);
    void draw(const Point &pos, const Size &size);
    void draw(const Point &pos, const Size &size, const Color_Rect& colors, Render_Blend blend);
    void draw(const Point &pos, const Size &size, const Point &src_pos, const Size &src_size);
    void draw(const Point &pos, const Size &size, const Point &src_pos, const Size &src_size, const Color_Rect& colors, Render_Blend blend);

    void draw(const Point dest[4], const Point src[4], const Color_Rect& colors, Render_Blend blend, float zbuffer = 0.0f);

public:
    std::string name_; 
    Rect area_;
    Imageset *owner_;
};

/////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif