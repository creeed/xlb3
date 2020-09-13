#ifndef __XLBE_FONT_H__
#define __XLBE_FONT_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

///////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbePoint.h"
#include "XlbeSize.h"
#include "XlbeColorRect.h"
#include "XlbeResource.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

#define LT_TOP                      0x00000000
#define LT_LEFT                     0x00000000
#define LT_CENTER                   0x00000001
#define LT_RIGHT                    0x00000002
#define LT_VCENTER                  0x00000004
#define LT_BOTTOM                   0x00000008

///////////////////////////////////////////////////////////////////////////////////////////////////
class Font : public Resource
{
public:
	Font(const std::string& name);
	virtual ~Font();

	virtual int get_width();
	virtual int get_height();
    virtual int get_string_width(const char *s);

	virtual void draw_string(int x, int y, const char *s, const Color_Rect &color, float rot = 0.0f);
    virtual void draw_string(const Point &pt, const char *s, const Color_Rect &color, float rot = 0.0f);

public:
	virtual void prepare();
	virtual void unprepare();
	virtual void load();
	virtual void unload();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif