#ifndef __XLBE_ANIMATION_INSTANCE_H__
#define __XLBE_ANIMATION_INSTANCE_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//���ߣ����ֱ�
//QQ: 597389076
//mail: creednew2000@163.com

//���������������Ͷ��� ��ɾ��лл��

/////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeAnimation.h"
#include "XlbeActionInterval.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

/////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Animation_Instance : public Action_Interval
{
public:
    Animation_Instance(Animation *animation, bool origin);
    virtual ~Animation_Instance();

public:
    virtual void stop() ;
    virtual void update(float time) ;
    virtual void start_with_target(Entity *target) ;

private:
    bool origin_;
	int index_;
	bool first_frame_;
    Image *origin_image_;
    Animation *animation_;
};

/////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif