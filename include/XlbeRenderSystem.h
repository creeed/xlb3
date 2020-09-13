#ifndef __XLBE_RENDER_SYSTEM_H__
#define __XLBE_RENDER_SYSTEM_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

///////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeRect.h"
#include "XlbeVector.h"
#include "XlbeConfigoption.h"
#include "XlbeRenderPrimitive.h"
#include "XlbeRenderWindow.h"
#include "XlbeRenderTexture.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

///////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Render_System
{
public:
    Render_System() ;  
    virtual ~Render_System();

public:
	virtual int get_geometry_width() const { return geometry_width_; }
	virtual void set_geometry_width(int width) { geometry_width_ = width; }
	virtual int get_geometry_height() const { return geometry_height_; }
	virtual void set_geometry_height(int height) { geometry_height_ = height; }

    virtual Render_Window *initialise(const std::string& title, unsigned int width, unsigned int height, bool fullscreen) =0;
    virtual void shutdown() =0;

    virtual Rect get_geometry_rect()  ;

	virtual bool texture_filter() { return texture_filter_; }
	virtual void set_texture_filter(bool filter) { texture_filter_ = filter; }

	virtual void setup_view_matrix() = 0;
	virtual void setup_projection_matrix() = 0;
	virtual void set_camera(const Vector3 &pos, const Vector3 &view, const Vector3 &up) = 0;

    virtual bool begin_scene() =0;
    virtual void end_scene() =0;
    virtual void clear(unsigned long color) =0;

    virtual void render_line(Render_Line *line) =0;
    virtual void render_triple(Render_Triple *triple) =0;
    virtual void render_quad(Render_Quad *quad) =0;

    virtual Render_Texture* create_texture(const std::string& name, int width, int height) =0;
    virtual Render_Texture* create_texture(const std::string& filename) =0;
	virtual Render_Texture* get_texture(const std::string& name) = 0;
	virtual void destroy_texture(const std::string& name) =0;
    virtual void destroy_all_textures() =0;

    virtual void *get_device() const = 0;

protected:
	int geometry_width_;
	int geometry_height_;

	bool texture_filter_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif