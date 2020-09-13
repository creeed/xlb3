#ifndef __XLBE_LAYER_H__
#define __XLBE_LAYER_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeInput.h"
#include "XlbeNode.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Layer : public Node 
{
public:
	Layer(const std::string& name) ;
    virtual ~Layer();

public:
    virtual void on_key_char(char c);
    virtual void on_key_down(Key_Code key);
    virtual void on_key_up(Key_Code key);
    virtual void on_mouse_move(const Point &pt);
    virtual void on_mouse_down(const Point &pt, Mouse_ButtonID button_id, int click_count);
    virtual void on_mouse_up(const Point &pt, Mouse_ButtonID button_id, int click_count);
	virtual void on_mouse_wheel(const Point &pt, int delta);
    virtual void on_mouse_drag(const Point &pt);

private:

};

//////////////////////////////////////////////////////////////////////////////////////////////////////
} 

#endif
