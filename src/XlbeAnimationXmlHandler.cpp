#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeSpriteResource.h"
#include "XlbeAnimationResource.h"
#include "XlbeSpriteResourceManager.h"
#include "XlbeAnimationResourceManager.h"
#include "XlbeAnimationXmlHandler.h"

////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////
const std::string Animation_Xml_Handler::animation_element_( "Animation" );
const std::string Animation_Xml_Handler::animation_name_attribute( "Name" );
const std::string Animation_Xml_Handler::animation_duration_attribute( "Duration" );
const std::string Animation_Xml_Handler::keyframe_element_( "KeyFrame" );
const std::string Animation_Xml_Handler::keyframe_value_attribute( "Value" );
const std::string Animation_Xml_Handler::keyframe_time_attribute( "Time" );

////////////////////////////////////////////////////////////////////////////////////////////
Animation_Xml_Handler::Animation_Xml_Handler(const std::string& filename, std::vector<Resource*> *resources)
{
	resources_ = resources;
    Root::singleton()->xml_parser()->parse_xml_file(*this, filename);
}

Animation_Xml_Handler::~Animation_Xml_Handler()
{
}

void Animation_Xml_Handler::element_start(const std::string& element, const Xml_Attributes& attributes)
{
    if (element == animation_element_)
        element_animation_start(attributes);

    else if (element == keyframe_element_)
        element_keyframe_start(attributes);
}

void Animation_Xml_Handler::element_end(const std::string& element)
{
    if (element == animation_element_)
        element_animation_end();

    else if (element == keyframe_element_)
        element_keyframe_end();
}

void Animation_Xml_Handler::element_animation_start(const Xml_Attributes& attributes)
{
    const std::string name(attributes.get_value_as_string(animation_name_attribute));
	float duration(attributes.get_value_as_float(animation_duration_attribute));
	animation_ = (Animation_Resource *)Animation_Resource_Manager::singleton()->create_resource(name, 0); 
	animation_->set_duration(duration);
}

void Animation_Xml_Handler::element_keyframe_start(const Xml_Attributes& attributes)
{
    if (!animation_)
        throw_xml_error("Attempt to access null object.");

    const std::string value(attributes.get_value_as_string(keyframe_value_attribute));
    float time(attributes.get_value_as_float(keyframe_time_attribute));

	Sprite_Resource *spr_res  = (Sprite_Resource *)Sprite_Resource_Manager::singleton()->get_resource(value);
	if (spr_res)
        animation_->insert_keyframe(new Animation_Keyframe(spr_res, time));
}

void Animation_Xml_Handler::element_animation_end()
{
	if (animation_)
	{
		animation_->prepare();
		if (resources_)
		    resources_->push_back(animation_);
		animation_ = 0;
	}
}

void Animation_Xml_Handler::element_keyframe_end()
{
}

////////////////////////////////////////////////////////////////////////////////////////////
}