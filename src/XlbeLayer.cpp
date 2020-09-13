#include "XlbeException.h"
#include "XlbeNode.h"
#include "XlbeSprite.h"
#include "XlbeLayer.h"
#include "XlbeScene.h"
#include "XlbeRoot.h"

/////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

/////////////////////////////////////////////////////////////////////////////////////////
Layer::Layer(const std::string& name)
:Node(name)
{
}

Layer::~Layer()
{
}

void Layer::on_key_char(char c)
{
    Nodes::iterator iend = childs_.end();

    for (Nodes::iterator i = childs_.begin(); i != iend; ++i)
    {
        Layer *layer = dynamic_cast<Layer*>((*i));

        if (layer && layer->is_visible())
            layer->on_key_char(c);
    }
}

void Layer::on_key_down(Key_Code key)
{
    Nodes::iterator iend = childs_.end();

    for (Nodes::iterator i = childs_.begin(); i != iend; ++i)
    {
        Layer *layer = dynamic_cast<Layer*>((*i));

        if (layer && layer->is_visible())
            layer->on_key_down(key);
    }
}

void Layer::on_key_up(Key_Code key)
{
    Nodes::iterator iend = childs_.end();

    for (Nodes::iterator i = childs_.begin(); i != iend; ++i)
    {
        Layer *layer = dynamic_cast<Layer*>((*i));

        if (layer && layer->is_visible())
            layer->on_key_up(key);
    }
}

void Layer::on_mouse_move(const Point &pt)
{
    Nodes::iterator iend = childs_.end();

    for (Nodes::iterator i = childs_.begin(); i != iend; ++i)
    {
        Layer *layer = dynamic_cast<Layer*>((*i));

        if (layer && layer->is_visible())
            layer->on_mouse_move(pt);
    }
}

void Layer::on_mouse_down(const Point &pt, Mouse_ButtonID button_id, int click_count)
{
    Nodes::iterator iend = childs_.end();

    for (Nodes::iterator i = childs_.begin(); i != iend; ++i)
    {
        Layer *layer = dynamic_cast<Layer*>((*i));

        if (layer && layer->is_visible())
            layer->on_mouse_down(pt, button_id, click_count);
    }
}

void Layer::on_mouse_up(const Point &pt, Mouse_ButtonID button_id, int click_count)
{
    Nodes::iterator iend = childs_.end();

    for (Nodes::iterator i = childs_.begin(); i != iend; ++i)
    {
        Layer *layer = dynamic_cast<Layer*>((*i));

        if (layer && layer->is_visible())
            layer->on_mouse_up(pt, button_id, click_count);
    }
}

void Layer::on_mouse_wheel(const Point &pt, int delta)
{
    Nodes::iterator iend = childs_.end();

    for (Nodes::iterator i = childs_.begin(); i != iend; ++i)
    {
        Layer *layer = dynamic_cast<Layer*>((*i));

        if (layer && layer->is_visible())
            layer->on_mouse_wheel(pt, delta);
    }
}

void Layer::on_mouse_drag(const Point &pt)
{
    Nodes::iterator iend = childs_.end();

    for (Nodes::iterator i = childs_.begin(); i != iend; ++i)
    {
        Layer *layer = dynamic_cast<Layer*>((*i));

        if (layer && layer->is_visible())
            layer->on_mouse_drag(pt);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
}


