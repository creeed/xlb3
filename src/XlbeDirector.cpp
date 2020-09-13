#include "XlbeException.h"
#include "XlbeScene.h"
#include "XlbeDirector.h"

/////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe{

template<> Director* Singleton<Director>::singleton_ = 0;
Director* Director::singleton()
{
    return singleton_;
}

/////////////////////////////////////////////////////////////////////////////////////////
Director::Director()
:paused_(false),
new_push_(false),
runing_pop_(false),
running_scene_(0),
next_scene_(0)
{
}

Director::~Director()
{
    paused_ = false;
    new_push_ = false;
    runing_pop_ = false;
    running_scene_ = 0;
    next_scene_ = 0;

    while (!scenes_.empty())
    {
        Scene *scene = scenes_.top();

        /*scene->exit();*/
        scenes_.pop();
    }
}

void Director::push_scene(Scene *scene)
{
    if (running_scene_)
    {
        scenes_.push(running_scene_);
    }

    // next_scene_ is not non, set_next_scene run 
    next_scene_ = scene;

    new_push_ = true;
    runing_pop_ = false;

	next_scene_->event_director(true);
}

void Director::pop_scene()
{
    if (scenes_.empty())
    {
        throw_scene_error("no scene in stack");
    }
    else
    {
        // next_scene_ is not non, set_next_scene run 
        next_scene_ = scenes_.top();
        scenes_.pop();

        new_push_ = false;
        runing_pop_ = true;
    }
}

void Director::replace_scene(Scene *scene)
{
    if (!running_scene_)
    {
        throw_scene_error(" no running_scene_");
    }
    else
    {
        // next_scene_ is not non, set_next_scene run 
        next_scene_ = scene;
        
        new_push_ = true;
        runing_pop_ = true;

		next_scene_->event_director(false);
    }
}

void Director::draw_scene(float dt)
{
    if (paused_)
        return;

    if (next_scene_)
        set_next_scene();

    if (running_scene_)
    {
        running_scene_->update(dt);
        running_scene_->draw();
    }
}

void Director::pause()
{
    if (paused_)
        return;

    paused_ = true;
}

void Director::resume()
{
    if (!paused_)
        return;

    paused_ = false;
}

void Director::set_next_scene()
{
    if (running_scene_ )
    {
        running_scene_->exit();
		running_scene_->event_director(false);
    }

    running_scene_ = next_scene_;
    next_scene_ = 0;

    if (new_push_)
	{
        running_scene_->enter();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
}