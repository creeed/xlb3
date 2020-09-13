#include "XlbeException.h"
#include "XlbeWindow.h"
#include "XlbeWidgetManager.h"
#include "XlbeSprite.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////////
Window::Window(const std::string &name) : Widget(name)
{
	spr_bk_ = new Sprite(name + "_bk");
	spr_bk_->set_hot(Point(0, 0));
    set_movable(true);
}

Window::~Window() 
{
	delete spr_bk_;
}

void Window::set_bk_image(const std::string &image) 
{
	if (!image.empty())
        spr_bk_->set_sprite_resource(image);
}

void Window::draw()
{
	if (!is_visible())
		return ;

	if (spr_bk_->get_sprite_resource())
	{
		spr_bk_->set_position(get_absolute_position());
		spr_bk_->set_size(get_size());
		spr_bk_->draw();
	}

	Widget::draw();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

