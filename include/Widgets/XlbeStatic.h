#ifndef __XLBE_STATIC_H__
#define __XLBE_STATIC_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"

#include "XlbeWindow.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

#define LT_TOP                      0x00000000
#define LT_LEFT                     0x00000000
#define LT_CENTER                   0x00000001
#define LT_RIGHT                    0x00000002
#define LT_VCENTER                  0x00000004
#define LT_BOTTOM                   0x00000008
#define LT_WORDBREAK                0x00000016

//////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Static : public Window
{
public:
	typedef std::vector<std::string> Text_Rows;

public:
    Static(const std::string &name) ;
    virtual ~Static() ;

public:
	virtual void set_font(const std::string &font) ;
	virtual void set_size(const Size &size) ;
	virtual void set_text(const std::string& text);
	virtual void set_text_color(const Color &color) { color_ = color; }

    virtual uint32_t get_align() { return align_; }
    virtual uint32_t set_align(uint32_t align) { uint32_t old = align_; align_= align;  return old; }

public:
	virtual void on_got_focus();
	virtual void on_lost_focus();	

    virtual void on_mouse_enter(const Point &pt);
    virtual void on_mouse_exit(const Point &pt);
    virtual void on_mouse_down(const Point &pt, Mouse_ButtonID button_id, int click_count);
    virtual void on_mouse_up(const Point &pt, Mouse_ButtonID button_id, int click_count);

    virtual void draw();

protected:
	void adjust_text();

private:
	bool text_changed_;

	uint32_t align_;
	Color_Rect color_;
	Text_Rows text_rows_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif