#include "XlbeException.h"
#include "XlbeWidget.h"
#include "XlbeFocusHandler.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////////
Focus_Handler::Focus_Handler() 
{
	focused_widget_ = 0;
	dragged_widget_ = 0;
	last_widget_with_mouse_ = 0;
	last_widget_pressed_ = 0;
	modal_focused_widget_ = 0;
}

Focus_Handler::~Focus_Handler() 
{
}

void Focus_Handler::add(Widget* widget)
{
	widgets_.push_back(widget);
}

void Focus_Handler::remove(Widget* widget)
{
	if (is_focused(widget))
	{
		focused_widget_ = NULL;
	}

	for (WidgetsIterator iter = widgets_.begin(); iter != widgets_.end(); ++iter)
	{
		if ((*iter) == widget)
		{
			widgets_.erase(iter);
			break;
		}
	}

	if (dragged_widget_ == widget)
	{
		dragged_widget_ = NULL;
		return;
	}   

	if (last_widget_with_mouse_ == widget)
	{
		last_widget_with_mouse_ = NULL;
		return;
	}

	if (last_widget_pressed_ == widget)
	{
		last_widget_pressed_ = NULL;
		return;
	}
}

void Focus_Handler::focus_none()
{ 
	if (focused_widget_ != NULL)
	{
		Widget* focused = focused_widget_;
		focused_widget_ = NULL;

		focused->on_lost_focus();
	}
}

void Focus_Handler::request_focus(Widget* widget)
{
	if (widget == NULL || widget == focused_widget_)
	{
		return;
	}

	int index = -1;
	for (int i = 0; i < widgets_.size(); ++i)
	{
		if (widgets_[i] == widget)
		{
			index = i;
			break;
		}
	}

	if (index < 0)
	{
		throw_ui_error("Trying to focus a none existing widget.");
	}

	Widget *old_focused = focused_widget_;
	if (old_focused != widget)
	{
		focused_widget_ = widgets_.at(index);

		if (old_focused != NULL)
		{
            old_focused->on_lost_focus();
		}

		focused_widget_->on_got_focus();
	}        
}

void Focus_Handler::request_modal_focus(Widget *widget)
{
	if (modal_focused_widget_ != NULL && modal_focused_widget_ != widget)
	{
		throw_ui_error("Another widget allready has modal focus.");
	}

	modal_focused_widget_ = widget;

	if (focused_widget_ != NULL && !focused_widget_->has_modal_focus())
	{
		focus_none();
	}
}

void Focus_Handler::release_modal_focus(Widget *widget)
{
	if (modal_focused_widget_ == widget)
	{
		modal_focused_widget_ = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

