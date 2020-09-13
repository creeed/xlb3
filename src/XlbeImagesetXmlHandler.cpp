#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeImageset.h"
#include "XlbeImagesetXmlHandler.h"

////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////
const std::string Imageset_Xml_Handler::imageset_element_( "Imageset" );
const std::string Imageset_Xml_Handler::image_element_( "Image" );
const std::string Imageset_Xml_Handler::imageset_name_attribute( "Name" );
const std::string Imageset_Xml_Handler::imageset_imagefile_attribute( "Imagefile" );
const std::string Imageset_Xml_Handler::imageset_nativehorzres_attribute( "NativeHorzRes" );
const std::string Imageset_Xml_Handler::imageset_nativevertres_attribute( "NativeVertRes" );
const std::string Imageset_Xml_Handler::image_name_attribute( "Name" );
const std::string Imageset_Xml_Handler::image_xpos_attribute( "XPos" );
const std::string Imageset_Xml_Handler::image_ypos_attribute( "YPos" );
const std::string Imageset_Xml_Handler::image_width_attribute( "Width" );
const std::string Imageset_Xml_Handler::image_height_attribute( "Height" );

////////////////////////////////////////////////////////////////////////////////////////////
Imageset_Xml_Handler::Imageset_Xml_Handler(const std::string& filename, const std::string& resource_group)
:imageset_(0),
object_read_(false),
resource_group_(resource_group)
{
    Root::singleton()->xml_parser()->parse_xml_file(*this, filename, resource_group);
}

Imageset_Xml_Handler::~Imageset_Xml_Handler()
{
}

void Imageset_Xml_Handler::element_start(const std::string& element, const Xml_Attributes& attributes)
{
    if (element == image_element_)
        element_image_start(attributes);

    else if (element == imageset_element_)
        element_imageset_start(attributes);
}

void Imageset_Xml_Handler::element_end(const std::string& element)
{
    if (element == imageset_element_)
        element_imageset_end();
}

void Imageset_Xml_Handler::element_imageset_start(const Xml_Attributes& attributes)
{
    const std::string name(attributes.get_value_as_string(imageset_name_attribute));
    const std::string filename(attributes.get_value_as_string(imageset_imagefile_attribute));
    const Size native( attributes.get_value_as_integer(imageset_nativehorzres_attribute), 
        attributes.get_value_as_integer(imageset_nativevertres_attribute));

    imageset_ = new Imageset(name, filename, resource_group_, native);
}

void Imageset_Xml_Handler::element_image_start(const Xml_Attributes& attributes)
{
    if (!imageset_)
        throw_xml_error("Attempt to access null object.");

    const std::string name(attributes.get_value_as_string(image_name_attribute));

    Rect rect;

    rect.left_ = static_cast<float>(attributes.get_value_as_integer(image_xpos_attribute));
    rect.top_ = static_cast<float>(attributes.get_value_as_integer(image_ypos_attribute));
    rect.right_ = rect.left_ + static_cast<float>(attributes.get_value_as_integer(image_width_attribute));
    rect.bottom_ = rect.top_ + static_cast<float>(attributes.get_value_as_integer(image_height_attribute));

    imageset_->define_image(name, rect);
}

void Imageset_Xml_Handler::element_imageset_end()
{
}

const std::string& Imageset_Xml_Handler::get_object_name() const
{
    return imageset_->get_name();
}

Imageset& Imageset_Xml_Handler::get_object() const
{
    return *imageset_;
}

////////////////////////////////////////////////////////////////////////////////////////////
}