#ifndef __XLBE_FOCUS_HANDLER_H__
#define __XLBE_FOCUS_HANDLER_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

class XlbeWidget;

//////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Focus_Handler
{
public:
	typedef std::vector<Widget*> Widgets;
	typedef Widgets::iterator WidgetsIterator;

public:
	Focus_Handler() ;
	virtual ~Focus_Handler() ;

public:
	virtual Widget* get_focused() const { return focused_widget_; }
	virtual bool is_focused(const Widget* widget) const { return focused_widget_ == widget ;}

	virtual void focus_none() ;

	virtual Widget* get_dragged_widget() { return dragged_widget_; }
	virtual void set_dragged_widget(Widget* widget) { dragged_widget_ = widget; }

	virtual Widget* get_last_widget_with_mouse() { return last_widget_with_mouse_; }
	virtual void set_last_widget_with_mouse(Widget* widget) { last_widget_with_mouse_ = widget; }

	virtual Widget* get_last_widget_pressed() { return last_widget_pressed_; }
	virtual void set_last_widget_pressed(Widget* widget) { last_widget_pressed_ = widget; }

    virtual void add(Widget* widget);
    virtual void remove(Widget* widget);

	void request_focus(Widget* widget);

	Widget* get_modal_focused() const { return modal_focused_widget_; }
	void request_modal_focus(Widget *widget);
	void release_modal_focus(Widget *widget);

private:
	Widget* focused_widget_;
	Widget* modal_focused_widget_;

	Widget* dragged_widget_;
	Widget* last_widget_with_mouse_;
	Widget* last_widget_pressed_;

	Widgets widgets_;
	WidgetsIterator widgets_iterator_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif