#ifndef __XLBE_COLOR_H__
#define __XLBE_COLOR_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Color 
{
public:
    Color();
    Color(int color);
    Color(int color, int alpha);
    Color(int red, int green, int blue);
    Color(int red, int green, int blue, int alpha);

public:
    int red() const;
    int green() const;
    int blue() const;
    int alpha() const;

    unsigned long toint() const;

    int& operator[] (int index);
    int operator[] (int index) const;	

public:
    int red_;
    int green_;
    int blue_;
    int alpha_;
};

////////////////////////////////////////////////////////////////////////////////////////////
inline Color::Color()
:red_(0xFF),
green_(0xFF),
blue_(0xFF),
alpha_(0xFF)
{
}

inline Color::Color(int color)
:alpha_((color >> 24) & 0xFF),
red_((color >> 16) & 0xFF),
green_((color >> 8) & 0xFF),
blue_(color & 0xFF)
{
    if (alpha_ == 0)
    {
        alpha_ = 255;
    }
}

inline Color::Color(int color, int alpha)
:red_((color >> 16) & 0xFF),
green_((color >> 8) & 0xFF),
blue_(color & 0xFF),
alpha_(alpha)
{
}

inline Color::Color(int red, int green, int blue)
:red_(red),
green_(green),
blue_(blue),
alpha_(0xFF)
{
}

inline Color::Color(int red, int green, int blue, int alpha)
:red_(red),
green_(green),
blue_(blue),
alpha_(alpha)
{
}


inline int Color::red() const
{
    return red_;
}

inline int Color::green() const
{
    return green_;
}

inline int Color::blue() const
{
    return blue_;
}

inline int Color::alpha() const
{
    return alpha_;
}

inline unsigned long Color::toint() const
{
    return (alpha_ << 24) | (red_ << 16) | (green_ << 8) | (blue_);
}

inline int& Color::operator[] (int index)
{
    static int junk = 0;

    switch (index)
    {
    case 0:
        return red_;
    case 1:
        return green_;
    case 2:
        return blue_;
    case 3:
        return alpha_;
    default:
        return junk;
    }
}

inline int Color::operator[] (int index) const
{
    switch (index)
    {
    case 0:
        return red_;
    case 1:
        return green_;
    case 2:
        return blue_;
    case 3:
        return alpha_;
    default:
        return 0;
    }
}

inline bool operator== (const Color& color1, const Color& color2)
{
    return 
        (color1.red_ == color2.red_) &&
        (color1.green_ == color2.green_) &&
        (color1.blue_ == color2.blue_) && 
        (color1.alpha_ == color2.alpha_);
}

inline bool operator!= (const Color& color1, const Color& color2)
{
    return 
        (color1.red_ != color2.red_) ||
        (color1.green_ != color2.green_) ||
        (color1.blue_ != color2.blue_) ||
        (color1.alpha_ != color2.alpha_);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif
