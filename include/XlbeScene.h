#ifndef __XLBE_SCENE_H__
#define __XLBE_SCENE_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeRect.h"
#include "XlbeInput.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

class Camera;
class Node;
class Layer;
class Sprite;
class Label;

//////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Scene 
{
public:
	typedef std::list<Input_Event> Inputs;

	typedef std::map<std::string, Camera*, xlbe_utility::fast_less_compare> Cameras;
    typedef std::map<std::string, Node*, xlbe_utility::fast_less_compare> Nodes;
    
public:
    Scene(const std::string& name);
    virtual ~Scene();

	virtual void clear_scene();

	virtual void enter();
    virtual void exit();

    virtual void update(float ftime, float dt);
    virtual void draw();

public:
    const std::string &get_name() const { return name_; }
    void set_name(const std::string &name) { name_ = name; }

    void regist_camera(Camera* camera);
    Camera* get_camera(const std::string& name) ;

    void regist_node(Node *node);
	void unregist_node(Node *node);

	Layer* get_root_layer();

public:
	bool is_key_down(Key_Code key);
	bool is_left_button_down();
	bool is_middle_button_down();
	bool is_right_button_down();

	virtual void push_input(Input_Event ie);
	virtual void pop_input(Input_Event &ie);
	virtual void process_input();

    virtual void handle_key_char(char c);
    virtual void handle_key_down(Key_Code key);
    virtual void handle_key_up(Key_Code key);
    virtual void handle_mouse_move(float x, float y);
    virtual void handle_mouse_down(float x, float y, Mouse_ButtonID button_id, int click_count);
    virtual void handle_mouse_up(float x, float y, Mouse_ButtonID button_id, int click_count);
	virtual void handle_mouse_wheel(float x, float y, int delta);

    virtual void on_key_char(char c);
    virtual void on_key_down(Key_Code key);
    virtual void on_key_up(Key_Code key);
    virtual void on_mouse_move(const Point &pt);
    virtual void on_mouse_down(const Point &pt, Mouse_ButtonID button_id, int click_count);
    virtual void on_mouse_up(const Point &pt, Mouse_ButtonID button_id, int click_count);
	virtual void on_mouse_wheel(const Point &pt, int delta);

private:
    std::string name_;

	Cameras cameras_;
	Nodes nodes_;
    
	Layer *layer_root_;

private:
	Inputs inputs_;

	int	down_buttons;
	bool key_down[0xFF];
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif