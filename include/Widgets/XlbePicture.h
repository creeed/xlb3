#ifndef __XLBE_PICTURE_H__
#define __XLBE_PICTURE_H__

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

class Image;

//////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Picture : public Widget
{
public:
    typedef rak::function_base1<bool, Picture*> *Slot_Func;

public:
    Picture(const std::string &name, Widget_Manager *creator) ;
    virtual ~Picture() ;

public:
	virtual void set_slot(Slot_Func solt) { slot_func_ = solt; }
    virtual void set_image(const std::string &image);

public:
	virtual void on_got_focus();
	virtual void on_lost_focus();	

    virtual void on_mouse_enter(const Point &pt);
    virtual void on_mouse_exit(const Point &pt);
    virtual void on_mouse_down(const Point &pt, Mouse_ButtonID button_id, int click_count);
    virtual void on_mouse_up(const Point &pt, Mouse_ButtonID button_id, int click_count);

    virtual void draw();

protected:
    Image* image_;
    Slot_Func slot_func_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif