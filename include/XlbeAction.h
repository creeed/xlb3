#ifndef __XLBE_ACTION_H__
#define __XLBE_ACTION_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

/////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

class Node;

/////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Action
{
public:
    Action();
    virtual ~Action();

public:
    uint32_t get_tag() const ;
    void set_tag(uint32_t tag);

	uint32_t get_data() const;
	void set_data(uint32_t data);

	bool is_auto_release() const { return auto_release_; }
	void set_auto_release(bool auto_release) { auto_release_ = auto_release; }

	bool is_pause() const ;
	void set_pause(bool pause);

	float duration() const { return duration_; }
    void set_duration(float d) { duration_ = d; }

	float elapse() const { return elapsed_; }
    void set_elapse(float e) { elapsed_ = e; }

	void pause();
    void resume();

    Node *target() const ;
    virtual void start_with_target(Node *target) ;

    virtual void reset() ;

    virtual bool is_done() ;
    virtual void stop() ;

    virtual void step(float dt) ;
    virtual void update(float time) ;

protected:
    uint32_t tag_;
	bool auto_release_;
	bool pause_;
	uint32_t data_;
    Node *target_;
	float duration_;
	float elapsed_;
};

/////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif