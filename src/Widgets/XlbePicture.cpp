#include "XlbePrereqs.h"
#include "XlbeColorRect.h"
#include "XlbeImageset.h"
#include "XlbePicture.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////////
Picture::Picture(const std::string &name, Widget_Manager *creator) : Widget(name, "Picture", creator)
{
    image_ = 0;
}

Picture::~Picture() 
{
}

void Picture::set_image(const std::string &image)
{
    image_ = Imageset_Manager::singleton()->string_to_image(image);
}

void Picture::on_got_focus()
{
}

void Picture::on_lost_focus()
{
    //down_ = false;
	//over_ = false;
}

void Picture::on_mouse_enter(const Point &pt)
{
	__super::on_mouse_enter(pt);
	//over_ = true;
}
void Picture::on_mouse_exit(const Point &pt)
{
	__super::on_mouse_exit(pt);
    //down_ = false;
	//over_ = false;
}

void Picture::on_mouse_down(const Point &pt, Mouse_ButtonID button_id, int click_count)
{
    //if (!is_visible()|| !is_enabled())
    //    return ;

    //down_ = true;
}

void Picture::on_mouse_up(const Point &pt, Mouse_ButtonID button_id, int click_count)
{
	//if (down_ && over_)
	//{
	//	down_ = false;
 //       /*(*slot_func_)(this);*/
	//}
	//else 
	//{
	//	down_ = false;
	//}
}

void Picture::draw()
{
    if (!is_visible() || !image_)
        return;

    image_->draw(get_absolute_position(), get_size());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

