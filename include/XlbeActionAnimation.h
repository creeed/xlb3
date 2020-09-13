#ifndef __XLBE_ACTION_ANIMATION_H__
#define __XLBE_ACTION_ANIMATION_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//���ߣ����ֱ�
//QQ: 597389076
//mail: creednew2000@163.com

//���������������Ͷ��� ��ɾ��лл��

/////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeAnimationResource.h"
#include "XlbeActionInterval.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

/////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Action_Animation : public Action_Interval
{
public:
	Action_Animation(const std::string &str_animation, bool origin);
    Action_Animation(Animation_Resource *animation, bool origin);
    virtual ~Action_Animation();

public:
    virtual void stop() ;
    virtual void update(float time) ;
    virtual void start_with_target(Node *target) ;

private:
    bool origin_;
	int index_;
	bool first_frame_;
    Sprite_Resource *origin_sprite_;
    Animation_Resource *animation_;
};

/////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif