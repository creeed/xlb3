#ifndef __XLBE_SPRITE_H__
#define __XLBE_SPRITE_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"

#include "XlbeNode.h"
#include "XlbeRenderPrimitive.h"
#include "XlbeRenderSystem.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

class Sprite_Resource;

//////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Sprite : public Node
{
public:
	Sprite(const std::string& name);
	Sprite(const std::string& name, const std::string &str_res) ;
	Sprite(const std::string& name, Sprite_Resource *res) ;
    virtual ~Sprite();

public:
	Sprite_Resource *get_sprite_resource() { return sprite_res_; }
	void set_sprite_resource(const std::string &str_res);
	void set_sprite_resource(Sprite_Resource *res);

	Size get_texture_size();

public:
    virtual void enter();
    virtual void exit();

    virtual void update(float ftime, float dt);
    virtual void draw();
    
protected:
    Render_Quad quad_;

	Point texture_pos_;
	Size texture_size_;
	Render_Texture *texture_;

	std::string sprite_res_name_;
	Sprite_Resource *sprite_res_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif