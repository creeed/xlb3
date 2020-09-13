#ifndef __XLBE_RENDER_WINDOW_D3D9_H__
#define __XLBE_RENDER_WINDOW_D3D9_H__

//////////////////////////////////////////////////////////////////////////////////////
#include <d3d9.h>
#include <d3dx9.h>

#include "XlbePrereqs.h"
#include "XlbeRenderWindow.h"

//////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

class Render_System_D3d9;

//////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Render_Window_D3d9 : public Render_Window
{		
public:
    Render_Window_D3d9(HINSTANCE hinst, Render_System_D3d9 *rs) ;
    virtual ~Render_Window_D3d9(); 

    virtual size_t window_handle() const { return (size_t)hwnd_; }
    virtual void create(const std::string& title, unsigned int width, unsigned int height, bool fullscreen);
    virtual void destroy() ;

    virtual bool visible() const { return (hwnd_ /*&& !IsIconic(hwnd_)*/); }
    virtual void set_visible(bool visible) { visible_ = visible; }

    virtual void set_fullscreen(bool fullscreen);

	virtual Size size() const ;
    virtual Point position() const ;
    virtual void reposition(int left, int top) ;
	virtual void resize(int width, int height) ;

    virtual void window_moved_or_resized() ;

public:
    D3DPRESENT_PARAMETERS *presentation_parameters()  { return &d3dpp_; }

    void create_d3d_resources();
    void destroy_d3d_resources();

private:
    HWND hwnd_;
    HINSTANCE hinst_;

    Render_System_D3d9 *render_system_;
    D3DPRESENT_PARAMETERS d3dpp_;
};

//////////////////////////////////////////////////////////////////////////////////////
}

#endif