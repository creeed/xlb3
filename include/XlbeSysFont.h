#ifndef __XLBE_SYS_FONT_H__
#define __XLBE_SYS_FONT_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

///////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeFont.h"

#include <d3d9.h>
#include <d3dx9.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

///////////////////////////////////////////////////////////////////////////////////////////////////
class Sys_Font : public Font
{
public:
	Sys_Font(const std::string& name, const std::string& font_name, int width, int height, int weight, bool italic = false);
	virtual ~Sys_Font();

	virtual int get_height();
    virtual int get_string_width(const char *s);

	virtual void draw_string(int x, int y, int width, int height, const char *s, const Color_Rect &color, uint32_t format, uint32_t direction);
    virtual void draw_string(const Point &pt, const Size &size, const char *s, const Color_Rect &color, uint32_t format, uint32_t direction);

public:
	virtual void prepare();
	virtual void unprepare();
	virtual void load();
	virtual void unload();

private:
	int width_;
	int height_;

	ID3DXFont *font_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif