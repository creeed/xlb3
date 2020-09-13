#ifndef __XLBE_CONFIG_OPTION_H__
#define __XLBE_CONFIG_OPTION_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

///////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeRect.h"

///////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

///////////////////////////////////////////////////////////////////////////////////////////////
struct Xlbe_Export Config_Option
{
	int nfs_;
	int render_width_;
	int render_height_;
	int render_geometry_width_;
	int render_geometry_height_;
	bool full_screen_;
	bool deactivated_;
	bool hide_mouse_;
	bool texture_filter_;
	Rect caption_;
	float sound_value_;
	bool sound_enable_;
	float music_value_;
	bool music_enable_;

	Config_Option()
	{
		nfs_ = 40;
		render_width_ = 1024;
		render_height_ = 768;
		render_geometry_width_ = 1024;
		render_geometry_height_ = 768;
		full_screen_ = false;
		deactivated_ = false;
		hide_mouse_ = false;
		texture_filter_ = false;
		sound_value_ = 1.0f;
		sound_enable_= false;
		music_value_ = 1.0f;
		music_enable_= false;
	}

};

////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif 