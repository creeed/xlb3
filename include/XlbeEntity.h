#ifndef __XLBE_ENTITY_H__
#define __XLBE_ENTITY_H__

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
#include "XlbeNode.h"
#include "XlbeRenderPrimitive.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

class Scene;
class Action;
class ActionManager;
class Entity;

//////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Extend
{
public:
    Extend():group_(-1), mask_(0), entity_(0) {}
    virtual ~Extend() {}

public:
    virtual int get_group() const { return group_; }
    virtual void set_group(int group) { group_ = group; }

    virtual int get_mask() const { return mask_; }
    virtual void set_mask(int mask) { mask_ = mask; }

    virtual Entity *get_entity() { return entity_; }
    virtual void set_entity(Entity *entity) { entity_ = entity; }

private:
    int group_;
    int mask_;
    Entity *entity_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Entity
{
public:
    Entity(const std::string& name, const std::string& type, Scene *creator);
    virtual ~Entity();

public:
    const std::string &get_name() const { return name_; }
    void set_name(const std::string &name) { name_ = name; }

    const std::string &get_type() const { return type_; }

    virtual bool is_attached() const { return parent_ != 0; }
    virtual Node* get_parent_node(void) const { return parent_; }

    virtual bool visible() const { return visible_; }
    virtual void set_visible(bool visible) { visible_ = visible; }

    virtual bool disable() const { return disable_; }
    virtual void set_disable(bool disable) { disable_ = disable; }

    virtual bool running() const { return running_; }
    virtual void set_running(bool running) { running_ = running; }

    virtual Point position() const { return position_; }
    virtual Point get_absolute_position();
    virtual void set_position(const Point &position) { position_ = position; }

    virtual Size size() const { return size_; }
    virtual void set_size(const Size &size)  { size_ = size;  }

    virtual float rotation() const { return rotation_; }
    virtual void set_rotation(float rotation) { rotation_ = rotation; }

    virtual Size scale() const { return scale_; }
    virtual void set_scale(const Size &scale)  { scale_ = scale; }

    virtual Size flip() const { return flip_; }
    virtual void set_flip(const Size &flip) { flip_ = flip; }

    virtual Point hot() const { return hot_; }
    virtual void set_hot(const Point &hot)  { hot_ = hot; } 

    virtual Color_Rect color() const { return color_; }
    virtual void set_color(const Color_Rect &color) { color_ = color;}

    virtual Render_Blend blend() const { return blend_; }
    virtual void set_blend(Render_Blend blend) { blend_ = blend;}

    virtual int zorder() const { return zorder_; }
    virtual void set_zorder(int z)  { zorder_ = z; }

    virtual int zbuffer() const { return zbuffer_; }
    virtual void set_zbuffer(int zbuffer)  { zbuffer_ = zbuffer; }

    virtual Rect get_boundbox() const { return Rect(position_, size_); }

    virtual Scene *get_creator() const { return creator_; }
    virtual void notify_attached(Node *node);

    virtual void show_boundbox() { show_boundbox_ = true; }
    virtual void hide_boundbox() { show_boundbox_ = false; }

    uint32_t get_data() const { return data_; }
    void set_data(uint32_t data) { data_ = data; }

    Extend *get_extend() { return extend_; }
    void set_extend(Extend *extend) { extend_ = extend; extend_->set_entity(this); }

public:
    int number_of_action();
    Action *get_action(int tag);
    void run_action(Action *action);
    void remove_action(Action* action);
    void remove_action(int tag);
    void remove_all_action();

public:
    virtual void enter();
    virtual void exit();

    virtual void update(float dt);
    virtual void draw();

protected:
    std::string name_;
    std::string type_;

    bool visible_; 
    bool disable_;
    bool running_;
    int zorder_;
	float zbuffer_;
    float rotation_;	
    Size scale_;
    Point hot_; 
    Point position_;
    Size flip_;
    Size size_;
    Color_Rect color_;
    Render_Blend blend_;

    Node *parent_;
    Scene *creator_;

    bool show_boundbox_;

    uint32_t data_;
    Extend *extend_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif