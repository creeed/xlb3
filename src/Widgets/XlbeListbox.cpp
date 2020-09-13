#include "XlbePrereqs.h"
#include "XlbeColorRect.h"
#include "XlbeImageset.h"
#include "XlbeListbox.h"
#include "XlbeScrollbar.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////////
Listbox::Listbox(const std::string &name, Widget_Manager *creator) : Widget(name, "Listbox", creator)
{
    over_ = false;
    down_ = false;

	bk_image_ = 0;
    normal_image_ = 0;
    over_image_ = 0;
    down_image_ = 0;	
    disabled_image_ = 0;

	slot_position_func_ = 0;

	scrollbar_  = 0;
	position_ = 0;
	page_size_ = 0;
	select_item_ = -1;
	item_height_ = 0;
}

Listbox::~Listbox() 
{
}

void Listbox::set_image(const std::string &bk_image, const std::string &normal_image, 
		const std::string &over_image, const std::string &down_image, const std::string &disabled_image)
{
	if (!bk_image.empty())
	    bk_image_ = Imageset_Manager::singleton()->string_to_image(bk_image);
    
    if (!normal_image.empty())
        normal_image_ = Imageset_Manager::singleton()->string_to_image(normal_image);

	if (!over_image.empty())
        over_image_ = Imageset_Manager::singleton()->string_to_image(over_image);

	if (!down_image.empty())
        down_image_ = Imageset_Manager::singleton()->string_to_image(down_image);

	if (!disabled_image.empty())
        disabled_image_ = Imageset_Manager::singleton()->string_to_image(disabled_image);
}

void Listbox::on_got_focus()
{
}

void Listbox::on_lost_focus()
{
    down_ = false;
	over_ = false;
}

void Listbox::on_mouse_enter(const Point &pt)
{
	__super::on_mouse_enter(pt);

	over_ = true;
}
void Listbox::on_mouse_exit(const Point &pt)
{
	__super::on_mouse_exit(pt);

    //down_ = false;
	over_ = false;
}

void Listbox::on_mouse_down(const Point &pt, Mouse_ButtonID button_id, int click_count)
{
 if (!is_visible()|| !is_enabled())
        return ;

    down_ = true;
}

void Listbox::on_mouse_up(const Point &pt, Mouse_ButtonID button_id, int click_count)
{
	if (down_ && over_)
	{
		down_ = false;

		//if (slot_position_func_)
  //          (*slot_position_func_)(this);
	}
	else 
	{
		down_ = false;
	}
}

void Listbox::on_mouse_wheel(const Point &pt, int delta)
{
	if (scrollbar_ != 0)
	{
		int amount = 1;

		if (delta > 0)
		{
			scrollbar_->set_value(scrollbar_->get_value() - amount);
		}
		else if (delta < 0)
		{
			scrollbar_->set_value(scrollbar_->get_value() + amount);
		}
	}
}

void Listbox::draw()
{
    if (!is_visible() || !disabled_image_ || !down_image_ || !over_image_ || !normal_image_ )
        return;

	Point pt = get_absolute_position();

	if (bk_image_)
	{
		bk_image_->draw(pt, get_size());
	}

	int first_line = (int) position_;
	int last_line = std::min((int) list_items_.size(), (int) position_ + (int) page_size_);

	for (int i = first_line; i < last_line; i++)
	{
		if (i == select_item_)
		{
			Point pt_draw(rc_client_.left_ + pt.x_, rc_client_.top_ + (i - (int)position_) * item_height_ + pt.y_);
			Size sz_draw(rc_client_.get_width(), item_height_);

			down_image_->draw(pt_draw, sz_draw);

			list_items_[i]->draw_select(pt_draw, sz_draw);
		}
		else
		{
			Point pt_draw(rc_client_.left_ + pt.x_, rc_client_.top_ + (i - (int)position_) * item_height_ + pt.y_);
			Size sz_draw(rc_client_.get_width(), item_height_);

			normal_image_->draw(pt_draw, sz_draw);

			list_items_[i]->draw_normal(pt_draw, sz_draw);
		}
	}

	Widget::draw();
}

void Listbox::set_size(int width, int height) 
{
	Widget::set_size(width, height);
}

void Listbox::set_client_rect(const Rect &rc)
{ 
	rc_client_ = rc; 

	float height = rc_client_.get_height();
	float page_size = 1;			
	
	if (height > item_height_ ) 
		page_size = float(height) / item_height_;

	page_size_ = page_size;
		
	if (scrollbar_ != NULL) 
		scrollbar_->set_page_size(page_size);
}

int Listbox::get_selected()
{
	return select_item_;
}

void Listbox::set_selected(int selected)
{
	if (selected < 0)
	{
		select_item_ = -1;
	}
	else if (selected >= get_element_count())
	{
		select_item_ = get_element_count() - 1;
	}
	else
	{
		select_item_ = selected;
	}
}

int Listbox::get_element_count() const
{
	return list_items_.size();
}

List_Item *Listbox::get_element(int index)
{
	if (index < 0 || index >= get_element_count())
		return 0;

	return list_items_.at(index);
}

int Listbox::add_element(List_Item *item) 
{
	item->set_owner(this);
	item->set_index(get_element_count());

	list_items_.push_back(item);

	if (scrollbar_ != NULL) 
		scrollbar_->set_max_value(list_items_.size());

	return item->get_index();
}

void Listbox::remove_element(int index)
{
}

void Listbox::remove_all_element()
{
	for (int i = 0; i < get_element_count(); i++)
	{
		if (list_items_[i] != 0)
			delete list_items_[i];
	}
    
	list_items_.clear();
    select_item_ = -1;
}

void Listbox::set_scrollbar(Scrollbar *scrollbar) 
{
	scrollbar_ = scrollbar;
	add_widget(scrollbar_);

	scrollbar_->set_slot(rak::mem_fn(this, &Listbox::scrollbar_position));
}

bool Listbox::scrollbar_position(Scrollbar* scrollbar)
{
    position_ = scrollbar_->get_value();

	if (slot_position_func_)
        (*slot_position_func_)(this);

	return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
}

