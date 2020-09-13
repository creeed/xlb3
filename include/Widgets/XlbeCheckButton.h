#ifndef __XLBE_CHECK_BUTTON_H__
#define __XLBE_CHECK_BUTTON_H__

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
class Xlbe_Export Check_Button : public Widget
{
public:
    typedef rak::function_base1<bool, Check_Button*> *Slot_Func;

public:
    Check_Button(const std::string &name, Widget_Manager *creator) ;
    virtual ~Check_Button() ;

public:
	virtual void set_slot(Slot_Func solt) { slot_func_ = solt; }
    virtual void set_image(const std::string &button_image, const std::string &over_image,
		const std::string &down_image, const std::string &disabled_image,
		const std::string &check_button_image, const std::string &check_over_image,
		const std::string &check_down_image, const std::string &check_disabled_image);

	bool get_checked() const { return checked_; }
	void set_checked(bool checked) { checked_ = checked; }

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
    bool down_;
	bool checked_;

    Image* button_image_;
    Image* over_image_;
    Image* down_image_;	
    Image* push_image_;	
    Image* disabled_image_;

	Image* check_button_image_;
    Image* check_over_image_;
    Image* check_down_image_;	
    Image* check_push_image_;	
    Image* check_disabled_image_;

    Slot_Func slot_func_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif