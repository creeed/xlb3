#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeAnimation.h"
#include "XlbeFigure.h"
#include "XlbeFigureManager.h"
#include "XlbeFigureXmlHandler.h"

////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////
const std::string Figure_Xml_Handler::figure_element_( "Figure" );
const std::string Figure_Xml_Handler::plate_element_( "Plate" );
const std::string Figure_Xml_Handler::animation_element_( "Animation" );
const std::string Figure_Xml_Handler::keyframe_element_( "KeyFrame" );
const std::string Figure_Xml_Handler::figure_name_attribute( "Name" );
const std::string Figure_Xml_Handler::figure_width_attribute( "Width" );
const std::string Figure_Xml_Handler::figure_height_attribute( "Height" );
const std::string Figure_Xml_Handler::plate_name_attribute( "Name" );
const std::string Figure_Xml_Handler::plate_value_attribute( "Value" );
const std::string Figure_Xml_Handler::animation_name_attribute( "Name" );
const std::string Figure_Xml_Handler::animation_duration_attribute( "Duration" );
const std::string Figure_Xml_Handler::animation_count_attribute( "Count" );
const std::string Figure_Xml_Handler::keyframe_value_attribute( "Value" );
const std::string Figure_Xml_Handler::keyframe_time_attribute( "Time" );

////////////////////////////////////////////////////////////////////////////////////////////
Figure_Xml_Handler::Figure_Xml_Handler(const std::string& filename, const std::string& resource_group)
:figure_(0),
animation_(0),
resource_group_(resource_group)
{
    Root::singleton()->xml_parser()->parse_xml_file(*this, filename, resource_group);
}

Figure_Xml_Handler::~Figure_Xml_Handler()
{
}

void Figure_Xml_Handler::element_start(const std::string& element, const Xml_Attributes& attributes)
{
    if (element == figure_element_)
        element_figure_start(attributes);

    else if (element == plate_element_)
        element_plate_start(attributes);

    else if (element == animation_element_)
        element_animation_start(attributes);

    else if (element == keyframe_element_)
        element_keyframe_start(attributes);
}

void Figure_Xml_Handler::element_end(const std::string& element)
{
    if (element == figure_element_)
        element_figure_end();

    else if (element == plate_element_)
        element_plate_end();

    else if (element == animation_element_)
        element_animation_end();

    else if (element == keyframe_element_)
        element_keyframe_end();
}

void Figure_Xml_Handler::element_figure_start(const Xml_Attributes& attributes)
{
    const std::string name(attributes.get_value_as_string(figure_name_attribute));
    const int width = attributes.get_value_as_integer(figure_width_attribute);
    const int height = attributes.get_value_as_integer(figure_height_attribute);

    figure_ = new Figure(name, width, height);
}

void Figure_Xml_Handler::element_plate_start(const Xml_Attributes& attributes)
{
    if (!figure_)
        throw_xml_error("Attempt to access null object.");

    const std::string name(attributes.get_value_as_string(plate_name_attribute));
    const std::string value(attributes.get_value_as_string(plate_value_attribute));

    figure_->define_plate(name, value);
}

void Figure_Xml_Handler::element_animation_start(const Xml_Attributes& attributes)
{
    if (!figure_)
        throw_xml_error("Attempt to access null object.");

    const std::string name(attributes.get_value_as_string(animation_name_attribute));
    float duration(attributes.get_value_as_float(animation_duration_attribute));
    int count(attributes.get_value_as_integer(animation_count_attribute));

    animation_ = figure_->create_animation(name, duration, count);
}

void Figure_Xml_Handler::element_keyframe_start(const Xml_Attributes& attributes)
{
    if (!animation_)
        throw_xml_error("Attempt to access null object.");

    const std::string value(attributes.get_value_as_string(keyframe_value_attribute));
    float time(attributes.get_value_as_float(keyframe_time_attribute));

	Image *image  = figure_->get_plate(value);
	if (image)
        animation_->insert_keyframe(new Animation_Keyframe(image, time));
}

void Figure_Xml_Handler::element_figure_end()
{
}

void Figure_Xml_Handler::element_plate_end()
{
}

void Figure_Xml_Handler::element_animation_end()
{
     animation_ = 0;
}

void Figure_Xml_Handler::element_keyframe_end()
{
}

const std::string& Figure_Xml_Handler::get_object_name() const
{
    return figure_->get_name();
}

Figure& Figure_Xml_Handler::get_object() const
{
    return *figure_;
}

////////////////////////////////////////////////////////////////////////////////////////////
}