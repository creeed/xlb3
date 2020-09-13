#include "XlbeException.h"
#include "XlbeNode.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {	

////////////////////////////////////////////////////////////////////////////////////////////
Node::Node(const std::string& name)
:name_(name),
parent_(0),
visible_(true),
hot_(0.5f, 0.5f),
scale_(1.0f,1.0f),
rotation_(0.0f),
blend_(BLEND_COLORMUL_ALPHABLEND),
data_(0)
{
}

Node::~Node()
{
	remove_all_action();
}

Point Node::get_absolute_position() 
{
    Node *node = this;

    Point pt(position_);
    while (node = node->get_parent())
    {
        pt.x_ += node->get_position().x_;
        pt.y_ += node->get_position().y_;
    }

    return pt;
}

Node* Node::get_child(int index) const
{
	if (index >= childs_.size())
		return 0;

	return *(childs_.begin() + index);	 
}

int Node::number_of_children() const
{
	return childs_.size();
}

void Node::insert_child(Node* child, int index)
{
    if (child->get_parent())
    {
        throw_scene_error(child->get_name() + " already was a child of " +
            child->get_parent()->get_name());
    }

	if (index == -1)
	{
        childs_.push_back(child);
	}
	else if (index >= childs_.size())
	{
		childs_.push_back(child);
	}
	else
	{
		childs_.insert(childs_.begin() + index, child);
	}

    child->set_parent(this);
}

void Node::remove_child(int index)
{
	if (index >= childs_.size())
		return;

	Node* child = *(childs_.begin() + index);
	childs_.erase(childs_.begin() + index);
	child->set_parent(0);
}

void Node::remove_child(Node* child)
{
	childs_.erase(std::remove(childs_.begin(), childs_.end(), child), childs_.end());
	child->set_parent(0);
}

void Node::remove_all_children()
{
    Nodes::iterator iend = childs_.end();
    for (Nodes::iterator i = childs_.begin(); i != iend; ++i)
    {
        (*i)->set_parent(0);
    }

    childs_.clear();
}

void Node::enter()
{
    Nodes::iterator iend = childs_.end();
   
    for (Nodes::iterator i = childs_.begin(); i != iend; ++ i)
    {
        (*i)->enter();
    }
}

void Node::exit()
{
    Nodes::iterator iend = childs_.end();
   
    for (Nodes::iterator i = childs_.begin(); i != iend; ++ i)
    {
        (*i)->exit();
    }
}

void Node::update(float ftime, float dt)
{
	action_update(dt);

    Nodes::iterator iend = childs_.end();
   
    for (Nodes::iterator i = childs_.begin(); i != iend; ++ i)
    {
        (*i)->update(ftime, dt);
    }
}

void Node::draw()
{
    Nodes::iterator iend = childs_.end();
   
    for (Nodes::iterator i = childs_.begin(); i != iend; ++ i)
    {
		if ((*i)->is_visible())
            (*i)->draw();
    }
}

void Node::action_update(float dt)
{
	Action *act;

    for (Actions::iterator i = actions_.begin(); i != actions_.end(); )
    {
		act = (*i);

		if (act->is_done())
		{
			delete act;
            i = actions_.erase(i);
		}
		else 
		{
			if (!act->is_pause())
			{
			    act->step(dt);
			}

			i++;
		}   
	}
}

bool Node::run_action(Action *action, bool pause)
{
	action->set_pause(pause);
	actions_.push_back(action);

	action->start_with_target(this);

	return true;
}

void Node::pause_action(Action *action)
{
	//Actions::iterator iend = actions_.end();
 //  
 //   for (Actions::iterator i = actions_.begin(); i != iend; ++ i)
 //   {
	//	if ((*i) == action)
	//		(*i)->pause();
 //   }

	action->pause();
}

void Node::resume_action(Action *action)
{
	//Actions::iterator iend = actions_.end();
 //  
 //   for (Actions::iterator i = actions_.begin(); i != iend; ++ i)
 //   {
	//	if ((*i) == action)
	//		(*i)->resume();
 //   }

	action->resume();
}

Action *Node::get_action(int index)
{
	if (index < 0 || index > number_of_action())
		return 0;

	int count = 0;
	Actions::iterator iend = actions_.end();
    for (Actions::iterator i = actions_.begin(); i != iend; ++ i)
    {
		if (index == count)
		{
			return (*i);
		}

		count ++;
    }

	return 0;
}

void Node::remove_action(Action *action)
{
	Actions::iterator iend = actions_.end();
   
    for (Actions::iterator i = actions_.begin(); i != iend; ++ i)
    {
		if ((*i) == action)
		{
			actions_.erase(i);
			break;
		}
    }
}

void Node::remove_all_action()
{
	Actions::iterator iend = actions_.end();
   
    for (Actions::iterator i = actions_.begin(); i != iend; ++ i)
    {
		delete (*i);
    }

    actions_.clear();
}

void Node::pause_all_action()
{
	Actions::iterator iend = actions_.end();
   
    for (Actions::iterator i = actions_.begin(); i != iend; ++ i)
    {
		(*i)->pause();
    }
}

void Node::resume_all_action()
{
	Actions::iterator iend = actions_.end();
   
    for (Actions::iterator i = actions_.begin(); i != iend; ++ i)
    {
		(*i)->resume();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
}