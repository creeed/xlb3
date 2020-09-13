#include "XlbeException.h"
#include "XlbeEntity.h"
#include "XlbeAction.h"
#include "XlbeActionManager.h"
#include "XlbeScene.h"

/////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

/////////////////////////////////////////////////////////////////////////////////////////
Entity::Entity(const std::string& name, const std::string& type, Scene *creator)
:name_(name),
type_("Entity"),
creator_(creator),
parent_(0),
visible_(true),
disable_(false),
running_(true),
zorder_(-1),
zbuffer_(0.0f),
rotation_(0.0f),	
scale_(1.0f,1.0f),
hot_(0.5,0.5),
flip_(0.0f,0.0f),
size_(0,0),
blend_(BLEND_COLORMUL_ALPHABLEND),
show_boundbox_(false),
data_(0),
extend_(0)
{
}

Entity::~Entity()
{
}

Point Entity::get_absolute_position()
{
    Point pt(position_);

    Node *node = parent_;

    while (node)
    {
        pt.x_ += node->get_position().x_;
        pt.y_ += node->get_position().y_;

        node = node->get_parent();
    }

    return pt;
}

void Entity::enter()
{
    running_ = true;
}

void Entity::exit()
{
    running_ = false;
}

void Entity::notify_attached(Node *node)
{
    parent_ = node;
}

void Entity::update(float dt)
{
}

void Entity::draw()
{
}

int Entity::number_of_action()
{
    return get_creator()->action_manager()->number_of_actions(this);
}

Action *Entity::get_action(int tag)
{
    return get_creator()->action_manager()->get_action(tag);
}

void Entity::run_action(Action *action)
{
    get_creator()->action_manager()->add_action(action, this, !running_);
}

void Entity::remove_action(Action* action)
{
    get_creator()->action_manager()->remove_action(action->get_tag());
}

void Entity::remove_action(int tag)
{
    get_creator()->action_manager()->remove_action(tag);
}

void Entity::remove_all_action()
{
    get_creator()->action_manager()->remove_all_action(this);
}

////////////////////////////////////////////////////////////////////////////////////////////
}
