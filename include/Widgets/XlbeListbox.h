#ifndef __XLBE_LISTBOX_H__
#define __XLBE_LISTBOX_H__

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
class Listbox;
class Scrollbar;

//////////////////////////////////////////////////////////////////////////////////////////////////////
class List_Item
{
public:
	virtual ~List_Item() { }

    virtual int get_index() const = 0;
    virtual void set_index(int index) = 0;

    virtual Listbox* get_owner() = 0;
    virtual void set_owner(Listbox* owner) = 0;

    virtual bool is_selected() const = 0;
    virtual void select(bool select) = 0;

    virtual void draw_normal(const Point &pt, const Size &size) = 0;
	virtual void draw_select(const Point &pt, const Size &size) = 0;
	virtual void draw_over(const Point &pt, const Size &size) = 0;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Listbox : public Widget
{
public:
    typedef rak::function_base1<bool, Listbox*> *Slot_Position_Func;
	typedef std::vector<List_Item*> List_Items;

public:
    Listbox(const std::string &name, Widget_Manager *creator) ;
    virtual ~Listbox() ;

public:
	virtual void set_position_slot(Slot_Position_Func solt) { slot_position_func_ = solt; }
    virtual void set_image(const std::string &bk_image, const std::string &normal_image, 
		const std::string &over_image, const std::string &down_image, const std::string &disabled_image);

	virtual void set_size(int width, int height) ;
	virtual Rect get_client_rect()  { return rc_client_; }
	virtual void set_client_rect(const Rect &rc);

	virtual int get_selected();
    virtual void set_selected(int selected);

    virtual int get_element_count() const;
    virtual List_Item *get_element(int i);

	virtual int add_element(List_Item *item) ;
    virtual void remove_element(int i);
	virtual void remove_all_element();

	virtual float get_item_height() const { return item_height_; }
	virtual void set_item_height(float item_height) { item_height_ = item_height; }

	virtual Scrollbar *get_scrollbar() { return scrollbar_; }
	virtual void set_scrollbar(Scrollbar *scrollbar) ;
	bool scrollbar_position(Scrollbar* scrollbar);

public:
	virtual void on_got_focus();
	virtual void on_lost_focus();	

    virtual void on_mouse_enter(const Point &pt);
    virtual void on_mouse_exit(const Point &pt);
    virtual void on_mouse_down(const Point &pt, Mouse_ButtonID button_id, int click_count);
    virtual void on_mouse_up(const Point &pt, Mouse_ButtonID button_id, int click_count);
    virtual void on_mouse_wheel(const Point &pt, int delta);

    virtual void draw();

protected:
    bool over_;
    bool down_;

    Image* bk_image_;
    Image* normal_image_;
    Image* over_image_;
    Image* down_image_;	
    Image* disabled_image_;

    Slot_Position_Func slot_position_func_;

	List_Items list_items_;

	int select_item_;
	float item_height_;
	float position_;
	float page_size_;

	Scrollbar *scrollbar_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif