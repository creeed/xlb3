#ifndef __XLBE_ACTION_COMBINE_H__
#define __XLBE_ACTION_COMBINE_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

/////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeAction.h"
#include "XlbeActionInterval.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

/////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Action_Sequence : public Action_Interval
{
public:
	typedef std::vector<Action*> Actions;

public:
    Action_Sequence(Action *act1, ...);
    virtual ~Action_Sequence();

public:
	virtual void step(float dt) ;
    virtual void stop();

    virtual void start_with_target(Node *target);

private:
	int index_;
	Actions actions_;

};

/////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Action_Spawn : public Action_Interval
{
private:
    class Spawn : public Action_Interval
    {
    public:
        Spawn(Action *act1, Action *act2);
        ~Spawn();

    public:
        virtual void update(float time);
        virtual void stop();

        virtual void start_with_target(Node *target);

    private:
        float split_;
        int last_;
        Action_Interval *actions_[2];
    };

public:
    Action_Spawn(Action *act1, ...);
    virtual ~Action_Spawn();

public:
    virtual void update(float time);
    virtual void stop();

    virtual void start_with_target(Node *target);

private:
    Spawn *spawn_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Action_Repeat_Forever : public Action
{
public:
    Action_Repeat_Forever(Action *a);
    virtual ~Action_Repeat_Forever();

public:
    virtual bool is_done() { return stop_; }
    virtual void stop() { other_->stop(); stop_ = true; target_ = 0; }

    virtual void step(float dt);
    virtual void start_with_target(Node *target);

private:
    bool stop_;
    Action *other_;
};

/////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif