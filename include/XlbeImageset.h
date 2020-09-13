#ifndef __XLBE_IMAGESET_H__
#define __XLBE_IMAGESET_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeResource.h"
#include "XlbeImage.h"
#include "XlbeRenderTexture.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Imageset : public Resource
{
public:
    typedef std::map<std::string, Image, xlbe_utility::fast_less_compare> Images;

public:
    Imageset(const std::string& name, Render_Texture *texture);
	Imageset(const std::string& name, const std::string& filename, const std::string& resource_group, const Size& native);
    virtual ~Imageset();

public:
	virtual void prepare();
	virtual void unprepare();
	virtual void load();
	virtual void unload();

public:
	Render_Texture* get_texture() const { return texture_; }
	Size get_native_size() const { return Size(native_width_, native_height_); }
    void set_native_size(const Size native) { native_width_ = native.width_; native_height_ = native.height_ ;}
	uint32_t get_image_count() const { return images_.size(); }

	bool is_image_defined(const std::string& name) const { return images_.find(name) != images_.end(); }
	Image& get_image(const std::string& name);
	void define_image(const std::string& name, const Point& position, const Size& size);
	void define_image(const std::string& name, const Rect& image_rect);
	void undefine_image(const std::string& name);
	void undefine_all_images();

	Size get_image_size(const std::string& name) /*const*/	{ return get_image(name).get_size(); }
	float get_image_width(const std::string& name) /*const*/ { return get_image(name).get_width(); }
	float get_image_height(const std::string& name) /*const*/ { return get_image(name).get_height(); }

    void draw(const Point dest[4], const Point src[4], const Color_Rect& colors, Render_Blend blend, float zbuffer = 0.0f);

private:
    Render_Quad quad_;
	float native_width_;
	float native_height_;
	Images images_;
    Render_Texture *texture_;
    std::string filename_;
    std::string resource_group_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif