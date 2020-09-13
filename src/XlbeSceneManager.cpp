#include "XlbeException.h"
#include "XlbeScene.h"
#include "XlbeSceneManager.h"

/////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe{

template<> Scene_Manager* Singleton<Scene_Manager>::singleton_ = 0;
Scene_Manager* Scene_Manager::singleton()
{
    return singleton_;
}

/////////////////////////////////////////////////////////////////////////////////////////
Scene_Manager::Scene_Manager()
:paused_(false),
new_push_(false),
runing_pop_(false),
running_scene_(0),
next_scene_(0)
{
}

Scene_Manager::~Scene_Manager()
{
    paused_ = false;
    new_push_ = false;
    runing_pop_ = false;
    running_scene_ = 0;
    next_scene_ = 0;

    while (!scenes_.empty())
    {
        Scene *scene = scenes_.top();

        scene->exit();
        scenes_.pop();
    }
}

void Scene_Manager::push_scene(Scene *scene)
{
    if (running_scene_)
    {
        scenes_.push(running_scene_);
    }

    next_scene_ = scene;

    new_push_ = true;
    runing_pop_ = false;
}

void Scene_Manager::pop_scene()
{
    if (scenes_.empty())
    {
        throw_scene_error("no scene in stack");
    }
    else
    {
        next_scene_ = scenes_.top();
        scenes_.pop();

        new_push_ = false;
        runing_pop_ = true;
    }
}

void Scene_Manager::draw_scene(float ftime, float dt)
{
    if (paused_)
        return;

    if (next_scene_)
        set_next_scene();

    if (running_scene_)
    {
        running_scene_->update(ftime, dt);
        running_scene_->draw();
    }
}

void Scene_Manager::pause()
{
    if (paused_)
        return;

    paused_ = true;
}

void Scene_Manager::resume()
{
    if (!paused_)
        return;

    paused_ = false;
}

void Scene_Manager::set_next_scene()
{
    if (running_scene_ )
    {
        running_scene_->exit();
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