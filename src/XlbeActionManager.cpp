#include "XlbeException.h"
#include "XlbeActionManager.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

/////////////////////////////////////////////////////////////////////////////////////////////////
Action_Manager::Action_Manager()
{
    tag_ = 0;
}

Action_Manager::~Action_Manager()
{
    for (Elements::iterator i = elements_.begin(); i != elements_.end(); ++i)
    {
        delete i->second;
    }

    elements_.clear();

    for (Erases::iterator i = erases_.begin(); i != erases_.end(); ++i)
    {
		delete (*i);  
    }

	erases_.clear();

    for (Inserts::iterator i = inserts_.begin(); i != inserts_.end(); ++i)
    {
		delete (*i);  
    }

	inserts_.clear();
}

void Action_Manager::initialise()
{
	tag_ = 0;
}

void Action_Manager::cleanup()
{
	tag_ = 0;

	for (Elements::iterator i = elements_.begin(); i != elements_.end(); ++i)
	{
		delete i->second;
	}

	elements_.clear();

	for (Erases::iterator i = erases_.begin(); i != erases_.end(); ++i)
	{
		delete (*i);  
	}

	erases_.clear();

	for (Inserts::iterator i = inserts_.begin(); i != inserts_.end(); ++i)
	{
		delete (*i);  
	}

	inserts_.clear();
}

void Action_Manager::update(float dt)
{
	Action *act;

	prepare();

    for (Elements::iterator i = elements_.begin(); i != elements_.end(); ++i)
    {
		act = i->second;

		if (act->is_done())
		{
			Erases::iterator j = std::find(erases_.begin(), erases_.end(), i->second);
			if (j == erases_.end())
		        erases_.push_back(act);
		}
		else 
		{
			if (!act->is_pause())
			    act->step(dt);
		}   
	}
}

void Action_Manager::pause_target(Entity *target)
{
    Elements::iterator i;
    Elements::iterator iend = elements_.end();

    for (i = elements_.begin(); i != iend; ++i)
    {
		if (i->second->target() == target)
            i->second->pause();
    }
}

void Action_Manager::resume_targer(Entity *target)
{
    Elements::iterator i;
    Elements::iterator iend = elements_.end();

    for (i = elements_.begin(); i != iend; ++i)
    {
		if (i->second->target() == target)
            i->second->resume();
    }
}

int Action_Manager::number_of_actions(Entity *target)
{
	int count = 0;

    Elements::iterator i;
    Elements::iterator iend = elements_.end();

    for (i = elements_.begin(); i != iend; ++i)
    {
		if (i->second->target() == target)
            count ++;
    }

    return count;
}

Action *Action_Manager::get_action(uint32_t tag)
{
    Elements::iterator i = elements_.find(tag);

	if (i == elements_.end())
    {
        return 0;
    }

	Erases::iterator j;
    Erases::iterator jend = erases_.end();
	for (j = erases_.begin(); j != jend; ++j)
    {
		if ((*j)->get_tag() == tag)
			return 0;
    }

    return i->second;
}

void Action_Manager::add_action(Action *action, Entity *target, bool pause)
{
	uint32_t tag = tag_factory();

    Elements::iterator i = elements_.find(tag);

    if (i != elements_.end())
    {
        throw_scene_error("action id is in manager !");
    }

	action->set_tag(tag);
	action->set_pause(pause);
    action->start_with_target(target);

	inserts_.push_back(action);
}

void Action_Manager::remove_action(uint32_t tag)
{
    Elements::iterator i = elements_.find(tag);

    if (i == elements_.end())
    {
        //throw_scene_error("action id is not in manager !");
		return;
    }

	Erases::iterator j = std::find(erases_.begin(), erases_.end(), i->second);
	if (j == erases_.end())
	    erases_.push_back(i->second);
}

void Action_Manager::remove_all_action(Entity *target)
{
    Elements::iterator i;
    Elements::iterator iend = elements_.end();

	for (i = elements_.begin(); i != iend; ++i)
    {
		if (i->second->target() == target)
		{
			Erases::iterator j = std::find(erases_.begin(), erases_.end(), i->second);
			if (j == erases_.end())
                erases_.push_back(i->second);
		}
    }
}

void Action_Manager::prepare()
{
	Erases::iterator i;
    Erases::iterator iend = erases_.end();

    for (i = erases_.begin(); i != iend; ++i)
    {
		uint32_t tag = (*i)->get_tag();
		delete (*i);
		elements_.erase(tag);   
    }

	erases_.clear();

	Inserts::iterator j;
    Inserts::iterator jend = inserts_.end();
	for (j = inserts_.begin(); j != jend; ++j)
    {
		elements_.insert(Elements::value_type((*j)->get_tag(), (*j)));   
    }

	inserts_.clear();
}

uint32_t Action_Manager::tag_factory()
{
	tag_ ++;

	if (tag_ == 0)
		tag_ ++;

	return tag_;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
}