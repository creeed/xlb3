#ifndef __XLBE_UI_BUILDER_H__
#define __XLBE_UI_BUILDER_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeXmlHandler.h"
#include "XlbeWidget.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

class Image;

//////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export UI_Builder : public Xml_Handler
{
public:
	typedef std::vector<Widget *> Widgets;

public:
    UI_Builder(const std::string &xml) ;
    virtual ~UI_Builder() ;

public:
	virtual void element_start(const std::string& element, const Xml_Attributes& attributes);
	virtual void element_end(const std::string& element);

private:
	void element_window_start(const Xml_Attributes& attributes);
    void element_window_end();

	void element_button_start(const Xml_Attributes& attributes);
    void element_button_end();

	void element_static_start(const Xml_Attributes& attributes);
    void element_static_end();

	void element_progress_start(const Xml_Attributes& attributes);
    void element_progress_end();

	void element_slider_start(const Xml_Attributes& attributes);
    void element_slider_end();

	void element_edit_start(const Xml_Attributes& attributes);
    void element_edit_end();

private:
	Widgets widgets_;

	static const std::string window_element_;
	static const std::string button_element_;
    static const std::string static_element_;
	static const std::string progress_element_;
	static const std::string slider_element_;
	static const std::string edit_element_;

	static const std::string name_attribute_;
	static const std::string text_attribute_;
	static const std::string posx_attribute_;
	static const std::string posy_attribute_;
	static const std::string width_attribute_;
	static const std::string height_attribute_;
	static const std::string font_attribute_;
	static const std::string visible_attribute_;
	static const std::string movable_attribute_;
	static const std::string enabled_attribute_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif