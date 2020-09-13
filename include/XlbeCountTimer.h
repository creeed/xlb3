#ifndef __XLBE_COUNT_TIMER_H__
#define __XLBE_COUNT_TIMER_H__

////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Count_Timer
{
public:
	Count_Timer() 
	{
		opered_ = false;

		timer_term_ = 0;
		timer_old_ = 0;
	}

	~Count_Timer() { }

public:
	void cleanup()
	{
		opered_ = false;

		timer_term_ = 0;
		timer_old_ = 0;
	}

	bool is_set_timer() { return opered_; }
	void set_term_time(uint32_t term) { timer_term_ = term; }
	uint32_t get_term_time() { return timer_term_; }
	uint32_t get_tick_old_time() { return timer_old_; }

	void begin_timer(uint32_t term, uint32_t now) 
	{
		opered_ = true;

		timer_term_ = term;
		timer_old_ = now;
	}

	bool counting_timer(uint32_t now)
	{
		if (!opered_)
			return false;

		uint32_t newa = now;

		if(newa < timer_old_ + timer_term_ )
			return false;

		timer_old_ = newa;

		return true;
	}

	uint32_t get_leave_time(uint32_t now) 
	{
		if(!counting_timer(now))
		{
			return timer_term_ + timer_old_ - now;
		}

		return 0;
	}

private:
	bool opered_;

	uint32_t timer_term_;
	uint32_t timer_old_;
};

/////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif