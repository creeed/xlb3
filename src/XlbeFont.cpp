#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeFont.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////////////
Font::Font(const std::string& name)
{
	resource_type_ = "font";

    size_ = 0;
	name_ = name;
}

Font::~Font()
{
    
}

void Font::prepare()
{
	if (!is_prepared())
    {
       load_state_ = LOADSTATE_PREPARED;
    }
}

void Font::unprepare()
{
	load_state_ = LOADSTATE_UNPREPARED;
}

void Font::load()
{
    if (!is_loaded())
    {
       load_state_ = LOADSTATE_LOADED;
    }
}

void Font::unload()
{
    load_state_ = LOADSTATE_UNLOADED;
}

int	Font::get_width()
{
	return 0;
}

int	Font::get_height()
{
	return 0;
}

int Font::get_string_width(const char *s)
{
	return 0;
}

void Font::draw_string(int x, int y, const char *s, const Color_Rect &color, float rot)
{
}

void Font::draw_string(const Point &pt, const char *s, const Color_Rect &color, float rot)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
}
