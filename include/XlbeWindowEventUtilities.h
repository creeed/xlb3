#ifndef __XLBE_WINDOW_EVENT_UTILITIES_H__
#define __XLBE_WINDOW_EVENT_UTILITIES_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

//////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeInput.h"
#include "XlbeRenderWindow.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////////////
class Window_Event_Listener
{
public:
    virtual void window_moved(Render_Window* rw) = 0;
    virtual void window_focus_change(Render_Window* rw) = 0;
    virtual void window_resized(Render_Window* rw) = 0;
    virtual void window_closed(Render_Window* rw) = 0;
	virtual void window_input(Input_Event ie) = 0;

};

class Xlbe_Export Window_Event_Utilities
{
public:
    typedef std::vector<Window_Event_Listener *> Event_Listeners;
    typedef std::vector<Render_Window *> Render_Windows;

public:
    static void add_event_listener(Window_Event_Listener *listener);
    static void remove_event_listener(Window_Event_Listener *listener);

    static void add_render_window(Render_Window *window);
    static void remove_render_window(Render_Window *window);

    static bool message_pump();

    static LRESULT CALLBACK _WndProc(HWND hWnd, UINT uMsg,WPARAM wParam, LPARAM lParam);

    static Event_Listeners event_listeners_;
    static Render_Window  *render_window_;

    static Point drag_caption_delta_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif