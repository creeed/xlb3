#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeWindowEventUtilities.h"
#include "XlbeRenderWindowD3d9.h"
#include "XlbeRenderSystemD3d9.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

/////////////////////////////////////////////////////////////////////////////////////////////////
Render_Window_D3d9::Render_Window_D3d9(HINSTANCE hinst, Render_System_D3d9 *rs)
:hinst_(hinst),
render_system_(rs)
{
}

Render_Window_D3d9::~Render_Window_D3d9()
{
    destroy();
}

void Render_Window_D3d9::create(const std::string& title, unsigned int width, unsigned int height, bool fullscreen)
{
    DWORD style;
    int left, top;

    WNDCLASS wc = { CS_DBLCLKS|CS_OWNDC|CS_HREDRAW|CS_VREDRAW, 
        Window_Event_Utilities::_WndProc, 0, 0, hinst_,
        LoadIcon(GetModuleHandle(0), IDI_APPLICATION), LoadCursor(NULL, IDC_ARROW),
        (HBRUSH)GetStockObject(BLACK_BRUSH), 0, "XLBERENDERWND" };
    RegisterClass(&wc);

    left=(GetSystemMetrics(SM_CXSCREEN)-width)/2;
    top=(GetSystemMetrics(SM_CYSCREEN)-height)/2;

    if (fullscreen)
    {
        style = WS_VISIBLE|WS_CLIPCHILDREN; 

    }
    else
    {      
        style = WS_POPUP|WS_SYSMENU|WS_MINIMIZEBOX|WS_VISIBLE|WS_CLIPCHILDREN;
    }

    hwnd_ = CreateWindowEx(0, "XLBERENDERWND", title.c_str(), 
        style, left, top, width, height, 0, 0, hinst_, this);

    active_ = true;
    closed_ = false;
    fullscreen_ = fullscreen;
    width_ = width;
    height_ = height;

    create_d3d_resources();

    Window_Event_Utilities::add_render_window(this);
}

void Render_Window_D3d9::destroy()
{
    destroy_d3d_resources();

    if (hwnd_)
    {
        Window_Event_Utilities::remove_render_window(this);
        DestroyWindow(hwnd_);
    }

    hwnd_ = 0;
    active_ = false;
    closed_ = true;
}

void Render_Window_D3d9::set_fullscreen(bool fullscreen) 
{
    DWORD style;

    if (fullscreen == fullscreen_)
    {
        return;
    }

    fullscreen_ = fullscreen;

    if (fullscreen_)
    {
        style = WS_VISIBLE|WS_CLIPCHILDREN; 

        d3dpp_.Windowed = FALSE;
        d3dpp_.SwapEffect = D3DSWAPEFFECT_FLIP;
    }
    else
    {
        style = WS_POPUP|WS_SYSMENU|WS_MINIMIZEBOX|WS_VISIBLE|WS_CLIPCHILDREN;

        d3dpp_.Windowed = TRUE;
        d3dpp_.SwapEffect = D3DSWAPEFFECT_COPY;
    }

    SetWindowLong(hwnd_, GWL_STYLE, style);
    SetWindowPos(hwnd_, 0, 0,0, 0,0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

    render_system_->notify_device_lost();

}

Size Render_Window_D3d9::size() const 
{
	if (hwnd_)
	{
		RECT rc;
		GetWindowRect(hwnd_, &rc);

		return Size(rc.right - rc.left, rc.bottom - rc.top);
	}

	return Size(0,0);
}

Point Render_Window_D3d9::position() const 
{
    if (hwnd_)
    {
        RECT rc;
        GetWindowRect(hwnd_, &rc);

        return Point(rc.left, rc.top);
    }

    return Point(0,0);
}

void Render_Window_D3d9::reposition(int left, int top) 
{
    if (hwnd_ && !fullscreen_)		
    {			
        SetWindowPos(hwnd_, 0, left, top, 0, 0,SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);		
    }
}

void Render_Window_D3d9::resize(int width, int height)
{
    if (hwnd_ && !fullscreen_)		
    {			
        SetWindowPos(hwnd_, 0, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);		
    }
}

void Render_Window_D3d9::window_moved_or_resized()
{
    //WM_DISPLAYCHANGE
    render_system_->notify_device_lost();
}

void Render_Window_D3d9::create_d3d_resources()
{
    D3DDISPLAYMODE mode;
    D3DFORMAT format = D3DFMT_UNKNOWN;  

    ZeroMemory(&d3dpp_, sizeof(d3dpp_));

    if(FAILED(render_system_->d3d()->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode)) 
        || mode.Format==D3DFMT_UNKNOWN) 
    {
        throw_render_error("Render_Window_D3d9::create_d3d_resources Can't determine desktop video mode");  
    }

    d3dpp_.BackBufferWidth = width_;
    d3dpp_.BackBufferHeight = height_;
    d3dpp_.BackBufferFormat = mode.Format;
    d3dpp_.BackBufferCount  = 1;
    d3dpp_.MultiSampleType  = D3DMULTISAMPLE_NONE ;
    d3dpp_.hDeviceWindow    = hwnd_;
    d3dpp_.EnableAutoDepthStencil = TRUE;
    d3dpp_.AutoDepthStencilFormat = D3DFMT_D16;

    if (fullscreen_)
    {
        d3dpp_.Windowed = FALSE;
        d3dpp_.SwapEffect = D3DSWAPEFFECT_FLIP;
    }
    else
    {
        d3dpp_.Windowed = TRUE;
        d3dpp_.SwapEffect = D3DSWAPEFFECT_COPY;
    }

    IDirect3DDevice9 *device=0;
    if( FAILED( render_system_->d3d()->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, 
        hwnd_, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp_, &device)))
    {
        throw_render_error("Render_Window_D3d9::create_d3d_resources -- Can't create D3D device");
    }

    render_system_->set_device(device);
}

void Render_Window_D3d9::destroy_d3d_resources()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////
}