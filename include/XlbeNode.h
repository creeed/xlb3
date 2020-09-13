#ifndef __XLBE_NODE_H__
#define __XLBE_NODE_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeSize.h"
#include "XlbePoint.h"
#include "XlbeRect.h"
#include "XlbeColorRect.h"
#include "XlbeRenderPrimitive.h"
#include "XlbeAction.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Node
{
public:
    typedef std::vector<Node*> Nodes;
	typedef std::list<Action*> Actions;

public:
    Node(const std::string& name);
    virtual ~Node();

public:
    const std::string &get_name() const { return name_; }
    void set_name(const std::string &name) { name_ = name; }

    bool is_visible() const { if (get_parent() == 0) { return visible_; } else { return visible_ && get_parent()->is_visible(); } }
    virtual void set_visible(bool visible) { visible_ = visible; }

	Point get_absolute_position() ;
    Point get_position() const { return position_; }
	void set_position(const Point &position) { position_ = position; }

	Size get_size() const { return size_; }
    virtual void set_size(const Size &size)  { size_ = size;  }

    Size get_scale() const { return scale_; }
    void set_scale(const Size &scale)  { scale_ = scale; }

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

public:
    Node* get_parent() const { return parent_; }
    void set_parent(Node *parent) { parent_ = parent; }

	void set_data(uint32_t data) { data_  = data; }
	uint32_t get_data() const { return data_; }

	virtual Node* get_child(int index) const; 
    virtual int number_of_children() const;
    virtual void insert_child(Node* child, int index = -1);
    virtual void remove_child(int index);
    virtual void remove_child(Node* child);
    virtual void remove_all_children();

    virtual void enter();
    virtual void exit();

    virtual void update(float ftime, float dt);
    virtual void draw();

public:
	void action_update(float dt);
    
    bool run_action(Action *action, bool pause = false);
	void pause_action(Action *action);
    void resume_action(Action *action);
	void remove_action(Action *action);

	int number_of_action() const { return actions_.size(); }
	Action *get_action(int index);
	void remove_all_action();
	void pause_all_action();
    void resume_all_action();

protected:
    std::string name_;
	uint32_t data_;
    Node *parent_;
    Nodes childs_;

    Point position_;
	Size size_;
    bool visible_; 
	float rotation_;
	Color_Rect color_rect_;
	Point hot_; 
	Size scale_;
	Size flip_;
	Rect src_rect_;
	Render_Blend blend_;

	Actions actions_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif