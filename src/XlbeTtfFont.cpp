#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeRenderSystem.h"
#include "XlbeTtfFont.h"

#include <shlobj.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
Ttf_Font::Ttf_Font(const std::string& name)
:Font(name)
{
	texture_ = 0;
	texture_width_ = 1024;
	texture_height_ = 1024;
	max_font_height_ = 0;
	max_font_width_ = 0;

	face_  = 0;
	library_ = 0;
	
    image_data_ = 0;
	left_blank_count_ = 0;
	pixel_bytes_ = 2;
	char_spacer_ = 5;
	image_row_ = 0;
	image_column_ = 0;
	max_bearing_y_ = 0;
}

Ttf_Font::~Ttf_Font()
{
}

int Ttf_Font::get_width()
{
	return max_font_width_;
}

int Ttf_Font::get_height()
{
	return max_font_height_;
}

int Ttf_Font::get_string_width(const char *s)
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
		{
			letter = define_letter(dest[i]);
		}

		letter->use_count_++;
		width += letter->size_.width_;
	}

	delete [] dest;

    return width;

	return 0;
}

void Ttf_Font::draw_string(int x, int y, const char *s, const Color_Rect &color, float rot)
{
    draw_string(Point(x, y), s, color, rot);
}

void Ttf_Font::draw_string(const Point &pt, const char *s, const Color_Rect &color, float rot)
{
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
		{
			letter = define_letter(dest[i]);
		}

		if (dest[i] == 32)
		{
			letter->use_count_++;
			draw_point.x_ += letter->size_.width_;
			continue;
		}

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

		tx1 = letter->pos_.x_ / texture_width_;
		ty1 = letter->pos_.y_ / texture_height_;

		tx2 = (letter->pos_.x_ + letter->size_.width_) / texture_width_;
		ty2 = (letter->pos_.y_ + letter->size_.height_) / texture_height_;

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
		draw_point.x_ += letter->size_.width_;
    }

	delete [] dest;
}

void Ttf_Font::set_ttf_filename(const std::string &dir, const std::string &filename)
{
	ttf_filename_ = dir + filename;

	if (access(ttf_filename_.c_str(), 0) == -1)
	{
		char buf[MAX_PATH] = {0};
        SHGetSpecialFolderPath(0 , buf , CSIDL_FONTS , FALSE);

		ttf_filename_ = buf;
		ttf_filename_ += "\\";
		ttf_filename_ += filename;

		if (access(ttf_filename_.c_str(), 0) == -1)
		{
			ttf_filename_.clear();

			char buf[MAX_PATH] = {0};
			SHGetSpecialFolderPath(0 , buf , CSIDL_FONTS , FALSE);

			ttf_filename_ = buf;
			ttf_filename_ += "\\";
			ttf_filename_ += "simsun.ttc";
		}
	}
}

void Ttf_Font::prepare()
{
	if (!is_prepared())
    {
       load_state_ = LOADSTATE_PREPARED;
    }
}

void Ttf_Font::unprepare()
{
	load_state_ = LOADSTATE_UNPREPARED;
}

void Ttf_Font::load()
{
	if (is_loaded())
		return;

	if(FT_Init_FreeType(&library_))
		throw_font_error("init freetype library failed!");

	if(FT_New_Face(library_, ttf_filename_.c_str(), 0, &face_)) 
	{
		throw_font_error(ttf_filename_ + "open font file failed!");
	}

	uint32_t max_face_count = face_->num_faces;
	if (FT_Set_Pixel_Sizes(face_, font_size_.width_, font_size_.height_) != 0)
        throw_font_error("Ttf_Font::update_size -- FT_Set_Pixel_Sizes failed");

	//for(uint32_t i = 33; i < 166; i++)
	//{
	//	FT_Load_Char( face_, i, FT_LOAD_RENDER );

	//	if( ( (2 * ( face_->glyph->bitmap.rows << 6 ) - face_->glyph->metrics.horiBearingY )) << 6 > max_font_height_ )
	//		max_font_height_ = (( 2 * ( face_->glyph->bitmap.rows << 6 ) - face_->glyph->metrics.horiBearingY )) >> 6;

	//	if( face_->glyph->metrics.horiBearingY > max_bearing_y_ )
	//		max_bearing_y_ = face_->glyph->metrics.horiBearingY;

	//	if( (face_->glyph->advance.x >> 6 ) + ( face_->glyph->metrics.horiBearingX >> 6 ) > max_font_width_)
	//		max_font_width_ = (face_->glyph->advance.x >> 6 ) + ( face_->glyph->metrics.horiBearingX >> 6 );
	//}

	//for(uint32_t i = 19968; i < 40869; i++)
	//{
	//	FT_Load_Char( face_, i, FT_LOAD_RENDER );

	//	if( (( 2 * ( face_->glyph->bitmap.rows << 6 ) - face_->glyph->metrics.horiBearingY ) )>> 6 > max_font_height_ )
	//		max_font_height_ = (( 2 * ( face_->glyph->bitmap.rows << 6 ) - face_->glyph->metrics.horiBearingY )) >> 6;

	//	if( face_->glyph->metrics.horiBearingY > max_bearing_y_ )
	//		max_bearing_y_ = face_->glyph->metrics.horiBearingY;

	//	if( (face_->glyph->advance.x >> 6 ) + ( face_->glyph->metrics.horiBearingX >> 6 ) > max_font_width_)
	//		max_font_width_ = (face_->glyph->advance.x >> 6 ) + ( face_->glyph->metrics.horiBearingX >> 6 );
	//}


	int data_size = texture_width_ * texture_height_ * pixel_bytes_;
	left_blank_count_ = max_face_count;
	image_data_ = new uint8_t[data_size];

	for (size_t i = 0; i < data_size; i += pixel_bytes_)
	{
		image_data_[i + 0] = 0xFF;    // luminance
		image_data_[i + 1] = 0x00;    // alpha
	}

	texture_filename_ = name_ + "/" + ttf_filename_;
	texture_ = Root::singleton()->render_system()->create_texture(texture_filename_, texture_width_, texture_height_);
    
	load_state_ = LOADSTATE_LOADED;
}

void Ttf_Font::unload()
{
	Letters::iterator iend = letters_.end();
	for (Letters::iterator i = letters_.begin(); i != iend; i++)
	{
		delete i->second;
	}

	letters_.clear();

	if (image_data_)
	{
		delete [] image_data_;
		image_data_ = 0;
	}

	if (quad_.texture_)
	{
		texture_ = 0;
		Root::singleton()->render_system()->destroy_texture(texture_filename_);
	}

	FT_Done_FreeType(library_);

	texture_width_ = 1024;
	texture_height_ = 1024;
	max_font_height_ = 0;
	max_font_width_ = 0;

	face_  = 0;
	library_ = 0;
	
    image_data_ = 0;
	left_blank_count_ = 0;
	pixel_bytes_ = 2;
	char_spacer_ = 5;
	image_row_ = 0;
	image_column_ = 0;
	max_bearing_y_ = 0;

	load_state_ = LOADSTATE_UNLOADED;
}

Ttf_Font::Letter *Ttf_Font::get_letter(wchar_t id) 
{
	Letters::iterator ifind = letters_.find(id);

	if (ifind == letters_.end())
	{
		return 0;
	}
	else 
		return ifind->second;
}

Ttf_Font::Letter *Ttf_Font::define_letter(wchar_t id)
{
	if(get_left_blank_count() == 0)    
	{
		undefine_letter(get_less_use_char());
	}

	FT_Error ftResult;

	ftResult = FT_Load_Char( face_, id, FT_LOAD_RENDER | FT_LOAD_FORCE_AUTOHINT );
	if (ftResult)
	{
		char error[256];
		sprintf(error, " cannot load CodePoint %d", id);
		throw_font_error(error);
	}

	FT_Int advance = face_->glyph->advance.x >> 6;
	uint8_t* buffer = face_->glyph->bitmap.buffer;

	if (!buffer)
	{
		if (id == 32)
		{
			Letter *letter = new Letter;
			letter->pos_.set_point(0, 0);
			letter->size_.set_size(max_font_width_ * 0.5, max_font_height_  * 0.5);
			letters_[id] = letter;

			return letter;
		}

		char error[256];
		sprintf(error, " Freetype returned null for character %d", id);
		throw_font_error(error);
	}

	int y_bearnig = ( max_bearing_y_ >> 6 ) - ( face_->glyph->metrics.horiBearingY >> 6 );
	int x_bearing = face_->glyph->metrics.horiBearingX >> 6;

	for(int j = 0; j < face_->glyph->bitmap.rows; ++j )
	{
		size_t row = j + image_row_ + y_bearnig;
		uint8_t* dest = &image_data_[(row * texture_width_ * pixel_bytes_) + (image_column_ + x_bearing) * pixel_bytes_];
		for(int k = 0; k < face_->glyph->bitmap.width; ++k )
		{
			*dest++ = 0xFF;
			*dest++ = *buffer++; 
		}
	}

	Letter *letter = new Letter;
	letter->pos_.set_point(image_column_, image_row_);
	letter->size_.set_size(face_->glyph->advance.x >> 6, max_font_height_ );
	letters_[id] = letter;

	image_column_ += (advance + char_spacer_);
	if( texture_width_ - 1 < image_column_ + ( advance ) )
	{
		image_row_ += max_font_height_ + char_spacer_;
		image_column_ = 0;
	}

	--left_blank_count_;
	texture_->ckeck_loaded();
	uint32_t *tex_data = texture_->lock(false);       

	for(uint32_t i = 0; i < texture_height_; ++i)
	{
		for(uint32_t j = 0; j < texture_width_; ++j)
		{
			uint8_t pixel = image_data_[(i * texture_height_ + j) * 2];
			uint8_t alpha = image_data_[(i * texture_height_ + j) * 2 + 1];
			tex_data[i * texture_width_ + j] = (alpha << 24) | (pixel << 16) | (pixel << 8) | pixel ;
		}
	}

	texture_->unlock();

	//texture_->save_to_file("1.png");

	return letter;
}

void Ttf_Font::undefine_letter(wchar_t id)
{
	Letters::iterator ifind = letters_.find(id);

	if (ifind == letters_.end())
		return ;

	delete ifind->second;
	letters_.erase(ifind);
}

void Ttf_Font::undefine_all_letters()
{
	Letters::iterator iend = letters_.end();
	for (Letters::iterator i = letters_.begin(); i != iend; i++)
	{
		delete i->second;
	}

    letters_.clear();
}

wchar_t Ttf_Font::get_less_use_char()
{
	Letters::iterator i = letters_.begin(), iend = letters_.end(), iless = letters_.begin();
	while(i != iend)
	{
		if(i->second->use_count_ < iless->second->use_count_)
			iless = i;

		++i;
	}

	return iless->first; 
}

int Ttf_Font::get_use_count(wchar_t id)
{
	Letters::iterator ifind = letters_.find(id);

	if (ifind == letters_.end())
		return -1;

	else return ifind->second->use_count_;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
}
