#include "XlbeRoot.h"
#include "XlbeRenderWindow.h"
#include "XlbeRenderSystem.h"
#include "XlbeWindowEventUtilities.h"

#include "XlbeScene.h"
#include "XlbeSceneManager.h"
#include "XlbeWidgetManager.h"

///////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

///////////////////////////////////////////////////////////////////////////////////////////////
Window_Event_Utilities::Event_Listeners Window_Event_Utilities::event_listeners_;
Render_Window *Window_Event_Utilities::render_window_=0;
Point Window_Event_Utilities::drag_caption_delta_;

////////////////////////////////////////////////////////////
void Window_Event_Utilities::add_event_listener(Window_Event_Listener *listener)
{
    event_listeners_.push_back(listener);
}

void Window_Event_Utilities::remove_event_listener(Window_Event_Listener *listener)
{
    Event_Listeners::iterator i = event_listeners_.begin();
    for (; i!=event_listeners_.end(); ++i)
    {
        if ((*i) == listener)
        {
            event_listeners_.erase(i);
            return;
        }
    }
}

void Window_Event_Utilities::add_render_window(Render_Window *window)
{
    render_window_ = window;
}

void Window_Event_Utilities::remove_render_window(Render_Window *window)
{
    render_window_ = 0;  
}

bool Window_Event_Utilities::message_pump()
{
	bool ret = false;
    MSG  msg;

    while( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
    {
		ret = true;
        TranslateMessage( &msg );
        DispatchMessage( &msg );
    }

	return ret;
}

LRESULT CALLBACK Window_Event_Utilities::_WndProc(HWND hWnd, UINT uMsg,
                                                  WPARAM wParam, LPARAM lParam)
{
    if (render_window_==0 )
        return DefWindowProc(hWnd, uMsg, wParam, lParam);

	Input_Event input_event;
	memset(&input_event, 0, sizeof(Input_Event));

    switch( uMsg )
    {
    case WM_ACTIVATE:
        {
            bool active = (LOWORD(wParam) != WA_INACTIVE);
            if( active )
            {        
                render_window_->set_active( true );       
            }
            else
            {
				if (render_window_->deactivated_on_focus_change())
                    render_window_->set_active( false );
            }

            for (Event_Listeners::iterator i = event_listeners_.begin(); i!=event_listeners_.end(); ++i)
            {
                (*i)->window_focus_change(0);
            }

            break;
        }
	case WM_KEYDOWN:
		{
			input_event.type_ = INPUT_KEYDOWN;
			input_event.key_ = (int) wParam;
			input_event.handle_ = (size_t)hWnd;

			Scene* scene = Scene_Manager::singleton()->get_run_scene();
			if (scene) scene->push_input(input_event);
			Widget_Manager::singleton()->push_input(input_event);

			for (Event_Listeners::iterator i = event_listeners_.begin(); i!=event_listeners_.end(); ++i)
            {
                (*i)->window_input(input_event);
            }

			return 0;
		}
    case WM_SYSKEYDOWN:
		{
			input_event.type_ = INPUT_SYSKEYDOWN;
			input_event.key_ = (int) wParam;
			input_event.handle_ = (size_t)hWnd;

			Scene* scene = Scene_Manager::singleton()->get_run_scene();
			if (scene) scene->push_input(input_event);
			Widget_Manager::singleton()->push_input(input_event);

			for (Event_Listeners::iterator i = event_listeners_.begin(); i!=event_listeners_.end(); ++i)
            {
                (*i)->window_input(input_event);
            }

			return 0;
		}
	case WM_KEYUP:
		{
			input_event.type_ = INPUT_KEYUP;
			input_event.key_ = (int) wParam;
			input_event.handle_ = (size_t)hWnd;

			Scene* scene = Scene_Manager::singleton()->get_run_scene();
			if (scene) scene->push_input(input_event);
			Widget_Manager::singleton()->push_input(input_event);

			for (Event_Listeners::iterator i = event_listeners_.begin(); i!=event_listeners_.end(); ++i)
            {
                (*i)->window_input(input_event);
            }

			return 0;
		}
    case WM_SYSKEYUP:
		{
			input_event.type_ = INPUT_SYSKEYUP;
			input_event.key_ = (int) wParam;
			input_event.handle_ = (size_t)hWnd;

			Scene* scene = Scene_Manager::singleton()->get_run_scene();
			if (scene) scene->push_input(input_event);
			Widget_Manager::singleton()->push_input(input_event);


			for (Event_Listeners::iterator i = event_listeners_.begin(); i!=event_listeners_.end(); ++i)
            {
                (*i)->window_input(input_event);
            }

			return 0;
		}
	case WM_CHAR:
	    {
			if (int(wParam) >= 33 && int(wParam) != 127)
			{
				input_event.type_ = INPUT_CHAR;
				input_event.chr_ = (int) wParam;
				input_event.handle_ = (size_t)hWnd;

				Scene* scene = Scene_Manager::singleton()->get_run_scene();
				if (scene) scene->push_input(input_event);
				Widget_Manager::singleton()->push_input(input_event);

				for (Event_Listeners::iterator i = event_listeners_.begin(); i!=event_listeners_.end(); ++i)
				{
					(*i)->window_input(input_event);
				}
			}

			return 0;
	    }
    case WM_SYSCHAR:
        if (wParam != VK_SPACE)
            return 0;
        break;
    case WM_LBUTTONDOWN:
        {
            Point pt(LOWORD(lParam), HIWORD(lParam));
            Rect rc = render_window_->caption_rect();

			float width_geometry, height_geometry;
			float width_window, height_window;
			float width_rate, height_rate;

			width_geometry = Root::singleton()->render_system()->get_geometry_width();
			height_geometry = Root::singleton()->render_system()->get_geometry_height();
			width_window =  render_window_->size().width_;
            height_window = render_window_->size().height_;

			width_rate = width_window / width_geometry ;
			height_rate = height_window / height_geometry   ;

			rc.left_ = rc.left_ * width_rate ;
			rc.top_ = rc.top_ * height_rate;
			rc.right_ = rc.right_ * width_rate;
			rc.bottom_ = rc.bottom_ * height_rate;

            if (rc.pt_in_rect(pt))
            {
				
                POINT mouse_cur_pos;
                RECT window_cur_pos; 

                GetCursorPos(&mouse_cur_pos); 
                GetWindowRect((HWND)render_window_->window_handle(), &window_cur_pos);

                drag_caption_delta_.x_ = mouse_cur_pos.x - window_cur_pos.left;
                drag_caption_delta_.y_ = mouse_cur_pos.y - window_cur_pos.top;

                render_window_->set_draging_caption(true);
            }

			input_event.type_ = INPUT_LBUTTONDOWN;
			input_event.x_ = (float)((short) LOWORD(lParam)) * (width_geometry / width_window);
			input_event.y_ = (float)((short) HIWORD(lParam)) * (height_geometry / height_window);
			input_event.handle_ = (size_t)hWnd;

			Scene* scene = Scene_Manager::singleton()->get_run_scene();
			if (scene) scene->push_input(input_event);
			Widget_Manager::singleton()->push_input(input_event);

			for (Event_Listeners::iterator i = event_listeners_.begin(); i!=event_listeners_.end(); ++i)
            {
                (*i)->window_input(input_event);
            }

            return 0;
        }
    case WM_LBUTTONUP:
        {
            render_window_->set_draging_caption(false);

			float width_geometry, height_geometry;
			float width_window, height_window;

			width_geometry = Root::singleton()->render_system()->get_geometry_width();
			height_geometry = Root::singleton()->render_system()->get_geometry_height();
			width_window =  render_window_->size().width_;
            height_window = render_window_->size().height_;

			input_event.type_ = INPUT_LBUTTONUP;
			input_event.x_ = (float)((short) LOWORD(lParam)) * (width_geometry / width_window);
			input_event.y_ = (float)((short) HIWORD(lParam)) * (height_geometry / height_window);
			input_event.handle_ = (size_t)hWnd;

			Scene* scene = Scene_Manager::singleton()->get_run_scene();
			if (scene) scene->push_input(input_event);
			Widget_Manager::singleton()->push_input(input_event);

			for (Event_Listeners::iterator i = event_listeners_.begin(); i!=event_listeners_.end(); ++i)
            {
                (*i)->window_input(input_event);
            }

            return 0;
        }	
	case WM_RBUTTONDOWN:
		{
			float width_geometry, height_geometry;
			float width_window, height_window;

			width_geometry = Root::singleton()->render_system()->get_geometry_width();
			height_geometry = Root::singleton()->render_system()->get_geometry_height();
			width_window =  render_window_->size().width_;
            height_window = render_window_->size().height_;

			input_event.type_ = INPUT_RBUTTONDOWN;
			input_event.x_ = (float)((short) LOWORD(lParam)) * (width_geometry / width_window);
			input_event.y_ = (float)((short) HIWORD(lParam)) * (height_geometry / height_window);
			input_event.handle_ = (size_t)hWnd;

			Scene* scene = Scene_Manager::singleton()->get_run_scene();
			if (scene) scene->push_input(input_event);
			Widget_Manager::singleton()->push_input(input_event);

			for (Event_Listeners::iterator i = event_listeners_.begin(); i!=event_listeners_.end(); ++i)
            {
                (*i)->window_input(input_event);
            }

            return 0;
		}

	case WM_MBUTTONDOWN:
		{
			float width_geometry, height_geometry;
			float width_window, height_window;

			width_geometry = Root::singleton()->render_system()->get_geometry_width();
			height_geometry = Root::singleton()->render_system()->get_geometry_height();
			width_window =  render_window_->size().width_;
            height_window = render_window_->size().height_;

			input_event.type_ = INPUT_MBUTTONDOWN;
			input_event.x_ = (float)((short) LOWORD(lParam)) * (width_geometry / width_window);
			input_event.y_ = (float)((short) HIWORD(lParam)) * (height_geometry / height_window);
			input_event.handle_ = (size_t)hWnd;

			Scene* scene = Scene_Manager::singleton()->get_run_scene();
			if (scene) scene->push_input(input_event);
			Widget_Manager::singleton()->push_input(input_event);

			for (Event_Listeners::iterator i = event_listeners_.begin(); i!=event_listeners_.end(); ++i)
            {
                (*i)->window_input(input_event);
            }

            return 0;
		}
	case WM_LBUTTONDBLCLK:
		{
			float width_geometry, height_geometry;
			float width_window, height_window;

			width_geometry = Root::singleton()->render_system()->get_geometry_width();
			height_geometry = Root::singleton()->render_system()->get_geometry_height();
			width_window =  render_window_->size().width_;
            height_window = render_window_->size().height_;

			input_event.type_ = INPUT_LBUTTONDBLCLK;
			input_event.x_ = (float)((short) LOWORD(lParam)) * (width_geometry / width_window);
			input_event.y_ = (float)((short) HIWORD(lParam)) * (height_geometry / height_window);
			input_event.handle_ = (size_t)hWnd;

			Scene* scene = Scene_Manager::singleton()->get_run_scene();
			if (scene) scene->push_input(input_event);
			Widget_Manager::singleton()->push_input(input_event);

			for (Event_Listeners::iterator i = event_listeners_.begin(); i!=event_listeners_.end(); ++i)
            {
                (*i)->window_input(input_event);
            }

            return 0;
		}
	case WM_RBUTTONDBLCLK:
		{
			float width_geometry, height_geometry;
			float width_window, height_window;

			width_geometry = Root::singleton()->render_system()->get_geometry_width();
			height_geometry = Root::singleton()->render_system()->get_geometry_height();
			width_window =  render_window_->size().width_;
            height_window = render_window_->size().height_;

			input_event.type_ = INPUT_RBUTTONDBLCLK;
			input_event.x_ = (float)((short) LOWORD(lParam)) * (width_geometry / width_window);
			input_event.y_ = (float)((short) HIWORD(lParam)) * (height_geometry / height_window);
			input_event.handle_ = (size_t)hWnd;

			Scene* scene = Scene_Manager::singleton()->get_run_scene();
			if (scene) scene->push_input(input_event);
			Widget_Manager::singleton()->push_input(input_event);

			for (Event_Listeners::iterator i = event_listeners_.begin(); i!=event_listeners_.end(); ++i)
            {
                (*i)->window_input(input_event);
            }

            return 0;
		}
	case WM_RBUTTONUP:
		{
			float width_geometry, height_geometry;
			float width_window, height_window;

			width_geometry = Root::singleton()->render_system()->get_geometry_width();
			height_geometry = Root::singleton()->render_system()->get_geometry_height();
			width_window =  render_window_->size().width_;
            height_window = render_window_->size().height_;

			input_event.type_ = INPUT_RBUTTONUP;
			input_event.x_ = (float)((short) LOWORD(lParam)) * (width_geometry / width_window);
			input_event.y_ = (float)((short) HIWORD(lParam)) * (height_geometry / height_window);
			input_event.handle_ = (size_t)hWnd;

			Scene* scene = Scene_Manager::singleton()->get_run_scene();
			if (scene) scene->push_input(input_event);
			Widget_Manager::singleton()->push_input(input_event);

			for (Event_Listeners::iterator i = event_listeners_.begin(); i!=event_listeners_.end(); ++i)
            {
                (*i)->window_input(input_event);
            }

            return 0;
		}
	case WM_MBUTTONUP:
		{
			float width_geometry, height_geometry;
			float width_window, height_window;

			width_geometry = Root::singleton()->render_system()->get_geometry_width();
			height_geometry = Root::singleton()->render_system()->get_geometry_height();
			width_window =  render_window_->size().width_;
            height_window = render_window_->size().height_;

			input_event.type_ = INPUT_MBUTTONUP;
			input_event.x_ = (float)((short) LOWORD(lParam)) * (width_geometry / width_window);
			input_event.y_ = (float)((short) HIWORD(lParam)) * (height_geometry / height_window);
			input_event.handle_ = (size_t)hWnd;

			Scene* scene = Scene_Manager::singleton()->get_run_scene();
			if (scene) scene->push_input(input_event);
			Widget_Manager::singleton()->push_input(input_event);

			for (Event_Listeners::iterator i = event_listeners_.begin(); i!=event_listeners_.end(); ++i)
            {
                (*i)->window_input(input_event);
            }

            return 0;
		}
	case WM_MOUSEMOVE:	
		{
			float width_geometry, height_geometry;
			float width_window, height_window;

			width_geometry = Root::singleton()->render_system()->get_geometry_width();
			height_geometry = Root::singleton()->render_system()->get_geometry_height();
			width_window =  render_window_->size().width_;
            height_window = render_window_->size().height_;

			input_event.type_ = INPUT_MOUSEMOVE;
			input_event.x_ = (float)((short) LOWORD(lParam)) * (width_geometry / width_window);
			input_event.y_ = (float)((short) HIWORD(lParam)) * (height_geometry / height_window);
			input_event.handle_ = (size_t)hWnd;

			Scene* scene = Scene_Manager::singleton()->get_run_scene();
			if (scene) scene->push_input(input_event);
			Widget_Manager::singleton()->push_input(input_event);

			for (Event_Listeners::iterator i = event_listeners_.begin(); i!=event_listeners_.end(); ++i)
            {
                (*i)->window_input(input_event);
            }

			//Mouse_Cursor::singleton()->set_position(Point(input_event.x_, input_event.y_));

            return 0;
		}
	case WM_MOUSEWHEEL:	
		{
			RECT rc;
			GetWindowRect(hWnd, &rc);

			float width_geometry, height_geometry;
			float width_window, height_window;

			width_geometry = Root::singleton()->render_system()->get_geometry_width();
			height_geometry = Root::singleton()->render_system()->get_geometry_height();
			width_window =  render_window_->size().width_;
            height_window = render_window_->size().height_;

			input_event.type_ = INPUT_MOUSEWHEEL;
			input_event.x_ = (float)((short) LOWORD(lParam)) * (width_geometry / width_window) - rc.left;
			input_event.y_ = (float)((short) HIWORD(lParam)) * (height_geometry / height_window) - rc.top;
			input_event.wheel_ = ((short)HIWORD(wParam)) / 120;
			input_event.handle_ = (size_t)hWnd;

			Scene* scene = Scene_Manager::singleton()->get_run_scene();
			if (scene) scene->push_input(input_event);
			Widget_Manager::singleton()->push_input(input_event);

			for (Event_Listeners::iterator i = event_listeners_.begin(); i!=event_listeners_.end(); ++i)
            {
                (*i)->window_input(input_event);
            }

            return 0;
		}

    case WM_ENTERSIZEMOVE:
        break;
    case WM_EXITSIZEMOVE:
        break;
    case WM_MOVE:
        for (Event_Listeners::iterator j = event_listeners_.begin(); j!=event_listeners_.end(); ++j)
        {
            (*j)->window_moved(0);
        }

        break;
    case WM_DISPLAYCHANGE:
        render_window_->window_moved_or_resized();

        for (Event_Listeners::iterator j = event_listeners_.begin(); j!=event_listeners_.end(); ++j)
        {
            (*j)->window_resized(0);
        }

        break;
    case WM_SIZE:
        if (wParam != SIZE_MINIMIZED)
            render_window_->window_moved_or_resized();

        for (Event_Listeners::iterator j = event_listeners_.begin(); j!=event_listeners_.end(); ++j)
        {
            (*j)->window_resized(0);
        }

        break;
    case WM_GETMINMAXINFO:
        ((MINMAXINFO*)lParam)->ptMinTrackSize.x = 100;
        ((MINMAXINFO*)lParam)->ptMinTrackSize.y = 100;
        break;

    case WM_SETCURSOR:
        {      
			if (render_window_->active() && render_window_->hide_mouse() && LOWORD(lParam)==HTCLIENT)
            {
                SetCursor(NULL);
            }
            else SetCursor(LoadCursor(NULL, IDC_ARROW));

            return 0;
        } 
    case WM_CLOSE:
        {
			/*Root::singleton()->queue_end_rendering();*/

            for (Event_Listeners::iterator i = event_listeners_.begin(); i != event_listeners_.end(); ++i)
            {
                (*i)->window_closed(render_window_);
            }

            //render_window_->destroy();

            return 0;
        }
    case WM_ERASEBKGND:
        {
            return 0;
        }
	case WM_NCCALCSIZE :
		{
            return 0;
        }
	case WM_NCPAINT :
		{
            return 0;
		}
    }

    return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

///////////////////////////////////////////////////////////////////////////////////////////////
}