#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeSysFont.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////////////
Sys_Font::Sys_Font(const std::string& name, const std::string& font_name, int width, int height, int weight, bool italic)
{
    name_ = name;
    size_ = 0;

	width_ = width;
	height_ = height;

	font_ = 0;

	D3DXFONT_DESC font;
	memset(&font,0,sizeof(font));
	font.Height = height;
	font.Width = width;
	font.Weight = weight;
	font.Italic = italic;
	font.MipLevels = 0;
	font.OutputPrecision = OUT_DEFAULT_PRECIS;
	font.PitchAndFamily = DEFAULT_PITCH;
	font.Quality = DEFAULT_QUALITY;
	font.CharSet = DEFAULT_CHARSET;
	strcpy(font.FaceName, font_name.c_str());

	D3DXCreateFontIndirect((LPDIRECT3DDEVICE9)Root::singleton()->render_system()->get_device(), &font, &font_);
}

Sys_Font::~Sys_Font()
{
}

void Sys_Font::prepare()
{
	if (!is_prepared())
    {
       load_state_ = LOADSTATE_PREPARED;
    }
}

void Sys_Font::unprepare()
{
	//load_state_ = LOADSTATE_UNPREPARED;
}

void Sys_Font::load()
{
    if (!is_loaded())
    {
       load_state_ = LOADSTATE_LOADED;
    }
}

void Sys_Font::unload()
{
    load_state_ = LOADSTATE_UNLOADED;
}

int Sys_Font::get_height()
{
	return height_;
}

int Sys_Font::get_string_width(const char *s)
{
	return width_ * lstrlen(s);
}

void Sys_Font::draw_string(int x, int y, int width, int height, const char *s, const Color_Rect &color, uint32_t format, uint32_t direction)
{
  RECT rect;

  if(font_ == 0)
  {
	  return ;
	  
  }
    
  if(!width) width = 65535;
  if(!height) height = 65536;

  rect.left   = x;
  rect.top    = y;
  rect.right  = rect.left + width;
  rect.bottom = rect.top + height;

  
  if(FAILED(font_->DrawText(0, s, -1, &rect, format, D3DCOLOR_ARGB(color.top_left_.alpha(), color.top_left_.red(), color.top_left_.green(), color.top_left_.blue()))))
    return ;

  return ;
}

void Sys_Font::draw_string(const Point &pt, const Size &size, const char *s, const Color_Rect &color, uint32_t format, uint32_t direction)
{
	draw_string(pt.x_, pt.y_, size.width_, size.height_, s, color, format, direction);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
}
