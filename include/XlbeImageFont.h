#ifndef __XLBE_IMAGE_FONT_H__
#define __XLBE_IMAGE_FONT_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

///////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeFont.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

///////////////////////////////////////////////////////////////////////////////////////////////////
class Image_Font : public Font
{
public:
	struct Letter
	{
		Point pos_;
	    Size size_;
		int use_count_;

		Letter() { use_count_ = 0;}
	};

public:
    typedef std::map<wchar_t, Letter*> Letters;

public:
	Image_Font(const std::string& name);
	virtual ~Image_Font();

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

public:
	const Size &get_font_size() { return font_size_; }
	void set_font_size(const Size &size) { font_size_ = size; }

	const std::string &get_texture_filename() const { return texture_filename_; }
	void set_texture_filename(const std::string &filename) { texture_filename_ = filename; }

    bool is_letter_defined(wchar_t id) const { return letters_.find(id) != letters_.end(); }
	Letter *get_letter(wchar_t id) ;
	void define_letter(wchar_t id, const Point &pt, const Size &size);
	void undefine_letter(wchar_t id);
	void undefine_all_letters();

private:
	std::string texture_filename_;

	Render_Quad quad_;
	Render_Texture *texture_;
    Letters letters_;

    Size font_size_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif