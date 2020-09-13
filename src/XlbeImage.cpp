#include "XlbeRoot.h"
#include "XlbeImage.h"
#include "XlbeImageset.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

/////////////////////////////////////////////////////////////////////////////////////////////////////
Image::Image()
:owner_(0)
{
}

Image::Image(Imageset *owner, const std::string &name, const Rect &area)
:owner_(owner),
name_(name), 
area_(area)
{
}

Image::Image(const Image &image)
:owner_(image.owner_),
name_(image.name_), 
area_(image.area_)
{
}

Image::~Image()
{
}

std::string Image::imageset_name() const
{ 
    return owner_->get_name();
}

const Imageset*	Image::get_imageset() const 
{
    return owner_;
}

void Image::draw(const Point &pos)
{
    draw(pos, area_.get_size(), Point(0,0), area_.get_size(), Color_Rect(), BLEND_COLORMUL_ALPHABLEND);
}

void Image::draw(const Point &pos, const Color_Rect& colors)
{
    draw(pos, area_.get_size(), Point(0,0), area_.get_size(), colors, BLEND_COLORMUL_ALPHABLEND);
}

void Image::draw(const Point &pos, const Color_Rect& colors, Render_Blend blend)
{
    draw(pos, area_.get_size(), Point(0,0), area_.get_size(), colors, blend);
}

void Image::draw(const Point &pos, const Size &size)
{
    draw(pos, size, Point(0,0), area_.get_size(), Color_Rect(), BLEND_COLORMUL_ALPHABLEND);
}

void Image::draw(const Point &pos, const Size &size, const Color_Rect& colors, Render_Blend blend)
{
    draw(pos, size, Point(0,0), area_.get_size(), colors, blend);
}

void Image::draw(const Point &pos, const Size &size, const Point &src_pos, const Size &src_size)
{
    draw(pos, size, src_pos, src_size, Color_Rect(), BLEND_COLORMUL_ALPHABLEND);
}

void Image::draw(const Point &pos, const Size &size, const Point &src_pos, const Size &src_size, const Color_Rect& colors, Render_Blend blend)
{
    Point dest[4];
    Point src[4];

    float tx1, ty1, tx2, ty2;
    float x1, y1, x2, y2;

    tx1= (area_.left_+src_pos.x_)/owner_->get_native_size().width_;
    ty1 = (area_.top_+src_pos.y_)/owner_->get_native_size().height_;
    tx2= (area_.left_+src_pos.x_+src_size.width_)/owner_->get_native_size().width_; 
    ty2 = (area_.top_+src_pos.y_+src_size.height_)/owner_->get_native_size().height_;

    src[0].x_=tx1; src[0].y_=ty1; 
    src[1].x_=tx2; src[1].y_=ty1; 
    src[2].x_=tx2; src[2].y_=ty2; 
    src[3].x_=tx1; src[3].y_=ty2; 

    x1 = 0;
    y1 = 0;
    x2 = size.width_ ;
    y2 = size.height_; 

    dest[0].x_ =  x1 + pos.x_;
    dest[0].y_ =  y1 + pos.y_;

    dest[1].x_ =  x2 + pos.x_;
    dest[1].y_ =  y1 + pos.y_;

    dest[2].x_ =  x2 + pos.x_;
    dest[2].y_ =  y2 + pos.y_;

    dest[3].x_ =  x1 + pos.x_;
    dest[3].y_ =  y2 + pos.y_;

    draw(dest, src, colors, blend);
}

void Image::draw(const Point dest[4], const Point src[4], const Color_Rect& colors, Render_Blend blend, float zbuffer)
{
    owner_->draw(dest, src, colors, blend, zbuffer);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
}