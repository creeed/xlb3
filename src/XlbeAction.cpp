#include "XlbeException.h"
#include "XlbeAction.h"

/////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

/////////////////////////////////////////////////////////////////////////////////////////
Action::Action()
:tag_(0), 
target_(0), 
duration_(0.0f),
elapsed_(0.0f),
data_(0),
auto_release_(false),
pause_(false)
{
}

Action::~Action()
{
}

void Action::reset() 
{
    elapsed_ = 0.0f;
}

uint32_t Action::get_tag() const 
{
    return tag_;
}

void Action::set_tag(uint32_t tag)
{
    tag_ = tag;
}

uint32_t Action::get_data() const
{
	return data_;
}

void Action::set_data(uint32_t data)
{
	data_ = data;
}

bool Action::is_pause() const 
{
	return pause_;
}

void Action::set_pause(bool pause)
{
	pause_ = pause;
}

void Action::pause()
{
	pause_ = true;
}

void Action::resume()
{
	pause_ = false;
}

bool Action::is_done() 
{
    return true;
}

void Action::stop() 
{
    target_ = 0; 
}

void Action::step(float dt) 
{
}

void Action::update(float time)
{
}

Node *Action::target() const 
{
    return target_;
}

void Action::start_with_target(Node *target) 
{
    target_  = target; 
}

////////////////////////////////////////////////////////////////////////////////////////////
}
