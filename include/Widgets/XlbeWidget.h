#ifndef __XLBE_WIDGET_H__
#define __XLBE_WIDGET_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeRect.h"
#include "XlbeInput.h"
#include "XlbeFont.h"
#include "XlbeFontManager.h"
#include "XlbeNode.h"
#include "XlbeWidgetListener.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

class Widget_Manager;
class Focus_Handler;
class Sprite;

//////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Widget : public Node 
{
public:
    Widget(const std::string &name) ;
    virtual ~Widget() ;

	Focus_Handler* get_focus_handler() ;
	void set_focus_handler(Focus_Handler* focus_handler);

public:
    virtual void set_visible(bool visible);

	virtual bool is_enabled() const;
	virtual void set_enabled(bool enabled);

	virtual bool is_movable() const { return movable_; }
	virtual void set_movable(bool movable)  { movable_ = movable; }

	virtual bool is_focusable() const;
	virtual void set_focusable(bool focusable);

	virtual bool is_focused() const;
	virtual void request_focus();
    
	virtual void request_modal_focus();
	virtual void release_modal_focus();
	virtual bool has_modal_focus();

	virtual Font *get_font() const { return font_; }
	virtual void set_font(const std::string &font) ;

	virtual void set_text(const std::string& text) { text_  = text; }
	virtual const std::string& get_text()  { return text_; }

	virtual const Color_Rect &get_text_color() const { return color_; }
	virtual void set_text_color(const Color &color) { color_ = color; }

	virtual Rect get_window_rect() const { return Rect(position_, size_); }

public:
	virtual Widget *get_widget_at(int x, int y);

	virtual void move_to_top(Widget* widget);
	virtual void move_to_bottom(Widget* widget);

	virtual void insert_child(Node* child, int index = -1);
	virtual void remove_child(int index);
    virtual void remove_child(Node* child);
    virtual void remove_all_children();

public:
	virtual void on_got_focus();
	virtual void on_lost_focus();	

    virtual void on_key_char(char c);
    virtual void on_key_down(Key_Code key);
    virtual void on_key_up(Key_Code key);
    virtual void on_mouse_enter(const Point &pt);
    virtual void on_mouse_exit(const Point &pt);
    virtual void on_mouse_move(const Point &pt);
    virtual void on_mouse_down(const Point &pt, Mouse_ButtonID button_id, int click_count);
    virtual void on_mouse_up(const Point &pt, Mouse_ButtonID button_id, int click_count);
	virtual void on_mouse_wheel(const Point &pt, int delta);
    virtual void on_mouse_drag(const Point &pt);

protected:
	bool enabled_;
    bool movable_;
	bool focusable_;

	bool moving_;
	Point pt_drag_;

	Font *font_;
	std::string text_;
	Color_Rect color_;
	
	Focus_Handler* focus_handler_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif