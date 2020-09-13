#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeWidgetManager.h"
#include "XlbeUIBuilder.h"
#include "XlbeWindow.h"
#include "XlbeButton.h"
#include "XlbeStatic.h"
#include "XlbeProgress.h"
#include "XlbeSlider.h"
#include "XlbeEdit.h"

////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////
const std::string UI_Builder::window_element_( "Window" );
const std::string UI_Builder::button_element_( "Button" );
const std::string UI_Builder::static_element_( "Static" );
const std::string UI_Builder::progress_element_( "Progress" );
const std::string UI_Builder::slider_element_( "Slider" );
const std::string UI_Builder::edit_element_( "Edit" );

const std::string UI_Builder::name_attribute_( "Name" );
const std::string UI_Builder::text_attribute_( "Text" );
const std::string UI_Builder::posx_attribute_( "XPos" );
const std::string UI_Builder::posy_attribute_( "YPos" );
const std::string UI_Builder::width_attribute_( "Width" );
const std::string UI_Builder::height_attribute_( "Height" );
const std::string UI_Builder::font_attribute_( "Font" );
const std::string UI_Builder::visible_attribute_( "Visible" );
const std::string UI_Builder::movable_attribute_( "Movable" );
const std::string UI_Builder::enabled_attribute_( "Enabled" );

////////////////////////////////////////////////////////////////////////////////////////////
UI_Builder::UI_Builder(const std::string &xml)
{
    Root::singleton()->xml_parser()->parse_xml_file(*this, xml);
}

UI_Builder::~UI_Builder()
{
}

void UI_Builder::element_start(const std::string& element, const Xml_Attributes& attributes)
{
    if (element == window_element_)
	{
        element_window_start(attributes);
	}

	else if (element == button_element_)
		element_button_start(attributes);

	else if (element == static_element_)
		element_static_start(attributes);

	else if (element == progress_element_)
		element_progress_start(attributes);

	else if (element == slider_element_)
		element_slider_start(attributes);

	else if (element == edit_element_)
		element_edit_start(attributes);
}

void UI_Builder::element_end(const std::string& element)
{
    if (element == window_element_)
        element_window_end();

	else if (element == button_element_)
		element_button_end();

	else if (element == static_element_)
		element_static_end();

	else if (element == progress_element_)
		element_progress_end();

	else if (element == slider_element_)
		element_slider_end();

	else if (element == edit_element_)
		element_edit_end();
}

void UI_Builder::element_window_start(const Xml_Attributes& attributes)
{
    int xpos(attributes.get_value_as_integer(posx_attribute_));
	int ypos(attributes.get_value_as_integer(posy_attribute_));
    int width(attributes.get_value_as_integer(width_attribute_));
	int height(attributes.get_value_as_integer(height_attribute_));
	bool visible(attributes.get_value_as_bool(visible_attribute_, true));
	bool movable(attributes.get_value_as_bool(movable_attribute_, false));
	bool enabled(attributes.get_value_as_bool(enabled_attribute_, true));

    const std::string name(attributes.get_value_as_string(name_attribute_));
	const std::string text(attributes.get_value_as_string(text_attribute_));
	const std::string font(attributes.get_value_as_string(font_attribute_));

	const std::string bk_image(attributes.get_value_as_string("BkImage"));

	Window *window = new Window(name);
    window->set_text(text);
	window->set_font(font);
	window->set_visible(visible);
	window->set_movable(movable);
	window->set_enabled(enabled);
	
	window->set_position(Point(xpos, ypos));
	window->set_size(Size(width, height));
	window->set_bk_image(bk_image);

	if (!widgets_.empty())
		widgets_.back()->insert_child(window);

	widgets_.push_back(window);

}

void UI_Builder::element_window_end()
{
	widgets_.pop_back();
}

void UI_Builder::element_button_start(const Xml_Attributes& attributes)
{
    int xpos(attributes.get_value_as_integer(posx_attribute_));
	int ypos(attributes.get_value_as_integer(posy_attribute_));
    int width(attributes.get_value_as_integer(width_attribute_));
	int height(attributes.get_value_as_integer(height_attribute_));
	bool visible(attributes.get_value_as_bool(visible_attribute_, true));
	bool movable(attributes.get_value_as_bool(movable_attribute_, false));
	bool enabled(attributes.get_value_as_bool(enabled_attribute_, true));

    const std::string name(attributes.get_value_as_string(name_attribute_));
	const std::string text(attributes.get_value_as_string(text_attribute_));
	const std::string font(attributes.get_value_as_string(font_attribute_));
	
	const std::string normal_image(attributes.get_value_as_string("NormalImage"));
	const std::string over_image(attributes.get_value_as_string("OverImage"));
	const std::string push_image(attributes.get_value_as_string("PushImage"));
	const std::string disabled_image(attributes.get_value_as_string("DisabledImage"));
	
	Button *button = new Button(name);
    button->set_text(text);
	button->set_font(font);
	button->set_visible(visible);
	button->set_movable(movable);
	button->set_enabled(enabled);
	button->set_position(Point(xpos, ypos));
	button->set_size(Size(width, height));
	button->set_normal_image(normal_image);
	button->set_over_image(over_image);
	button->set_push_image(push_image);
	button->set_disabled_image(disabled_image);

	if (!widgets_.empty())
	{
		widgets_.back()->insert_child(button);
	}

	widgets_.push_back(button);

}

void UI_Builder::element_button_end()
{
	widgets_.pop_back();
}

void UI_Builder::element_static_start(const Xml_Attributes& attributes)
{
    int xpos(attributes.get_value_as_integer(posx_attribute_));
	int ypos(attributes.get_value_as_integer(posy_attribute_));
    int width(attributes.get_value_as_integer(width_attribute_));
	int height(attributes.get_value_as_integer(height_attribute_));
	bool visible(attributes.get_value_as_bool(visible_attribute_, true));
	bool movable(attributes.get_value_as_bool(movable_attribute_, false));
	bool enabled(attributes.get_value_as_bool(enabled_attribute_, true));

    const std::string name(attributes.get_value_as_string(name_attribute_));
	const std::string text(attributes.get_value_as_string(text_attribute_));
	const std::string font(attributes.get_value_as_string(font_attribute_));
	
	int nlign = 0;
	int color = 0;
	const std::string align(attributes.get_value_as_string("Align"));
	const std::string text_color(attributes.get_value_as_string("Color", "#FFFFFFFF"));
	color = strtoul(text_color.substr(1).c_str(), 0, 16);
	
	char delims[] = "|";
	char *result = NULL;
	char sz_align[256];
	strcpy(sz_align, align.c_str());
	result = strtok( sz_align, delims );
	while( result != NULL )
	{
		if (strcmp(result, "LT_TOP") == 0)
		{
			nlign |= LT_TOP;
		}
		else if (strcmp(result, "LT_LEFT") == 0)
		{
			nlign |= LT_LEFT;
		}
		else if (strcmp(result, "LT_CENTER") == 0)
		{
			nlign |= LT_CENTER;
		}
		else if (strcmp(result, "LT_RIGHT") == 0)
		{
			nlign |= LT_RIGHT;
		}
		else if (strcmp(result, "LT_VCENTER") == 0)
		{
			nlign |= LT_VCENTER;
		}
		else if (strcmp(result, "LT_BOTTOM") == 0)
		{
			nlign |= LT_BOTTOM;
		}
		else if (strcmp(result, "LT_WORDBREAK") == 0)
		{
			nlign |= LT_WORDBREAK;
		}

		result = strtok( NULL, delims );
	}       
	
	Static *astatic = new Static(name);
    astatic->set_text(text);
	astatic->set_font(font);
	astatic->set_visible(visible);
	astatic->set_movable(movable);
	astatic->set_enabled(enabled);
	astatic->set_position(Point(xpos, ypos));
	astatic->set_size(Size(width, height));
	astatic->set_align(nlign);
	astatic->set_text_color(color);
	
	if (!widgets_.empty())
	{
		widgets_.back()->insert_child(astatic);
	}

	widgets_.push_back(astatic);

}

void UI_Builder::element_static_end()
{
	widgets_.pop_back();
}

void UI_Builder::element_progress_start(const Xml_Attributes& attributes)
{
    int xpos(attributes.get_value_as_integer(posx_attribute_));
	int ypos(attributes.get_value_as_integer(posy_attribute_));
    int width(attributes.get_value_as_integer(width_attribute_));
	int height(attributes.get_value_as_integer(height_attribute_));
	bool visible(attributes.get_value_as_bool(visible_attribute_, true));
	bool movable(attributes.get_value_as_bool(movable_attribute_, false));
	bool enabled(attributes.get_value_as_bool(enabled_attribute_, true));

    const std::string name(attributes.get_value_as_string(name_attribute_));
	const std::string text(attributes.get_value_as_string(text_attribute_));
	const std::string font(attributes.get_value_as_string(font_attribute_));

	float value(attributes.get_value_as_float("Value"));
	const std::string track_image(attributes.get_value_as_string("TrackImage"));
	const std::string step_image(attributes.get_value_as_string("StepImage"));
	
	Progress *progress = new Progress(name);
    progress->set_text(text);
	progress->set_font(font);
	progress->set_visible(visible);
	progress->set_movable(movable);
	progress->set_enabled(enabled);
	progress->set_position(Point(xpos, ypos));
	progress->set_size(Size(width, height));

	progress->set_value(value);
	progress->set_track_image(track_image);
	progress->set_step_image(step_image);
	
	if (!widgets_.empty())
	{
		widgets_.back()->insert_child(progress);
	}

	widgets_.push_back(progress);
}

void UI_Builder::element_progress_end()
{
	widgets_.pop_back();
}

void UI_Builder::element_slider_start(const Xml_Attributes& attributes)
{
    int xpos(attributes.get_value_as_integer(posx_attribute_));
	int ypos(attributes.get_value_as_integer(posy_attribute_));
    int width(attributes.get_value_as_integer(width_attribute_));
	int height(attributes.get_value_as_integer(height_attribute_));
	bool visible(attributes.get_value_as_bool(visible_attribute_, true));
	bool movable(attributes.get_value_as_bool(movable_attribute_, false));
	bool enabled(attributes.get_value_as_bool(enabled_attribute_, true));

    const std::string name(attributes.get_value_as_string(name_attribute_));
	const std::string text(attributes.get_value_as_string(text_attribute_));
	const std::string font(attributes.get_value_as_string(font_attribute_));

	float value(attributes.get_value_as_float("Value"));
	const std::string track_image(attributes.get_value_as_string("TrackImage"));
	const std::string thumb_image(attributes.get_value_as_string("ThumbImage"));
	
	Slider *slider = new Slider(name);
    slider->set_text(text);
	slider->set_font(font);
	slider->set_visible(visible);
	slider->set_movable(movable);
	slider->set_enabled(enabled);
	slider->set_position(Point(xpos, ypos));
	slider->set_size(Size(width, height));

	slider->set_value(value);
	slider->set_track_image(track_image);
	slider->set_thumb_image(thumb_image);
	
	if (!widgets_.empty())
	{
		widgets_.back()->insert_child(slider);
	}

	widgets_.push_back(slider);
}

void UI_Builder::element_slider_end()
{
	widgets_.pop_back();
}

void UI_Builder::element_edit_start(const Xml_Attributes& attributes)
{
    int xpos(attributes.get_value_as_integer(posx_attribute_));
	int ypos(attributes.get_value_as_integer(posy_attribute_));
    int width(attributes.get_value_as_integer(width_attribute_));
	int height(attributes.get_value_as_integer(height_attribute_));
	bool visible(attributes.get_value_as_bool(visible_attribute_, true));
	bool movable(attributes.get_value_as_bool(movable_attribute_, false));
	bool enabled(attributes.get_value_as_bool(enabled_attribute_, true));

    const std::string name(attributes.get_value_as_string(name_attribute_));
	const std::string text(attributes.get_value_as_string(text_attribute_));
	const std::string font(attributes.get_value_as_string(font_attribute_));

	int limit_text = attributes.get_value_as_integer("LimitText");

	int nformat = 0;
	const std::string format(attributes.get_value_as_string("Format"));

	const std::string text_color(attributes.get_value_as_string("Color", "#FFFFFFFF"));
	int color = strtoul(text_color.substr(1).c_str(), 0, 16);

	char delims[] = "|";
	char *result = NULL;
	char sz_align[256];
	strcpy(sz_align, format.c_str());
	result = strtok( sz_align, delims );
	while( result != NULL )
	{
		if (strcmp(result, "ES_IME_AVAILABLE") == 0)
		{
			nformat |= ES_IME_AVAILABLE;
		}
		else if (strcmp(result, "ES_MASK_CHARACTER") == 0)
		{
			nformat |= ES_MASK_CHARACTER;
		}
		else if (strcmp(result, "ES_SINGLELINE") == 0)
		{
			nformat |= ES_SINGLELINE;
		}

		result = strtok( NULL, delims );
	}       
	

	Edit *edit = new Edit(name);
	edit->set_font(font);
	edit->set_visible(visible);
	edit->set_movable(movable);
	edit->set_enabled(enabled);
	edit->set_position(Point(xpos, ypos));
	edit->set_size(Size(width, height));

	edit->set_limit_text(limit_text);
	edit->set_format(nformat);
	edit->set_text(text);
	edit->set_text_color(color);
	

	if (!widgets_.empty())
	{
		widgets_.back()->insert_child(edit);
	}

	widgets_.push_back(edit);
}

void UI_Builder::element_edit_end()
{
	widgets_.pop_back();
}

////////////////////////////////////////////////////////////////////////////////////////////
}