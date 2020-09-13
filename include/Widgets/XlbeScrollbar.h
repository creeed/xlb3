#ifndef __XLBE_SCROLLBAR_H__
#define __XLBE_SCROLLBAR_H__

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

class Button;

//////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Scrollbar : public Widget
{
public:
	typedef rak::function_base1<bool, Scrollbar*> *Slot_Func;

public:
	Scrollbar(const std::string &name, Widget_Manager *creator) ;
	virtual ~Scrollbar() ;

public:
	virtual void set_slot(Slot_Func solt) { slot_func_ = solt; }
	virtual void set_image(const std::string &track_image, const std::string &thumb_image);
	virtual void set_upbutton_image(const std::string &button_image, const std::string &over_image,
		const std::string &down_image, const std::string &disabled_image);
	virtual void set_downbutton_image(const std::string &button_image, const std::string &over_image,
		const std::string &down_image, const std::string &disabled_image);

	virtual void set_invis_if_no_scroll(bool invis_if_no_scroll);

	virtual float get_value() const { return value_; }
	virtual void set_value(float value);

	virtual float get_max_value() const { return max_value_; }
	virtual void set_max_value(float max_value);

	virtual float get_page_size() const { return page_size_; }
	virtual void set_page_size(float page_size);
	
	virtual void set_horizontal(bool horizontal);

	virtual float get_track_size();
	virtual float get_thumb_size();
	virtual float get_thumb_position();
	virtual void set_thumb_position(float position);

	virtual void clamp_value();
    virtual int thumb_compare(float x, float y);

	bool button_press(Button* button);

public:
	virtual void update(float dt);
	virtual void draw();

	virtual void on_got_focus();
	virtual void on_lost_focus();	

    virtual void on_mouse_enter(const Point &pt);
    virtual void on_mouse_exit(const Point &pt);
    virtual void on_mouse_down(const Point &pt, Mouse_ButtonID button_id, int click_count);
    virtual void on_mouse_up(const Point &pt, Mouse_ButtonID button_id, int click_count);
	virtual void on_mouse_drag(const Point &pt);


protected:
	Image* track_image_;
	Image* thumb_image_;
	Slot_Func slot_func_;

	Button *up_button_;
	Button *down_button_;

    bool invis_if_no_scroll_;

	float value_;
	float max_value_;
	float page_size_;
	bool horizontal_;

	bool pressed_on_thumb_;
	float mouse_down_thumb_pos_;

	float mouse_down_x_;
	float mouse_down_y_;
	float last_mouse_x_;
	float last_mouse_y_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif
