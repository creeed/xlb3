#include "XlbeException.h"
#include "XlbeRenderSystem.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
Render_System::Render_System()
{
	geometry_width_ = 800;
	geometry_height_ = 600;

	texture_filter_ = false;
}

Render_System::~Render_System()
{
}

Rect Render_System::get_geometry_rect()  
{
    return Rect(Point(0,0), Size(geometry_width_, geometry_height_));
}

/////////////////////////////////////////////////////////////////
}