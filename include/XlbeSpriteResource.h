#ifndef __XLBE_SPRITE_RESOURCE_H__
#define __XLBE_SPRITE_RESOURCE_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeResource.h"
#include "XlbeSize.h"
#include "XlbePoint.h"
#include "XlbeRect.h"
#include "XlbeColorRect.h"
#include "XlbeRenderPrimitive.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Sprite_Resource : public Resource
{
public:
    Sprite_Resource(const std::string& name);
    virtual ~Sprite_Resource();

public:
	virtual void prepare();
	virtual void unprepare();
	virtual void load();
	virtual void unload();

public:
    float get_rotation() const { return rotation_; }
    void set_rotation(float rotation) { rotation_ = rotation; }

	Color get_color() const { return color_rect_.top_left_; }
    void set_color(const Color &color) { color_rect_.set_color(color); }

    Color_Rect get_color_rect() const { return color_rect_; }
    void set_color_rect(const Color_Rect &color) { color_rect_ = color;}

	Size get_flip() const { return flip_; }
    void set_flip(const Size &flip) { flip_ = flip; }

	Point get_hot() const { return hot_; }
    void set_hot(const Point &hot)  { hot_ = hot; } 

	Render_Blend get_blend() const { return blend_; }
    void set_blend(Render_Blend blend) { blend_ = blend;}

	Rect get_src_rect() { return src_rect_ ; }
	void set_src_rect(const Rect src) { src_rect_ = src; }

	Render_Texture *get_texture() const { return texture_; }
	void set_texture(Render_Texture *tex) { texture_ = tex; }

	const Point &get_texture_pos() const { return texture_pos_; }
	void set_texture_pos(Point &pt) { texture_pos_ = pt; }

	const Size &get_texture_size() const { return texture_size_; }
	void set_texture_size(Size &sz) { texture_size_ = sz; }

	const std::string &get_texture_filename() const { return texture_filename_; }
	void set_texture_filename(const std::string &filename) { texture_filename_ = filename; }

private:
	float rotation_;
	Color_Rect color_rect_;
	Point hot_; 
	Size flip_;
	Rect src_rect_;
	Render_Blend blend_;

	Point texture_pos_;
	Size texture_size_;
	Render_Texture *texture_;

	std::string texture_filename_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif