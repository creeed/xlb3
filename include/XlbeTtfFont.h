#ifndef __XLBE_TTF_FONT_H__
#define __XLBE_TTF_FONT_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

///////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeFont.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

///////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

///////////////////////////////////////////////////////////////////////////////////////////////////
class Ttf_Font : public Font
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
	Ttf_Font(const std::string& name);
	virtual ~Ttf_Font();

	virtual int get_width();
	virtual int get_height();
    virtual int get_string_width(const char *s);

	virtual void draw_string(int x, int y,  const char *s, const Color_Rect &color, float rot = 0.0f);
    virtual void draw_string(const Point &pt, const char *s, const Color_Rect &color, float rot = 0.0f);

public:
	const Size &get_font_size() { return font_size_; }
	void set_font_size(const Size &size) { font_size_ = size; }

	const std::string &get_ttf_filename() const { return ttf_filename_; }
	void set_ttf_filename(const std::string &dir, const std::string &filename) ;

	int get_max_font_width() const { return max_font_width_; }
	void set_max_font_width(int max_font_width) { max_font_width_ = max_font_width; }

	int get_max_font_height() const { return max_font_height_; }
	void set_max_font_height(int max_font_height) { max_font_height_ = max_font_height; }

	int get_max_bearing_y() const { return  max_bearing_y_; }
	void set_max_bearing_y(int max_bearing_y) { max_bearing_y_ = max_bearing_y; }

    bool is_letter_defined(wchar_t id) const { return letters_.find(id) != letters_.end(); }
	Letter *get_letter(wchar_t id);
	Letter *define_letter(wchar_t id);
	void undefine_letter(wchar_t id);
	void undefine_all_letters();

public:
	virtual void prepare();
	virtual void unprepare();
	virtual void load();
	virtual void unload();

private:
	void insert_glyph_info(wchar_t id);
	void remove_glyph(wchar_t id);
	Letter *renderglyph_into_texture(wchar_t id);

	wchar_t get_less_use_char();
	int get_use_count(wchar_t id);
	uint32_t get_left_blank_count() const { return left_blank_count_; }

private:
	Size font_size_;
	std::string ttf_filename_;
	std::string texture_filename_;

private:
    int texture_width_;
	int texture_height_;
	int max_font_height_;
	int max_font_width_;

	FT_Face face_;
	FT_Library library_;
	
    uint8_t *image_data_;
	uint32_t left_blank_count_;
	uint32_t pixel_bytes_;
	uint32_t char_spacer_;
	uint32_t image_row_;
	uint32_t image_column_;
	int max_bearing_y_;

	Letters letters_;
	Render_Texture *texture_;
	Render_Quad quad_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif