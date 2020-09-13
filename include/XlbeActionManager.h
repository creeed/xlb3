#ifndef __XLBE_ACTION_MANAGER_H__
#define __XLBE_ACTION_MANAGER_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeEntity.h"
#include "XlbeAction.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Action_Manager 
{
public:
    typedef std::map<uint32_t, Action*> Elements;
    typedef std::vector<Action*> Erases;
    typedef std::vector<Action*> Inserts;

public:
    Action_Manager();
    virtual ~Action_Manager();

public:
	void initialise();
	void cleanup();

	void prepare();
    void update(float dt);

    void pause_target(Entity *target);
    void resume_targer(Entity *target);

    int number_of_actions(Entity *target);
    Action *get_action(uint32_t tag);
    void add_action(Action *action, Entity *target, bool pause);
    void remove_action(uint32_t tag) ;
    void remove_all_action(Entity *target) ;

protected:
	uint32_t tag_factory();

private:
	uint32_t tag_;

	Erases erases_;
	Inserts inserts_;
    Elements elements_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif