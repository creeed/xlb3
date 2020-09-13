#ifndef __XLBE_PROGRESS_H__
#define __XLBE_PROGRESS_H__

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

class Image;

//////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Progress : public Window
{
public:
    Progress(const std::string &name) ;
    virtual ~Progress() ;

public:
	virtual float get_value() const { return value_; }
    virtual void set_value(float value);

    void set_track_image(const std::string &image);
	void set_step_image(const std::string &image);

public:
	virtual void on_got_focus();
	virtual void on_lost_focus();	

    virtual void on_mouse_enter(const Point &pt);
    virtual void on_mouse_exit(const Point &pt);
    virtual void on_mouse_down(const Point &pt, Mouse_ButtonID button_id, int click_count);
    virtual void on_mouse_up(const Point &pt, Mouse_ButtonID button_id, int click_count);

    virtual void draw();

public:


protected:
    bool over_;
    bool down_;

    float value_;

    Sprite *spr_track_;
    Sprite *spr_step_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif