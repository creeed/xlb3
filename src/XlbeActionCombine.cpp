#include "XlbeException.h"
#include "XlbeActionInterval.h"
#include "XlbeActionCombine.h"

/////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

///////////////////////////////////////////////////////////////////////////////////////////
Action_Sequence::Action_Sequence(Action *act1, ...)
:Action_Interval(0)
{
    va_list params;
    va_start(params, act1);	

	Action *now;
	actions_.push_back(act1);
	duration_ += act1->duration();

	while(act1)
	{
		now = va_arg(params, Action*);

		if ( now )
		{
			actions_.push_back(now);
			duration_ += now->duration();
		}
		else
			break;
	}

    va_end(params);

	index_ = 0;
}

Action_Sequence::~Action_Sequence()
{
	int size = actions_.size();
	for (int i = 0; i < size; i++)
	{
		delete actions_[i];
	}
}

void Action_Sequence::stop()
{
    Action_Interval::stop();
}

void Action_Sequence::step(float dt)
{
	elapsed_ += dt;

	float time = dt;
	float left = 0;
	Action *act = 0;
	int size = actions_.size();
	
	for (; index_ < size; index_++)
	{
		act = actions_[index_];

		if (act->elapse() == 0.0f)
		{
			act->start_with_target(target_);
		}

		left = act->duration() - act->elapse();
		if (left > 0.0f)
			left = time - left;
		else
			left = time;

		act->step(time);

		if (act->elapse() < act->duration())
		{
			break;
		}
		else
		{
			act->stop();
			
			time = left;
		}
	}

	if (elapsed_ >= duration_)
	{
		for (; index_ < size; index_++)
		{
			act = actions_[index_];

			if (act->elapse() == 0.0f)
			{
				act->start_with_target(target_);
			}

			left = (act->duration() - act->elapse());

			if (left > 0.0f)
			    act->step(left);

     		act->stop();
		}
	}
}

void Action_Sequence::start_with_target(Node *target)
{
    Action_Interval::start_with_target(target);

	int size = actions_.size();
	for (int i = 0; i < size; i++)
	{
		actions_[i]->reset();
	}

	index_ = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////
Action_Spawn::Spawn::Spawn(Action *act1, Action *act2)
:Action_Interval(0)
{
    actions_[0] = (Action_Interval *)act1;
    actions_[1] = (Action_Interval *)act2;

	float d1, d2;

	d1 = actions_[0]->duration();
	d2 = actions_[1]->duration();

	if (d1 > d2)
	{
		actions_[1] = new Action_Sequence(actions_[1], Action_Delay(d1 - d2), 0);
	}
	else if (d1 < d2)
	{
		actions_[0] = new Action_Sequence(actions_[0], Action_Delay(d2 - d1), 0);
	}

	duration_ = std::max(actions_[0]->duration(), actions_[1]->duration());
}

Action_Spawn::Spawn::~Spawn()
{
    delete actions_[0];
    delete actions_[1];
}

void Action_Spawn::Spawn::update(float time)
{
	actions_[0]->update(time);
	actions_[1]->update(time);
}

void Action_Spawn::Spawn::stop()
{
    actions_[0]->stop();
    actions_[1]->stop();

    __super::stop();
}

void Action_Spawn::Spawn::start_with_target(Node *target)
{
    __super:: start_with_target(target);	

    actions_[0]->start_with_target(target);
    actions_[1]->start_with_target(target);
}

Action_Spawn::Action_Spawn(Action *act1, ...)
:Action_Interval(0)
{
    va_list params;
    va_start(params,act1);	

    Action_Interval *now;
    Action_Interval *prev = (Action_Interval *)act1;

    while( act1 ) 
    {
        now = va_arg(params,Action_Interval*);
        if ( now )
        {
            prev = new Spawn(prev, now);
        }
        else
            break;
    }

    va_end(params);

    duration_ = prev->duration();

    spawn_ = (Spawn *)prev;
}

Action_Spawn::~Action_Spawn()
{
    delete spawn_;
}

void Action_Spawn::stop()
{
    spawn_->stop();

    __super::stop();
}

void Action_Spawn::update(float time)
{
    spawn_->update(time);
}

void Action_Spawn::start_with_target(Node *target)
{
    __super::start_with_target(target);

    spawn_->start_with_target(target);
}

/////////////////////////////////////////////////////////////////////////////////////////
Action_Repeat_Forever::Action_Repeat_Forever(Action *a)
:stop_(false),
other_(a)
{
}

Action_Repeat_Forever::~Action_Repeat_Forever()
{
    if (other_)
    {
        delete other_;
    }
}

void Action_Repeat_Forever::step(float dt)
{
    other_->step(dt);
    if( other_->is_done()) 
    {
        other_->stop();
        other_->start_with_target(target_);
    }
}

void Action_Repeat_Forever::start_with_target(Node *target)
{
    __super::start_with_target(target);

	other_->start_with_target(target);
}

/////////////////////////////////////////////////////////////////////////////////////////
}