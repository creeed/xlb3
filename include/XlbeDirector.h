#ifndef __XLBE_DIRECTOR_H__
#define __XLBE_DIRECTOR_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeSingleton.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

class Scene;

//////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Director : public Singleton<Director>
{
public:
    typedef std::stack<Scene*> Scenes;

public:
    Director();
    virtual ~Director();

    static Director* singleton();

public:
    void push_scene(Scene *scene);
    void pop_scene();
    void replace_scene(Scene *scene);

    void pause();
    void resume();

    Scene *get_run_scene() { return running_scene_; }
    Scene *get_next_scene() { return next_scene_; }

    void draw_scene(float dt);

private:
    void set_next_scene();

private:
    bool paused_;
    bool new_push_;
    bool runing_pop_;  

    Scene *running_scene_;
    Scene *next_scene_;

    Scenes scenes_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif