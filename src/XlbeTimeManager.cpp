#include "XlbeTimeManager.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////
template<> Time_Manager* Singleton<Time_Manager>::singleton_ = 0;
Time_Manager* Time_Manager::singleton()
{
    return singleton_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
Time_Manager::Time_Manager()
{
	start_time_ = 0 ;
	current_time_ = 0 ;
}

Time_Manager::~Time_Manager()
{
    cleanup();
}

bool Time_Manager::initialise()
{
	start_time_ = GetTickCount() ;
	current_time_ = GetTickCount() ;

	return true;
}

void Time_Manager::cleanup()
{
}

uint32_t Time_Manager::current_time( )
{
	current_time_ = GetTickCount() ;

	return current_time_ ;
}

////////////////////////////////////////////////////////////////////////////////////////////
}
