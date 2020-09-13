#include "XlbeException.h"
#include "XlbeFigure.h"
#include "XlbeImagesetManager.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////////////
Figure::Figure(const std::string& name, float width, float height)
{
    name_ = name;
    size_ = 0;

    width_ = width;
    height_ = height;
}


Figure::~Figure()
{
}

void Figure::prepare()
{
}

void Figure::unprepare()
{
}

void Figure::load()
{
    if (!is_loaded())
    {
       load_state_ = LOADSTATE_LOADED;
    }
}

void Figure::unload()
{
    load_state_ = LOADSTATE_UNLOADED;
}

int Figure::get_plate_count() const 
{
    return plates_.size(); 
}

bool Figure::is_plate_defined(const std::string& name) const 
{ 
    return plates_.find(name) != plates_.end();
}

Image *Figure::get_plate(const std::string &name) 
{
    Plates::iterator i = plates_.find(name);

    if (i != plates_.end())
    {
        return i->second;
    }

    throw_scene_error(name_ + " " + name + " plate not exisit");
}

void Figure::define_plate(const std::string &name, const std::string &value)
{
    if (is_plate_defined(name))
    {
        throw_scene_error(name + " plate is defined ");
    }

    plates_[name] = Imageset_Manager::singleton()->string_to_image(value);
}

void Figure::undefine_plate(const std::string &name)
{
    plates_.erase(name);
}

void Figure::undefine_all_plates()
{
    plates_.clear();
}

int Figure::get_animation_count() const 
{
    return animations_.size(); 
}

bool Figure::has_animation(const std::string& name) const 
{
    return animations_.find(name) != animations_.end();
}

Animation *Figure::get_animation(const std::string &name) 
{
    Animations::iterator i = animations_.find(name);

    if (i != animations_.end())
    {
        return i->second;
    }

    throw_scene_error(name + " animation not exisit");
}

Animation *Figure::create_animation(const std::string& name, float duration, int count)
{
    Animation *animation = new Animation(name, duration, count);
    animations_[animation->get_name()] = animation;

    return animation;
}

void Figure::destroy_animation(const std::string& name)
{
    Animations::iterator i = animations_.find(name);

    if (i == animations_.end())
        throw_scene_error(name + " animation not exists.");

    delete i->second;
    animations_.erase(i);
}

void Figure::destroy_all_animations()
{
    Animations::iterator i = animations_.begin();

    for(; i != animations_.end(); ++i)
    {
        delete i->second;
    }
    
    animations_.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
}
