#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeSpriteResource.h"
#include "XlbeSpriteResourceManager.h"
#include "XlbeSpriteXmlHandler.h"
#include "XlbeColorRect.h"

////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////
const std::string Sprite_Xml_Handler::sprite_element_( "Sprite" );
const std::string Sprite_Xml_Handler::sprite_name_attribute( "Name" );
const std::string Sprite_Xml_Handler::sprite_imagerect_attribute( "ImageRect" );
const std::string Sprite_Xml_Handler::sprite_imagefile_attribute( "Imagefile" );
const std::string Sprite_Xml_Handler::sprite_colorrect_attribute( "ColorRect" );
const std::string Sprite_Xml_Handler::sprite_rotation_attribute( "Rotation" );
const std::string Sprite_Xml_Handler::sprite_hot_attribute( "Hot" );
const std::string Sprite_Xml_Handler::sprite_blend_attribute( "Blend" );
const std::string Sprite_Xml_Handler::sprite_flip_attribute( "Flip" );
const std::string Sprite_Xml_Handler::sprite_srcrect_attribute( "SrcRect" );

////////////////////////////////////////////////////////////////////////////////////////////
Sprite_Xml_Handler::Sprite_Xml_Handler(const std::string& filename, std::vector<Resource*> *resources)
{
	resources_ = resources;
	script_filename_ = filename;
    Root::singleton()->xml_parser()->parse_xml_file(*this, filename);
}

Sprite_Xml_Handler::~Sprite_Xml_Handler()
{
}

void Sprite_Xml_Handler::element_start(const std::string& element, const Xml_Attributes& attributes)
{
    if (element == sprite_element_)
        element_sprite_start(attributes);
}

void Sprite_Xml_Handler::element_end(const std::string& element)
{
    if (element == sprite_element_)
        element_sprite_end();
}

void Sprite_Xml_Handler::element_sprite_start(const Xml_Attributes& attributes)
{
	int blend(attributes.get_value_as_integer(sprite_blend_attribute));
	float rotation(attributes.get_value_as_float(sprite_rotation_attribute));

    const std::string name(attributes.get_value_as_string(sprite_name_attribute));
	const std::string image_rect(attributes.get_value_as_string(sprite_imagerect_attribute));
	const std::string image_file(attributes.get_value_as_string(sprite_imagefile_attribute));
	const std::string color_rect(attributes.get_value_as_string(sprite_colorrect_attribute));
	const std::string src_rect(attributes.get_value_as_string(sprite_srcrect_attribute));
	const std::string filp(attributes.get_value_as_string(sprite_flip_attribute));
	const std::string hot(attributes.get_value_as_string(sprite_hot_attribute));

	Sprite_Resource *spr_res = (Sprite_Resource *)Sprite_Resource_Manager::singleton()->create_resource(name, 0);

    spr_res->set_rotation(rotation) ;
    spr_res->set_blend((Render_Blend)blend);

	//if (!color_rect.empty())
	//{
	//	int top_left_;
 //       int top_right_;
 //       int bottom_left_;
 //       int bottom_right_;
	//	sscanf(color_rect.c_str(), "#%x #%x #%x #%x", &top_left_, &top_right_, &bottom_left_, &bottom_right_);

	//	spr_res->set_color_rect(Color_Rect(Color(top_left_), Color(top_right_), Color(bottom_left_), Color(bottom_right_)));
	//}

	//if (!filp.empty())
	//{
	//	Size size;
	//	sscanf(filp.c_str(), "%f,%f", &size.width_, &size.height_);
	//	spr_res->set_flip(size);
	//}
	//
	//if (!hot.empty())
	//{
	//	Point pt;
	//	sscanf(hot.c_str(), "%f,%f", &pt.x_, &pt.y_);
	//	spr_res->set_hot(pt);
	//}

	//if (!src_rect.empty())
	//{
	//	Rect rc;
 //       sscanf(src_rect.c_str(), "%f,%f,%f,%f", &rc.left_, &rc.top_, &rc.right_, &rc.bottom_);
	//	spr_res->set_src_rect(rc) ;
	//}

	if (!image_rect.empty())
	{
		Rect rc;
		float x, y;

        sscanf(image_rect.c_str(), "%f,%f,%f,%f", &rc.left_, &rc.top_, &x, &y);

		rc.right_ = rc.left_ + x;
		rc.bottom_ = rc.top_ + y;

		spr_res->set_texture_pos(rc.get_position());
	    spr_res->set_texture_size(rc.get_size());
	}

	if (!image_file.empty())
	{
		char dir[_MAX_DIR];
		std::string texture_filename;

	    _splitpath( script_filename_.c_str(), 0, dir, 0, 0 );
	    texture_filename = dir + image_file;
		spr_res->set_texture_filename(texture_filename) ;
	}

	spr_res->prepare();
	if (resources_)
	    resources_->push_back(spr_res);
}

void Sprite_Xml_Handler::element_sprite_end()
{
}

////////////////////////////////////////////////////////////////////////////////////////////
}