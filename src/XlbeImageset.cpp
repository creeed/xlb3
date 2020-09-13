#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeImageset.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////////////
Imageset::Imageset(const std::string& name, Render_Texture *texture)
:texture_(texture)
{
    name_ = name;
    size_ = 0;

    quad_.texture_ = texture_;

    native_width_ = texture_->get_size().width_;
    native_height_ = texture_->get_size().height_;
}

Imageset::Imageset(const std::string& name, const std::string& filename, const std::string& resource_group, const Size& native)
{
    name_ = name;
    size_ = 0;

    filename_ = filename;
    resource_group_ = resource_group;

    native_width_ = native.width_;
    native_height_ = native.height_;

    define_image("full_image", Rect(0, 0, native_width_, native_height_));           
}

Imageset::~Imageset()
{
    unload();
}

void Imageset::prepare()
{
}

void Imageset::unprepare()
{
}

void Imageset::load()
{
    if (!is_loaded())
    {
       texture_ = &Root::singleton()->render_system()->create_texture(filename_, resource_group_);

       load_state_ = LOADSTATE_LOADED;
    }
}

void Imageset::unload()
{
    /*undefine_all_images();*/

    Root::singleton()->render_system()->destroy_texture(*texture_);
    texture_ = 0;

    load_state_ = LOADSTATE_UNLOADED;
}

Image& Imageset::get_image(const std::string &name) 
{
    Images::iterator i = images_.find(name);

    if (i != images_.end())
    {
        return i->second;
    }

    throw_scene_error(name_ + " " + name + " image not exisit");
}

void Imageset::define_image(const std::string& name, const Point& position, const Size& size)
{
    define_image(name, Rect(position, size));
}

void Imageset::define_image(const std::string &name, const Rect &area)
{
    if (is_image_defined(name))
    {
        throw_scene_error(name_ + " " + name + " Imageset::define_image  image is defined ");
    }

    images_.insert(std::pair<std::string, Image>(name, Image(this, name, area)));
}

void Imageset::undefine_image(const std::string &name)
{
    images_.erase(name);
}

void Imageset::undefine_all_images()
{
    images_.clear();
}

void Imageset::draw(const Point dest[4], const Point src[4], const Color_Rect& colors, Render_Blend blend, float zbuffer)
{
    quad_.blend_ = blend;

    quad_.texture_ = texture_;

    quad_.vertex_[0].color = colors.top_left_.toint();
    quad_.vertex_[1].color = colors.top_right_.toint();
    quad_.vertex_[2].color = colors.bottom_right_.toint();
    quad_.vertex_[3].color = colors.bottom_left_.toint();

    quad_.vertex_[0].x = dest[0].x_; quad_.vertex_[0].y = dest[0].y_; quad_.vertex_[0].z = zbuffer;
    quad_.vertex_[1].x = dest[1].x_; quad_.vertex_[1].y = dest[1].y_; quad_.vertex_[1].z = zbuffer;
    quad_.vertex_[2].x = dest[2].x_; quad_.vertex_[2].y = dest[2].y_; quad_.vertex_[2].z = zbuffer;
    quad_.vertex_[3].x = dest[3].x_; quad_.vertex_[3].y = dest[3].y_; quad_.vertex_[3].z = zbuffer;
	

    quad_.vertex_[0].tx=src[0].x_; quad_.vertex_[0].ty=src[0].y_; 
    quad_.vertex_[1].tx=src[1].x_; quad_.vertex_[1].ty=src[1].y_; 
    quad_.vertex_[2].tx=src[2].x_; quad_.vertex_[2].ty=src[2].y_; 
    quad_.vertex_[3].tx=src[3].x_; quad_.vertex_[3].ty=src[3].y_; 

    Root::singleton()->render_system()->render_quad(&quad_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
}
