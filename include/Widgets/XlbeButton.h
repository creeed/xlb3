#ifndef __XLBE_BUTTON_H__
#define __XLBE_BUTTON_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "rak/functional_fun.h"

#include "XlbeWindow.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Button : public Window
{
public:
    Button(const std::string &name) ;
    virtual ~Button() ;

public:
    void set_normal_image(const std::string &image);
	void set_over_image(const std::string &image);
	void set_push_image(const std::string &image);
	void set_disabled_image(const std::string &image);

public:
	virtual void on_got_focus();
	virtual void on_lost_focus();	

    virtual void on_mouse_enter(const Point &pt);
    virtual void on_mouse_exit(const Point &pt);
    virtual void on_mouse_down(const Point &pt, Mouse_ButtonID button_id, int click_count);
    virtual void on_mouse_up(const Point &pt, Mouse_ButtonID button_id, int click_count);

    virtual void draw();

protected:
    bool over_;
    bool push_;

	Sprite *spr_normal_;
	Sprite *spr_over_;
	Sprite *spr_push_;
	Sprite *spr_disabled_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif