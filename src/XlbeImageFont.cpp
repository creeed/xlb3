#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeImageFont.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////////////
Image_Font::Image_Font(const std::string& name)
:Font(name)
{
	texture_ = 0;
}

Image_Font::~Image_Font()
{
}


int Image_Font::get_width()
{
	return font_size_.width_;
}

int Image_Font::get_height()
{
	return font_size_.height_;
}

int Image_Font::get_string_width(const char *s)
{
    setlocale(LC_ALL, "chs"); 
  
    size_t dsize = strlen(s) + 1;
    wchar_t *dest = new wchar_t[dsize];
    wmemset(dest, 0, dsize);
    mbstowcs(dest,s,dsize);
    setlocale(LC_ALL, "C");

	dsize = wcslen(dest);

    float width = 0.0f;
    for (int i = 0; i < dsize; ++i)
    {
		Letter *letter =  get_letter(dest[i]);
		if (letter == 0)
			throw_font_error("id font not define.");

		letter->use_count_++;
		width += letter->size_.width_;
	}

	delete [] dest;

    return width;
}

void Image_Font::draw_string(int x, int y, const char *s, const Color_Rect &color, float rot)
{
	draw_string(Point(x, y), s, color, rot);
}

void Image_Font::draw_string(const Point &pt, const char *s, const Color_Rect &color, float rot)
{
	if (texture_)
	    texture_->ckeck_loaded();

	setlocale(LC_ALL, "chs"); 
  
    size_t dsize = strlen(s) + 1;
    wchar_t *dest = new wchar_t[dsize];
    wmemset(dest, 0, dsize);
    mbstowcs(dest,s,dsize);
    setlocale(LC_ALL, "C");

	dsize = wcslen(dest);

	Point draw_point = pt;
	for (int i = 0; i < dsize; ++i)
    {
		Letter *letter =  get_letter(dest[i]);
		if (letter == 0)
			throw_font_error("id font not define.");

		float x1, y1, x2, y2;
		float tx, ty, tx1, ty1, tx2, ty2;

		x1 = 0;
		y1 = 0;
		x2 = letter->size_.width_;
		y2 = letter->size_.height_; 

		quad_.vertex_[0].x  =  x1 + draw_point.x_;
		quad_.vertex_[0].y =  y1 + draw_point.y_;

		quad_.vertex_[1].x  =  x2 + draw_point.x_;
		quad_.vertex_[1].y =  y1 + draw_point.y_;

		quad_.vertex_[2].x  =  x2 + draw_point.x_;
		quad_.vertex_[2].y =  y2 + draw_point.y_;

		quad_.vertex_[3].x  =  x1 + draw_point.x_;
		quad_.vertex_[3].y =  y2 + draw_point.y_;

		tx1 = letter->pos_.x_ / texture_->get_size().width_;
		ty1 = letter->pos_.y_ / texture_->get_size().height_;

		tx2= (letter->pos_.x_ + letter->size_.width_) / texture_->get_size().width_;
		ty2 = (letter->pos_.y_ + letter->size_.height_) / texture_->get_size().height_;

		quad_.vertex_[0].tx = tx1; quad_.vertex_[0].ty = ty1; 
		quad_.vertex_[1].tx = tx2; quad_.vertex_[1].ty = ty1; 
		quad_.vertex_[2].tx = tx2; quad_.vertex_[2].ty = ty2; 
		quad_.vertex_[3].tx = tx1; quad_.vertex_[3].ty = ty2; 

		//quad_.blend_ = blend_;
		quad_.texture_ = texture_;

		quad_.vertex_[0].color = color.top_left_.toint();
		quad_.vertex_[1].color = color.top_right_.toint();
		quad_.vertex_[2].color = color.bottom_right_.toint();
		quad_.vertex_[3].color = color.bottom_left_.toint();

		Root::singleton()->render_system()->render_quad(&quad_);

		letter->use_count_++;

		if (rot == M_PI)
		{
			draw_point.x_ -= letter->size_.width_;
		}
		else
		    draw_point.x_ += letter->size_.width_;

	}

	delete [] dest;
}

void Image_Font::prepare()
{
	if (!is_prepared())
    {
       load_state_ = LOADSTATE_PREPARED;
    }
}

void Image_Font::unprepare()
{
	load_state_ = LOADSTATE_UNPREPARED;

	undefine_all_letters();
}

void Image_Font::load()
{
    if (!is_loaded())
    {
	    texture_ = Root::singleton()->render_system()->create_texture(texture_filename_);
        load_state_ = LOADSTATE_LOADED;
    }
}

void Image_Font::unload()
{
    load_state_ = LOADSTATE_UNLOADED;
}

Image_Font::Letter *Image_Font::get_letter(wchar_t id) 
{
	Letters::iterator ifind = letters_.find(id);

	if (ifind == letters_.end())
	{
		return 0;
	}
	else 
		return ifind->second;
}

void Image_Font::define_letter(wchar_t id, const Point &pt, const Size &size)
{
    if (is_letter_defined(id))
    {
        throw_font_error(" letter is defined ");
    }

	Letter *letter = new Letter;
	letter->pos_ = pt;
	letter->size_ = size;
	letters_[id] = letter;
}

void Image_Font::undefine_letter(wchar_t id)
{
	Letters::iterator ifind = letters_.find(id);

	if (ifind == letters_.end())
		return ;

	delete ifind->second;
    letters_.erase(id);
}

void Image_Font::undefine_all_letters()
{
	Letters::iterator iend = letters_.end();
	for (Letters::iterator i = letters_.begin(); i != iend; i++)
	{
		delete i->second;
	}

    letters_.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
}
