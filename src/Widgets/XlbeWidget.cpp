#include "XlbeException.h"
#include "XlbeWidget.h"
#include "XlbeFocusHandler.h"
#include "XlbeWidgetManager.h"
#include "XlbeFontManager.h"
#include "XlbeMouseCursor.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////////
Widget::Widget(const std::string &name)
: Node(name)
{
	font_ = 0;

	enabled_ = true;
    movable_ = false;
	focusable_ = true;

	moving_ = false;

	hot_ = Point(0, 0);

	focus_handler_ = 0;
	Widget_Manager::singleton()->regist_widget(this);
}

Widget::~Widget() 
{
}

bool Widget::is_enabled() const
{
	return enabled_ && is_visible();
}

void Widget::set_enabled(bool enabled)
{
	enabled_ = enabled;
}

void Widget::set_visible(bool visible)
{
	if (!visible && is_focused())
	{
		focus_handler_->focus_none();
	}

	visible_ = visible;
}

bool Widget::is_focusable() const
{
	return focusable_ && is_visible() && is_focused();
}

void Widget::set_focusable(bool focusable)
{
	if (!focusable && is_focused())
	{
		focus_handler_->focus_none();
	}

	focusable_ = focusable;
}

bool Widget::is_focused() const
{
	if (!focus_handler_)
	{
		return false;
	}

	return (focus_handler_->is_focused(this));
}

void Widget::set_font(const std::string &font) 
{ 
	if (font.empty())
		return;

	font_ = (Font*)Font_Manager::singleton()->get_resource(font); 
}

void Widget::set_focus_handler(Focus_Handler* focus_handler)
{
	if (focus_handler_)
	{
		focus_handler_->remove(this);
	}

	if (focus_handler)
	{
		focus_handler->add(this);
	}

	focus_handler_ = focus_handler;

	Nodes::iterator iend = childs_.end();
	for (Nodes::iterator i = childs_.begin(); i != iend; ++ i)
	{
		((Widget *)(*i))->set_focus_handler(focus_handler);
	}

}

Focus_Handler* Widget::get_focus_handler()
{
    return focus_handler_;
}

void Widget::request_focus()
{
	if (focus_handler_ == NULL)
	{
		throw_ui_error("No focushandler set (did you add the widget to the gui?).");
	}

	if (is_focusable())
	{
		focus_handler_->request_focus(this);
	}
}

void Widget::request_modal_focus()
{
	if (focus_handler_ == NULL)
	{
		throw_ui_error("No focushandler set (did you add the widget to the gui?).");
	}

	focus_handler_->request_modal_focus(this);
}

void Widget::release_modal_focus()
{
	if (focus_handler_ == NULL)
	{
		throw_ui_error("No focushandler set (did you add the widget to the gui?).");
	}

	focus_handler_->release_modal_focus(this);
}

bool Widget::has_modal_focus()
{
	if (focus_handler_ == NULL)
	{
		throw_ui_error("No focushandler set (did you add the widget to the gui?).");
	}

	if (get_parent() != NULL)
	{
		return (focus_handler_->get_modal_focused() == this) || ((Widget*)get_parent())->has_modal_focus();
	}

	return focus_handler_->get_modal_focused() == this;
}

Widget *Widget::get_widget_at(int x, int y)
{
	Nodes::reverse_iterator iter;
	for (iter = childs_.rbegin(); iter != childs_.rend(); ++iter)
	{
		Rect r((*iter)->get_position(), (*iter)->get_size());
		if ((*iter)->is_visible() && r.pt_in_rect(Point(x, y)))
		{
			return (Widget *)(*iter);
		}
	}

	return 0;
}

void Widget::insert_child(Node* child, int index)
{
	Node::insert_child(child, index);

    ((Widget*)child)->set_focus_handler(get_focus_handler());
}

void Widget::remove_child(int index)
{
	if (index >= childs_.size())
		return;

	Widget* child = (Widget*)(*(childs_.begin() + index));
	childs_.erase(childs_.begin() + index);
	child->set_parent(0);
	child->set_focus_handler(0);
}

void Widget::remove_child(Node* child)
{
	Widget* widget = (Widget*)child;
	childs_.erase(std::remove(childs_.begin(), childs_.end(), child), childs_.end());
	child->set_parent(0);
	widget->set_focus_handler(0);
}

void Widget::remove_all_children()
{
    Nodes::iterator iend = childs_.end();
    for (Nodes::iterator i = childs_.begin(); i != iend; ++i)
    {
        (*i)->set_parent(0);
		((Widget*)(*i))->set_focus_handler(0);
    }

    childs_.clear();
}

void Widget::on_got_focus()
{

}

void Widget::on_lost_focus()
{

}

void Widget::on_key_char(char c)
{

}

void Widget::on_key_down(Key_Code key)
{

}

void Widget::on_key_up(Key_Code key)
{

}

void Widget::on_mouse_enter(const Point &pt)
{

}

void Widget::on_mouse_exit(const Point &pt)
{

}

void Widget::on_mouse_move(const Point &pt)
{

}

void Widget::on_mouse_down(const Point &pt, Mouse_ButtonID button_id, int click_count)
{
	if (get_parent() != NULL)
	{
		((Widget*)get_parent())->move_to_top(this);
	}

	if (is_movable())
	{
		pt_drag_ = pt;
		moving_ = true;
	}
}

void Widget::on_mouse_up(const Point &pt, Mouse_ButtonID button_id, int click_count)
{

}

void Widget::on_mouse_wheel(const Point &pt, int delta)
{

}

void Widget::on_mouse_drag(const Point &pt)
{
	if (is_movable() && moving_)
	{
		set_position(pt - pt_drag_ + get_position());

		pt_drag_ = pt;
	}
}

void Widget::move_to_top(Widget* widget)
{
	remove_child(widget);
	insert_child(widget);
}

void Widget::move_to_bottom(Widget* widget)
{
	remove_child(widget);
	insert_child(widget, 0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

