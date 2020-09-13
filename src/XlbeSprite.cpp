#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeSprite.h"
#include "XlbeSpriteResource.h"
#include "XlbeSpriteResourceManager.h"

/////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

/////////////////////////////////////////////////////////////////////////////////////////
Sprite::Sprite(const std::string& name) 
:Node(name)
{
	texture_ = 0;
	texture_size_.set_size(1.0f, 1.0f);

	sprite_res_ = 0;
}

Sprite::Sprite(const std::string& name, const std::string &str_res) 
:Node(name)
{
	set_sprite_resource(str_res);
}

Sprite::Sprite(const std::string& name, Sprite_Resource *res) 
:Node(name)
{
	set_sprite_resource(res);
}

Sprite::~Sprite() 
{
}

void Sprite::set_sprite_resource(const std::string &str_res)
{
	if (str_res.empty())
		return;

	sprite_res_name_ = str_res;

	Sprite_Resource *res = (Sprite_Resource *)Sprite_Resource_Manager::singleton()->get_resource(str_res);
	
	if (res == 0)
		throw_scene_error(str_res + " sprite resource not find");

	set_sprite_resource(res);
}

void Sprite::set_sprite_resource(Sprite_Resource *res)
{
	if (res == 0)
		throw_scene_error(get_name() + " sprite's " + sprite_res_name_ + " resource  is not find");

	//rotation_ = res->get_rotation();
	//color_rect_ = res->get_color_rect();
	//hot_ = res->get_hot(); 
	//flip_ = res->get_flip();
	//src_rect_ = res->get_src_rect();
	//blend_ = res->get_blend();

	texture_pos_ = res->get_texture_pos();
	texture_size_ = res->get_texture_size();
	texture_ = res->get_texture();

    sprite_res_ = res;
	size_ = sprite_res_->get_texture_size();
}

Size Sprite::get_texture_size()
{
	if (sprite_res_)
		return sprite_res_->get_texture_size();

	else
		return Size(0, 0);
}

void Sprite::enter()
{
    Node::enter();
}

void Sprite::exit()
{
    Node::exit();
}

void Sprite::update(float ftime, float dt)
{
    Node::update(ftime, dt);
}

void Sprite::draw()
{
    if (!visible_)
        return;

	Node::draw();

	if (texture_)
	    texture_->ckeck_loaded();
	else
		return;

	float sint, cost;
	float x1, y1, x2, y2;
	float tx, ty, tx1, ty1, tx2, ty2;

	Point pt = get_absolute_position();

	float hotx = (size_.width_*hot_.x_);
    float hoty = (size_.height_*hot_.y_);

	x1 = -(hotx) * scale_.width_;
	y1 = -(hoty) * scale_.height_;
	x2 = (size_.width_ - hotx) * scale_.width_;
	y2 = (size_.height_ - hoty) * scale_.height_; 

	if (rotation_ != 0.0f)
	{
		//Ë³Ê±ÕëĞı×ª
		cost = std::cosf(rotation_);
		sint = std::sinf(rotation_);

		quad_.vertex_[0].x =  x1*cost - y1*sint + pt.x_;
		quad_.vertex_[0].y =  x1*sint + y1*cost + pt.y_;

		quad_.vertex_[1].x =  x2*cost - y1*sint + pt.x_;
		quad_.vertex_[1].y =  x2*sint + y1*cost + pt.y_;

		quad_.vertex_[2].x =  x2*cost - y2*sint + pt.x_;
		quad_.vertex_[2].y =  x2*sint + y2*cost + pt.y_;

		quad_.vertex_[3].x =  x1*cost - y2*sint + pt.x_;
		quad_.vertex_[3].y =  x1*sint + y2*cost + pt.y_;
	}
	else
	{
		quad_.vertex_[0].x  =  x1 + pt.x_;
		quad_.vertex_[0].y =  y1 + pt.y_;

		quad_.vertex_[1].x  =  x2 + pt.x_;
		quad_.vertex_[1].y =  y1 + pt.y_;

		quad_.vertex_[2].x  =  x2 + pt.x_;
		quad_.vertex_[2].y =  y2 + pt.y_;

		quad_.vertex_[3].x  =  x1 + pt.x_;
		quad_.vertex_[3].y =  y2 + pt.y_;
	}

	if (src_rect_.get_width() == 0.0f || src_rect_.get_height() == 0.0f)
	{
		tx1 = texture_pos_.x_ / texture_->get_size().width_;
		ty1 = texture_pos_.y_ / texture_->get_size().height_;

		tx2= (texture_pos_.x_ + texture_size_.width_) / texture_->get_size().width_;
		ty2 = (texture_pos_.y_ + texture_size_.height_) / texture_->get_size().height_;
	}
	else
	{
		tx1 = (texture_pos_.x_  + src_rect_.left_ ) / texture_->get_size().width_;
		ty1 = (texture_pos_.y_  + src_rect_.top_) / texture_->get_size().height_;

		tx2= (texture_pos_.x_ + src_rect_.left_+ src_rect_.get_width()) / texture_->get_size().width_;
		ty2 = (texture_pos_.y_ + src_rect_.top_ + src_rect_.get_height()) / texture_->get_size().height_;
	}


	quad_.vertex_[0].tx = tx1; quad_.vertex_[0].ty = ty1; 
    quad_.vertex_[1].tx = tx2; quad_.vertex_[1].ty = ty1; 
    quad_.vertex_[2].tx = tx2; quad_.vertex_[2].ty = ty2; 
    quad_.vertex_[3].tx = tx1; quad_.vertex_[3].ty = ty2; 

    quad_.blend_ = blend_;
    quad_.texture_ = texture_;

    quad_.vertex_[0].color = color_rect_.top_left_.toint();
    quad_.vertex_[1].color = color_rect_.top_right_.toint();
    quad_.vertex_[2].color = color_rect_.bottom_right_.toint();
    quad_.vertex_[3].color = color_rect_.bottom_left_.toint();

    Root::singleton()->render_system()->render_quad(&quad_);
}



////////////////////////////////////////////////////////////////////////////////////////////
}
