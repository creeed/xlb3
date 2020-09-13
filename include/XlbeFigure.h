#ifndef __XLBE_FIGURE_H__
#define __XLBE_FIGURE_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeResource.h"
#include "XlbeSize.h"
#include "XlbeAnimation.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Figure : public Resource
{
public:
    typedef std::map<std::string, Image*, xlbe_utility::fast_less_compare> Plates;
    typedef std::map< std::string, Animation*, xlbe_utility::fast_less_compare> Animations;

public:
    Figure(const std::string& name, float width, float height);
    virtual ~Figure();

public:
	virtual void prepare();
	virtual void unprepare();
	virtual void load();
	virtual void unload();

public:
    Size get_figure_size() const { return Size(width_, height_); }

    int get_plate_count() const ;
	bool is_plate_defined(const std::string& name) const ;
	Image *get_plate(const std::string &name) ;
	void define_plate(const std::string& name, const std::string& value);
	void undefine_plate(const std::string& name);
	void undefine_all_plates();

    int get_animation_count() const ;
	bool has_animation(const std::string& name) const ;
	Animation *get_animation(const std::string &name) ;
	Animation *create_animation(const std::string& name, float duration, int count);
	void destroy_animation(const std::string& name);
	void destroy_all_animations();

private:
    float width_;
    float height_;
    Plates plates_;
    Animations animations_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif