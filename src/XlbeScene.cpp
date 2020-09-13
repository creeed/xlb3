#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeLayer.h"
#include "XlbeLabel.h"
#include "XlbeSprite.h"
#include "XlbeCamera.h"
#include "XlbeScene.h"

////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////
Scene::Scene(const std::string& name)
:name_(name),
layer_root_(0),
down_buttons(0)
{
    for (int i = 0; i < 0xFF; i++)
		key_down[i] = false;
}

Scene::~Scene()
{
    clear_scene();
    
    delete layer_root_;
}

void Scene::regist_camera(Camera* camera)
{
    if (cameras_.find(camera->get_name()) != cameras_.end())
        throw_scene_error(camera->get_name() + " camera already exists.");

    cameras_[camera->get_name()] = camera;

    return ;
}

Camera* Scene::get_camera(const std::string& name) 
{
    Cameras::const_iterator i = cameras_.find(name);

    if (i == cameras_.end())
        throw_scene_error(name + " camera not found.");

    return i->second;
}

Layer* Scene::get_root_layer()
{
    if (!layer_root_)
	{
		layer_root_ = new Layer("Xlbe/LayerRoot");
		regist_node(layer_root_);
	}

    return layer_root_;
}

void Scene::regist_node(Node *node)
{
    //if (nodes_.find(node->get_name()) != nodes_.end())
    //    throw_scene_error(node->get_name() + "node already exists.");

    //nodes_[node->get_name()] = node;

    return ;
}

void Scene::unregist_node(Node *node)
{
	//Nodes::iterator ifind = nodes_.find(node->get_name());
 //   if (ifind != nodes_.end())
	//{
	//	nodes_.erase(ifind);
	//}

    return ;
}

void Scene::clear_scene()
{
	cameras_.clear();
	nodes_.clear();
}

void Scene::enter()
{
    get_root_layer()->enter();
}

void Scene::exit()
{
    get_root_layer()->exit();
}

void Scene::update(float ftime, float dt)
{
	//process_input();
    get_root_layer()->update(ftime, dt);
}

void Scene::draw()
{
    get_root_layer()->draw();
}

void Scene::push_input(Input_Event ie)
{
	inputs_.push_back(ie);
}

void Scene::pop_input(Input_Event &ie)
{
	if (inputs_.empty())
	{
		ie.type_ = INPUT_NULL;
		return;
	}

	ie = inputs_.front();
	inputs_.pop_front();
}

void Scene::process_input()
{
	while (inputs_.size() > 0)
	{
	    Input_Event ie = inputs_.front();
	    inputs_.pop_front();

		switch (ie.type_)
		{
		case INPUT_MOUSEMOVE:
			{
				handle_mouse_move(ie.x_, ie.y_);
				break;
			}
		case INPUT_LBUTTONDOWN:
			{
				SetCapture((HWND)ie.handle_);
				handle_mouse_down(ie.x_, ie.y_, MB_Left, 1);
				break;
			}
		case INPUT_RBUTTONDOWN:
			{
				SetCapture((HWND)ie.handle_);
				handle_mouse_down(ie.x_, ie.y_, MB_Right, 1);
				break;
			}
		case INPUT_MBUTTONDOWN:
			{
				SetCapture((HWND)ie.handle_);
				handle_mouse_down(ie.x_, ie.y_, MB_Middle, 1);
				break;
			}
		case INPUT_LBUTTONDBLCLK:
			{
				SetCapture((HWND)ie.handle_);
				handle_mouse_down(ie.x_, ie.y_, MB_Left, 2);
				break;
			}
		case INPUT_RBUTTONDBLCLK:
			{
				SetCapture((HWND)ie.handle_);
				handle_mouse_down(ie.x_, ie.y_, MB_Right, 2);
				break;
			}
		case INPUT_LBUTTONUP:	
			{
				//if ((down_buttons & ~1) == 0)
				//    ReleaseCapture();

				handle_mouse_up(ie.x_, ie.y_, MB_Left, 1);

				break;
			}
		case INPUT_RBUTTONUP:
			{
				//if ((down_buttons & ~2) == 0)
				//    ReleaseCapture();

				handle_mouse_up(ie.x_, ie.y_, MB_Right, 1);

				break;
			}
		case INPUT_MBUTTONUP:
			{
				//if ((down_buttons & ~4) == 0)
				//    ReleaseCapture();

				handle_mouse_up(ie.x_, ie.y_, MB_Middle, 1);
				break;
			}
		case INPUT_MOUSEWHEEL:
			{
				handle_mouse_wheel(ie.x_, ie.y_, ie.wheel_);
				break;
			}
		case INPUT_KEYDOWN:
		case INPUT_SYSKEYDOWN:
			{
				handle_key_down((Key_Code)ie.key_);
				break;
			}
		case INPUT_KEYUP:
		case INPUT_SYSKEYUP:
			{
				handle_key_up((Key_Code)ie.key_);
				break;
			}
		case INPUT_CHAR:
			{
				handle_key_char((char)ie.chr_);
				break;
			}
		}
	}
}

void Scene::handle_key_char(char c)
{
    on_key_char(c);
    get_root_layer()->on_key_char(c);
}

void Scene::handle_key_down(Key_Code key)
{
    on_key_down(key);
    get_root_layer()->on_key_down(key);
}

void Scene::handle_key_up(Key_Code key)
{
    on_key_up(key);
    get_root_layer()->on_key_up(key);
}

void Scene::handle_mouse_move(float x, float y)
{
    on_mouse_move(Point(x,y));
    get_root_layer()->on_mouse_move(Point(x,y));
}

void Scene::handle_mouse_down(float x, float y, Mouse_ButtonID button_id, int click_count)
{
    on_mouse_down(Point(x,y), button_id, click_count);
    get_root_layer()->on_mouse_down(Point(x,y), button_id, click_count);
}

void Scene::handle_mouse_up(float x, float y, Mouse_ButtonID button_id, int click_count)
{
    on_mouse_up(Point(x,y), button_id, click_count);
    get_root_layer()->on_mouse_up(Point(x,y), button_id, click_count);
}

void Scene::handle_mouse_wheel(float x, float y, int delta)
{
    on_mouse_wheel(Point(x,y), delta);
    get_root_layer()->on_mouse_wheel(Point(x,y), delta);
}

void Scene::on_key_char(char c)
{
}

void Scene::on_key_down(Key_Code key)
{
	if ((key >= 0) && (key < 0xFF))
		key_down[key] = true;
}

void Scene::on_key_up(Key_Code key)
{
	if ((key >= 0) && (key < 0xFF))
		key_down[key] = false;
}

void Scene::on_mouse_move(const Point &pt)
{
    Mouse_Cursor::singleton()->set_position(Point(pt.x_, pt.y_));
}

void Scene::on_mouse_down(const Point &pt, Mouse_ButtonID button_id, int click_count)
{
	if (button_id == MB_Right)
	{
		down_buttons |= 0x02;
	}
	else if (button_id == MB_Middle)
	{
		down_buttons |= 0x04;
	}
	else
	{
		down_buttons |= 0x01;
	}


}

void Scene::on_mouse_up(const Point &pt, Mouse_ButtonID button_id, int click_count)
{
	int mask;
	
	if (button_id == MB_Right)
		mask = 0x02;
	else if (button_id == MB_Middle)
		mask = 0x04;
	else
		mask = 0x01;

	down_buttons &= ~mask;	


}

void Scene::on_mouse_wheel(const Point &pt, int delta)
{
}

bool Scene::is_key_down(Key_Code key)
{
	return key_down[key] ;
}

bool Scene::is_left_button_down()
{
	return (down_buttons & 1) ? true : false;
}

bool Scene::is_middle_button_down()
{
	return (down_buttons & 4) ? true : false;
}

bool Scene::is_right_button_down()
{
	return (down_buttons & 2) ? true : false;
}

////////////////////////////////////////////////////////////////////////////////////////////

}