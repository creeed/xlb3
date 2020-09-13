#ifndef __XLBE_MOUSE_CURSOR_H__
#define __XLBE_MOUSE_CURSOR_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeSingleton.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

class Sprite;

//////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Mouse_Cursor : public Singleton<Mouse_Cursor>
{
public:
    Mouse_Cursor() ;
    virtual ~Mouse_Cursor() ;

    static Mouse_Cursor* singleton();

public:
    Sprite* get_cursor() const { return spr_cursor_; }  
    void set_cursor(const std::string& spr_res);

    Point get_position() const {return Point(position_.x_, position_.y_); }
	void set_position(const Point& position);
	void offset_position(const Point& offset);

	virtual Point get_centrepoint() const { return centrepoint_; }
    virtual void set_centrepoint(const Point &centrepoint)  { centrepoint_ = centrepoint; } 

    Rect get_constraint_area() const;
    void set_constraint_area(const Rect* area);

    bool is_visible(void) const	{ return visible_; }
    void set_visible(bool visible) { visible_ = visible; }
 
	void hide() { visible_ = false; }
	void show() { visible_ = true; }

    void draw() ;

private:
    void constrain_position();

private:
	Sprite* spr_cursor_;

	bool visible_;
	Point position_;					
	Point centrepoint_; 
	Rect constraints_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif