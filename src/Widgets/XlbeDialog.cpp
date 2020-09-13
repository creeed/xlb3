#include "XlbeException.h"
#include "XlbeDialog.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////////
Dialog::Dialog(const std::string &name, Widget_Manager *creator) : Widget(name, "Dialog", creator)
{
	slot_func_ = 0;
	back_image_ = 0;
    set_movable(true);
}

Dialog::~Dialog() 
{
}

void Dialog::set_image(const std::string &image) 
{
    back_image_ = Imageset_Manager::singleton()->string_to_image(image);
}

void Dialog::draw()
{
	if (!is_visible())
		return ;

	if (back_image_)
	    back_image_->draw(get_absolute_position(), get_size());

    draw_children();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
}

