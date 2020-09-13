#ifndef __XLBE_LABEL_H__
#define __XLBE_LABEL_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"

#include "XlbeSprite.h"
#include "XlbeFontManager.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Label : public Node
{
public:
    Label(const std::string& name) ;
    virtual ~Label() ;

public:
    virtual Font *get_font() const ;
    virtual void set_font(const std::string &font);

	void set_bk_image(const std::string &image);

    virtual const std::string &get_text() const { return text_; }
    virtual void set_text(const std::string &text) ;
	virtual void set_text_color(const Color &color) { color_.set_color(color); }
	virtual void set_text_color(const Color_Rect &color) { color_ = color; }

    virtual uint32_t get_format() { return format_; }
    virtual uint32_t set_format(uint32_t format) { uint32_t old=format_; format_=format;  return old; }

    virtual void draw();

private:
    std::string text_;

    Font *font_;
	uint32_t format_;
	Color_Rect color_;

	Sprite *spr_bk_;

};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif