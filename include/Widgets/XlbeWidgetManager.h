#ifndef __XLBE_WIDGET_MANAGER_H__
#define __XLBE_WIDGET_MANAGER_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeRect.h"
#include "XlbeInput.h"
#include "XlbeWidget.h"
#include "XlbeFocusHandler.h"
#include "XlbeWidgetListener.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

class Widget;

//////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Widget_Manager : public Singleton<Widget_Manager>
{
public:
	typedef std::list<Input_Event> Inputs;
	typedef std::map<std::string, Widget*, xlbe_utility::fast_less_compare> Widgets;
    typedef std::vector<Widget_Listener *> Widget_Listeners;
	typedef std::queue<Widget_Massage *> Async_Widget_Massages;

public:
    Widget_Manager();
    ~Widget_Manager();

	static Widget_Manager* singleton();

public:
	void regist_widget(Widget *widget);
    Widget* get_widget(const std::string& name);

	Widget *get_root_widget() const;
	void set_root_widget(Widget* root);

	Widget* get_widget_at(int x, int y);
    Widget* get_mouse_event_source(int x, int y);
    Widget* get_key_event_source();
	Widget* get_mouse_widget() { return mouse_widget_; }

	void focus_none() { focus_handler_->focus_none(); }

public:
	void add_widget_listener(Widget_Listener* listener);
    void remove_widget_listener(Widget_Listener* listener);

    void send_notify(Widget_Massage& msg, bool async = false);
	void send_notify(Widget* widget, const std::string &message, WPARAM wparam = 0, LPARAM lparam = 0, bool async = false);

public:
	void push_input(Input_Event ie);
	void pop_input(Input_Event &ie);
	void process_input();

	bool is_key_down(Key_Code key);
	bool is_left_button_down();
	bool is_middle_button_down();
	bool is_right_button_down();

    void handle_key_char(char c);
    void handle_key_down(Key_Code key);
    void handle_key_up(Key_Code key);
    void handle_mouse_move(float x, float y);
    void handle_mouse_down(float x, float y, Mouse_ButtonID button_id, int click_count);
    void handle_mouse_up(float x, float y, Mouse_ButtonID button_id, int click_count);
	void handle_mouse_wheel(float x, float y, int delta);

    void on_key_char(char c);
    void on_key_down(Key_Code key);
    void on_key_up(Key_Code key);
    void on_mouse_move(const Point &pt);
    void on_mouse_down(const Point &pt, Mouse_ButtonID button_id, int click_count);
    void on_mouse_up(const Point &pt, Mouse_ButtonID button_id, int click_count);
	void on_mouse_wheel(const Point &pt, int delta);

public:
	void clear_widget();

    void update(float ftime, float dt);
    void draw();

private:
	Inputs inputs_;
	int	down_buttons_;
	bool key_down[0xFF];
    
    Widgets widgets_;
    Widget* root_widget_;
	 Widget* mouse_widget_;
    Focus_Handler* focus_handler_;

	Widget_Listeners widget_listeners_;
	Async_Widget_Massages async_widget_massages_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif