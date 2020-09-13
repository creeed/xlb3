#ifndef __XLBE_TEXT_H__
#define __XLBE_TEXT_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "rak/functional_fun.h"

#include "XlbeWidget.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

#define LT_TOP                      0x00000000
#define LT_LEFT                     0x00000000
#define LT_CENTER                   0x00000001
#define LT_RIGHT                    0x00000002
#define LT_VCENTER                  0x00000004
#define LT_BOTTOM                   0x00000008

class Image;

//////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Text : public Widget
{
public:
	typedef std::vector<std::string> Text_Rows;
    typedef rak::function_base1<bool, Text*> *Slot_Func;

public:
    Text(const std::string &name, Widget_Manager *creator) ;
    virtual ~Text() ;

public:
	virtual void set_slot(Slot_Func solt) { slot_func_ = solt; }
    virtual void set_image(const std::string &image);
	virtual void set_text(const std::string& text);
	virtual void set_text_color(const Color_Rect &color) { color_ = color; }

    virtual uint32_t get_format() { return format_; }
    virtual uint32_t set_format(uint32_t format) { uint32_t old=format_; format_=format;  return old; }

public:
	virtual void on_got_focus();
	virtual void on_lost_focus();	

    virtual void on_mouse_enter(const Point &pt);
    virtual void on_mouse_exit(const Point &pt);
    virtual void on_mouse_down(const Point &pt, Mouse_ButtonID button_id, int click_count);
    virtual void on_mouse_up(const Point &pt, Mouse_ButtonID button_id, int click_count);

    virtual void draw();

private:
    std::string text_;

	uint32_t format_;
	Color_Rect color_;
	Image *image_;

    Slot_Func slot_func_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif