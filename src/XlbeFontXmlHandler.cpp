#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeFont.h"
#include "XlbeImageFont.h"
#include "XlbeTtfFont.h"
#include "XlbeFontXmlHandler.h"
#include "XlbeFontManager.h"

////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////
const std::string Font_Xml_Handler::font_element_( "Font" );
const std::string Font_Xml_Handler::font_name_attribute( "Name" );
const std::string Font_Xml_Handler::font_type_attribute( "Type" );
const std::string Font_Xml_Handler::font_width_attribute( "Width" );
const std::string Font_Xml_Handler::font_height_attribute( "Height" );
const std::string Font_Xml_Handler::font_filename_attribute( "Filename" );

const std::string Font_Xml_Handler::letter_element_( "Letter" );
const std::string Font_Xml_Handler::letter_id_attribute( "ID" );
const std::string Font_Xml_Handler::letter_imagerect_attribute( "ImageRect" );

////////////////////////////////////////////////////////////////////////////////////////////
Font_Xml_Handler::Font_Xml_Handler(const std::string& filename, std::vector<Resource*> *resources)
{
	font_ = 0;
	resources_ = resources;
	script_filename_ = filename;
    Root::singleton()->xml_parser()->parse_xml_file(*this, filename);
}

Font_Xml_Handler::~Font_Xml_Handler()
{
}

void Font_Xml_Handler::element_start(const std::string& element, const Xml_Attributes& attributes)
{
    if (element == font_element_)
        element_font_start(attributes);

    else if (element == letter_element_)
        element_letter_start(attributes);
}

void Font_Xml_Handler::element_end(const std::string& element)
{
    if (element == font_element_)
        element_font_end();

    else if (element == letter_element_)
        element_letter_end();
}

void Font_Xml_Handler::element_font_start(const Xml_Attributes& attributes)
{
    type_ = attributes.get_value_as_string(font_type_attribute);
    const int width(attributes.get_value_as_integer(font_width_attribute));
    const int height(attributes.get_value_as_integer(font_height_attribute));
	const int max_width(attributes.get_value_as_integer("MaxWidth"));
	const int max_height(attributes.get_value_as_integer("MaxHeight"));
	const int bearing_y(attributes.get_value_as_integer("BearingY"));

    const std::string name(attributes.get_value_as_string(font_name_attribute));
	const std::string filename(attributes.get_value_as_string(font_filename_attribute));

    if (type_ == "Pixmap")
	{
		font_ = (Font*)Font_Manager::singleton()->create_resource(name, 0);

		if (!filename.empty())
		{
			char dir[_MAX_DIR];
			std::string image_filename;

			_splitpath( script_filename_.c_str(), 0, dir, 0, 0 );
			image_filename = dir + filename;

			((Image_Font*)font_)->set_font_size(Size(width, height)) ;
			((Image_Font*)font_)->set_texture_filename(image_filename) ;
		}
	}
	else if (type_ == "FreeType")
	{
		font_ = (Font*)Font_Manager::singleton()->create_resource(name, 1);

		((Ttf_Font*)font_)->set_font_size(Size(width, height));
		((Ttf_Font*)font_)->set_max_font_width(max_width);
		((Ttf_Font*)font_)->set_max_font_height(max_height);
		((Ttf_Font*)font_)->set_max_bearing_y(bearing_y);
	    
		if (!filename.empty())
		{
			char dir[_MAX_DIR];
			std::string ttf_filename;

			_splitpath( script_filename_.c_str(), 0, dir, 0, 0 );
			ttf_filename = dir + filename;

			((Ttf_Font*)font_)->set_ttf_filename(dir, filename) ;
		}
        
	}
	else
        throw_xml_error("no know font type."); 

	font_->prepare();
	if (resources_)
	    resources_->push_back(font_);
}

void Font_Xml_Handler::element_font_end()
{
}

void Font_Xml_Handler::element_letter_start(const Xml_Attributes& attributes)
{
    if (!font_)
        throw_xml_error("Attempt to access null object.");

    if (type_ == "Pixmap")
    {
        wchar_t id = attributes.get_value_as_integer(letter_id_attribute);
        const std::string imagerect(attributes.get_value_as_string(letter_imagerect_attribute));

		Point pt;
		Size sz;
		if (!imagerect.empty())
		{
			sscanf(imagerect.c_str(), "%f,%f,%f,%f", &pt.x_, &pt.y_, &sz.width_, &sz.height_);
		}

        static_cast<Image_Font*>(font_)->define_letter(id, pt, sz);
    }
}

void Font_Xml_Handler::element_letter_end()
{
}

////////////////////////////////////////////////////////////////////////////////////////////
}