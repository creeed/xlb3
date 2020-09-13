#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeWidget.h"
#include "XlbeWidgetManager.h"
#include "XlbeMouseCursor.h"
#include "XlbeRenderSystemD3d9.h"

////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

template<> Widget_Manager* Singleton<Widget_Manager>::singleton_ = 0;
Widget_Manager* Widget_Manager::singleton()
{
    return singleton_;
}

////////////////////////////////////////////////////////////////////////////////////////////
Widget_Manager::Widget_Manager()
:down_buttons_(0)
{
    for (int i = 0; i < 0xFF; i++)
		key_down[i] = false;

	root_widget_ = 0;
	mouse_widget_ = 0;
	focus_handler_ = new Focus_Handler();
}

Widget_Manager::~Widget_Manager()
{
    clear_widget();
}

void Widget_Manager::clear_widget()
{
	widgets_.clear();
	SAFE_DELETE(focus_handler_);
}

void Widget_Manager::regist_widget(Widget *widget)
{
    if (widgets_.find(widget->get_name()) != widgets_.end())
        throw_scene_error(widget->get_name() + " widget already exists.");

	widget->set_focus_handler(focus_handler_);
    widgets_[widget->get_name()] = widget;

}

Widget* Widget_Manager::get_widget(const std::string& name)
{
    Widgets::const_iterator i = widgets_.find(name);

    if (i == widgets_.end())
        throw_scene_error(name + " widget not found.");

    return i->second;
}

void Widget_Manager::set_root_widget(Widget* root)
{
	if (root_widget_ != NULL)
	{
		root_widget_->set_focus_handler(NULL);
	}
	if (root != NULL)
	{
		root->set_focus_handler(focus_handler_);
	}

	root_widget_ = root;
}

Widget* Widget_Manager::get_root_widget() const
{
	return root_widget_;
}

Widget* Widget_Manager::get_widget_at(int x, int y)
{
	Widget* parent = root_widget_;
	Widget* child = root_widget_;

	while (child != NULL)
	{
		Widget* swap = child;

		Point pt = parent->get_absolute_position();
		child = parent->get_widget_at(x - pt.x_, y - pt.y_);

		parent = swap;
	}

	mouse_widget_ = parent;
	return parent;
}

Widget* Widget_Manager::get_mouse_event_source(int x, int y)
{
	Widget* widget = get_widget_at(x, y);

	if (focus_handler_->get_modal_focused() != 0 )
	{
		if (widget && widget->get_parent() && widget->get_parent() == focus_handler_->get_modal_focused())
			return widget;
		else
		    return focus_handler_->get_modal_focused();
	}

	return widget;
}

Widget* Widget_Manager::get_key_event_source()
{
	Widget* widget = focus_handler_->get_focused();

	if (focus_handler_->get_modal_focused() != 0 )
	{
		if (widget && widget->get_parent() && widget->get_parent() == focus_handler_->get_modal_focused())
			return widget;
		else
		    return focus_handler_->get_modal_focused();
	}

	return widget;
}

bool Widget_Manager::is_key_down(Key_Code key)
{
	return key_down[key] ;
}

bool Widget_Manager::is_left_button_down()
{
	return (down_buttons_ & 1) ? true : false;
}

bool Widget_Manager::is_middle_button_down()
{
	return (down_buttons_ & 4) ? true : false;
}

bool Widget_Manager::is_right_button_down()
{
	return (down_buttons_ & 2) ? true : false;
}

void Widget_Manager::update(float ftime, float dt)
{
	//process_input();

	if (root_widget_)
		root_widget_->update(ftime, dt);
}

void Widget_Manager::draw()
{
	if (root_widget_)
	{
		root_widget_->draw();
	}

	while(!async_widget_massages_.empty())
	{
		Widget_Massage *async = async_widget_massages_.front();

		Widget_Listeners::iterator i = widget_listeners_.begin();
		for (; i!=widget_listeners_.end(); ++i)
		{
			(*i)->notify(*async);
		}

		delete async;
		async_widget_massages_.pop();
	}
}

void Widget_Manager::push_input(Input_Event ie)
{
	inputs_.push_back(ie);
}

void Widget_Manager::pop_input(Input_Event &ie)
{
	if (inputs_.empty())
	{
		ie.type_ = INPUT_NULL;
		return;
	}

	ie = inputs_.front();
	inputs_.pop_front();
}

void Widget_Manager::process_input()
{
	while (inputs_.size() > 0)
	{
	    Input_Event ie = inputs_.front();
	    inputs_.pop_front();

		switch (ie.type_)
		{
		case INPUT_MOUSEMOVE:
			{
				handle_mouse_move(ie.x_, ie.y_);
				break;
			}
		case INPUT_LBUTTONDOWN:
			{
				//SetCapture((HWND)ie.handle_);
				handle_mouse_down(ie.x_, ie.y_, MB_Left, 1);
				break;
			}
		case INPUT_RBUTTONDOWN:
			{
				//SetCapture((HWND)ie.handle_);
				handle_mouse_down(ie.x_, ie.y_, MB_Right, 1);
				break;
			}
		case INPUT_MBUTTONDOWN:
			{
				//SetCapture((HWND)ie.handle_);
				handle_mouse_down(ie.x_, ie.y_, MB_Middle, 1);
				break;
			}
		case INPUT_LBUTTONDBLCLK:
			{
				//SetCapture((HWND)ie.handle_);
				handle_mouse_down(ie.x_, ie.y_, MB_Left, 2);
				break;
			}
		case INPUT_RBUTTONDBLCLK:
			{
				//SetCapture((HWND)ie.handle_);
				handle_mouse_down(ie.x_, ie.y_, MB_Right, 2);
				break;
			}
		case INPUT_LBUTTONUP:	
			{
				if ((down_buttons_ & ~1) == 0)
				    ReleaseCapture();

				handle_mouse_up(ie.x_, ie.y_, MB_Left, 1);

				break;
			}
		case INPUT_RBUTTONUP:
			{
				if ((down_buttons_ & ~2) == 0)
				    ReleaseCapture();

				handle_mouse_up(ie.x_, ie.y_, MB_Right, 1);

				break;
			}
		case INPUT_MBUTTONUP:
			{
				if ((down_buttons_ & ~4) == 0)
				    ReleaseCapture();

				handle_mouse_up(ie.x_, ie.y_, MB_Middle, 1);
				break;
			}
		case INPUT_MOUSEWHEEL:
			{
				handle_mouse_wheel(ie.x_, ie.y_, ie.wheel_);
				break;
			}
		case INPUT_KEYDOWN:
		case INPUT_SYSKEYDOWN:
			{
				handle_key_down((Key_Code)ie.key_);
				break;
			}
		case INPUT_KEYUP:
		case INPUT_SYSKEYUP:
			{
				handle_key_up((Key_Code)ie.key_);
				break;
			}
		case INPUT_CHAR:
			{
				handle_key_char((char)ie.chr_);
				break;
			}
		}
	}
}

void Widget_Manager::handle_key_char(char c)
{
    on_key_char(c);
}

void Widget_Manager::handle_key_down(Key_Code key)
{
    on_key_down(key);
}

void Widget_Manager::handle_key_up(Key_Code key)
{
    on_key_up(key);
}

void Widget_Manager::handle_mouse_move(float x, float y)
{
    on_mouse_move(Point(x,y));
}

void Widget_Manager::handle_mouse_down(float x, float y, Mouse_ButtonID button_id, int click_count)
{
    on_mouse_down(Point(x,y), button_id, click_count);
}

void Widget_Manager::handle_mouse_up(float x, float y, Mouse_ButtonID button_id, int click_count)
{
    on_mouse_up(Point(x,y), button_id, click_count);
}

void Widget_Manager::handle_mouse_wheel(float x, float y, int delta)
{
    on_mouse_wheel(Point(x,y), delta);
}

void Widget_Manager::on_key_char(char c)
{
	if (!root_widget_)
		return;

    Widget* source_widget = focus_handler_->get_focused();
	if (source_widget)
	{
		if (!source_widget->is_focusable())
		{
			focus_handler_->focus_none();
		}
		else
		{                    
			source_widget->on_key_char(c);                   
		}
	}
}

void Widget_Manager::on_key_down(Key_Code key)
{
	if ((key >= 0) && (key < 0xFF))
		key_down[key] = true;

	if (!root_widget_)
		return;

    Widget* source_widget = focus_handler_->get_focused();
	if (source_widget)
	{
		if (!source_widget->is_focusable())
		{
			focus_handler_->focus_none();
		}
		else
		{                    
			source_widget->on_key_down(key);                   
		}
	}
}

void Widget_Manager::on_key_up(Key_Code key)
{
	if ((key >= 0) && (key < 0xFF))
		key_down[key] = false;

	if (!root_widget_)
		return;

    Widget* source_widget = focus_handler_->get_focused();
	if (source_widget)
	{
		if (!source_widget->is_focusable())
		{
			focus_handler_->focus_none();
		}
		else
		{                    
			source_widget->on_key_up(key);                   
		}
	}
}

void Widget_Manager::on_mouse_move(const Point &pt)
{
	if (!root_widget_)
		return;

	if (focus_handler_->get_last_widget_with_mouse() != 0 && !root_widget_->get_window_rect().pt_in_rect(pt))
	{
		focus_handler_->get_last_widget_with_mouse()->on_mouse_exit(pt);
		focus_handler_->set_last_widget_with_mouse(0);

		return;
	}

	Widget* source_widget = get_mouse_event_source(pt.x_, pt.y_);

	if (source_widget != focus_handler_->get_last_widget_with_mouse())
	{
		if (focus_handler_->get_last_widget_with_mouse() != NULL)
		{
            focus_handler_->get_last_widget_with_mouse()->on_mouse_exit(pt);
		}

		source_widget->on_mouse_enter(pt);
		focus_handler_->set_last_widget_with_mouse(source_widget);
	}

	if (focus_handler_->get_dragged_widget() != NULL)
	{
		focus_handler_->get_dragged_widget()->on_mouse_drag(pt);
	}
	else
	{
		source_widget->on_mouse_move(pt);
	}
}

void Widget_Manager::on_mouse_down(const Point &pt, Mouse_ButtonID button_id, int click_count)
{
	if (button_id == MB_Right)
	{
		down_buttons_ |= 0x02;
	}
	else if (button_id == MB_Middle)
	{
		down_buttons_ |= 0x04;
	}
	else
	{
		down_buttons_ |= 0x01;
	}

	if (!root_widget_)
		return;

	Widget* source_widget = get_mouse_event_source(pt.x_, pt.y_);

	if (focus_handler_->get_dragged_widget() != NULL)
	{
		source_widget = focus_handler_->get_dragged_widget();
	}

	source_widget->request_focus();
	source_widget->on_mouse_down(pt, button_id, click_count);
	
	focus_handler_->set_last_widget_pressed(source_widget);
	focus_handler_->set_dragged_widget(source_widget);
}

void Widget_Manager::on_mouse_up(const Point &pt, Mouse_ButtonID button_id, int click_count)
{
	int mask;
	
	if (button_id == MB_Right)
		mask = 0x02;
	else if (button_id == MB_Middle)
		mask = 0x04;
	else
		mask = 0x01;

	down_buttons_ &= ~mask;	

	if (!root_widget_)
		return;

	Widget* source_widget = get_mouse_event_source(pt.x_, pt.y_);

	if (focus_handler_->get_dragged_widget() != NULL)
	{
		if (source_widget != focus_handler_->get_last_widget_pressed())
		{
			focus_handler_->set_last_widget_pressed(NULL);
		}

		source_widget = focus_handler_->get_dragged_widget();
	}

	source_widget->on_mouse_up(pt, button_id, click_count);

	if (focus_handler_->get_dragged_widget() != NULL)
	{
		focus_handler_->set_dragged_widget(NULL);
	}
}

void Widget_Manager::on_mouse_wheel(const Point &pt, int delta)
{
	if (!root_widget_)
		return;

	Widget* source_widget = get_mouse_event_source(pt.x_, pt.y_);

	if (focus_handler_->get_dragged_widget() != NULL)
	{
		source_widget = focus_handler_->get_dragged_widget();
	}

	source_widget->on_mouse_wheel(pt, delta);
}


void Widget_Manager::add_widget_listener(Widget_Listener *listener)
{
    widget_listeners_.push_back(listener);
}

void Widget_Manager::remove_widget_listener(Widget_Listener *listener)
{
    Widget_Listeners::iterator i = widget_listeners_.begin();
    for (; i!=widget_listeners_.end(); ++i)
    {
        if ((*i) == listener)
        {
            widget_listeners_.erase(i);
            return;
        }
    }
}

void Widget_Manager::send_notify(Widget_Massage& msg, bool async)
{
	if (async)
	{
		Widget_Listeners::iterator i = widget_listeners_.begin();
		for (; i!=widget_listeners_.end(); ++i)
		{
			(*i)->notify(msg);
		}
	}
	else
	{
		Widget_Massage *pmsg = new Widget_Massage;
		pmsg->type_ = msg.type_;
		pmsg->sender_ = msg.sender_;
		pmsg->wparam_ = msg.wparam_;
		pmsg->lparam_ = msg.lparam_;

		async_widget_massages_.push(pmsg);
	}
}

void Widget_Manager::send_notify(Widget* widget, const std::string &message, WPARAM wparam , LPARAM lparam , bool async )
{
	Widget_Massage msg;
	msg.type_ = message;
	msg.sender_ = widget;
	msg.wparam_ = wparam;
	msg.lparam_ = lparam;

    send_notify(msg, async);
}

////////////////////////////////////////////////////////////////////////////////////////////

}