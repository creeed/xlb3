#ifndef __XLBE_RENDER_WINDOW_H__
#define __XLBE_RENDER_WINDOW_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

///////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeRect.h"

///////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

///////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Render_Window 
{
public:
    Render_Window() : drag_(true), draging_(false), active_(true), closed_(true),
        visible_(false), fullscreen_(false), width_(0), height_(0), hide_mouse_(false), deactivated_(false) {}
    virtual ~Render_Window() {}

public:
    virtual size_t window_handle() const = 0;
    virtual void create(const std::string& title, unsigned int width, unsigned int height, bool fullscreen) =0;
    virtual void destroy() =0;

    virtual bool visible() const { return visible_; }
    virtual void set_visible(bool visible) { visible_ = visible; }

    virtual bool active() const { return active_; }          
    virtual void set_active(bool active) { active_ = active; }

    virtual bool closed() const { return closed_; }
    virtual void set_closed(bool closed) { closed_ = closed; }

	virtual const Rect &caption_rect() const { return caption_; }
    virtual void set_caption_rect(const Rect &rc) { caption_ = rc; }

    virtual bool hide_mouse() const { return hide_mouse_; }
    virtual void set_hide_mouse(bool hide) { hide_mouse_ = hide;  } 

    virtual bool deactivated_on_focus_change() const { return deactivated_; }
    virtual void set_deactivated_on_focus_change(bool deactivated) { deactivated_ = deactivated; }

    virtual bool fullscreen() const { return fullscreen_; }
    virtual void set_fullscreen(bool fullscreen) { fullscreen_ = fullscreen; }

    virtual Size size() const { return Size(width_, height_); }                  
    virtual Point position() const { return Point(0,0); }
    virtual void reposition(int left, int top) { }
	virtual void resize(int width, int height) { }

    virtual bool drag_caption() const { return drag_; }
    virtual void set_drag_caption(bool drag) { drag_ = drag; }

	virtual bool draging_caption() const { return draging_; }
    virtual void set_draging_caption(bool draging) { draging_ = draging; }

    virtual void window_moved_or_resized() {}

protected:
    bool drag_;
	bool draging_;

    bool active_;
    bool closed_;
    bool visible_;
    bool fullscreen_;
    unsigned int width_;
    unsigned int height_;

	bool hide_mouse_;
    bool deactivated_;
    Rect caption_;

};

///////////////////////////////////////////////////////////////////////////////////////
}

#endif

