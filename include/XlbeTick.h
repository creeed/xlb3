#ifndef __XLBE_TICK_H__
#define __XLBE_TICK_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//class Xlbe_Export Tick 
//{    
//public:
//    Tick() { reset(); }
//    ~Tick() {}
//
//public:
//    uint32_t get_milli_seconds()
//    {
//		current_tick_ = GetTickCount();
//        return (current_tick_ - start_tick_) ;
//    }
//
//    uint32_t get_micro_seconds()
//    {
//		current_tick_ = GetTickCount();
//        return  (current_tick_ - start_tick_ ) * 1000.0   ;
//    }
//
//    void reset() { start_tick_ = current_tick_ = GetTickCount(); }
//
//private:
//    uint32_t start_tick_;
//    uint32_t current_tick_;
//};

class Xlbe_Export Tick 
{    
public:
    Tick()    { reset(); }
    ~Tick()   {}

    void reset()  { zero_clock_ = clock(); }

    unsigned long get_milli_seconds()
    {
        clock_t newclock = clock();
        return (unsigned long)( (float)( newclock - zero_clock_ ) / ( (float)CLOCKS_PER_SEC / 1000.0 ) ) ;
    }

    unsigned long get_micro_seconds()
    {
        clock_t newclock = clock();
        return (unsigned long)( (float)( newclock - zero_clock_ ) / ( (float)CLOCKS_PER_SEC / 1000000.0 ) ) ;
    }

private:
    clock_t zero_clock_;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif 