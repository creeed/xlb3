#include "XlbeException.h"
#include "XlbeSpriteResource.h"
#include "XlbeRenderSystem.h"
#include "XlbeRoot.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////////////
Sprite_Resource::Sprite_Resource(const std::string& name)
{
	resource_type_ = "sprite";

    name_ = name;
    rotation_ = 0.0f;
    blend_ = BLEND_COLORMUL_ALPHABLEND;
	texture_ = 0;
	texture_size_.set_size(1.0f, 1.0f);
	
}

Sprite_Resource::~Sprite_Resource()
{
	//由用户来卸载资源， 回避引用计数
	//if ()
}

void Sprite_Resource::prepare()
{
	if (!is_prepared())
    {
       load_state_ = LOADSTATE_PREPARED;
    }
}

void Sprite_Resource::unprepare()
{
	load_state_ = LOADSTATE_UNPREPARED;
}

void Sprite_Resource::load()
{
    if (!is_loaded())
    {
		texture_ = Root::singleton()->render_system()->create_texture(texture_filename_);
        load_state_ = LOADSTATE_LOADED;
    }
}

void Sprite_Resource::unload()
{
    load_state_ = LOADSTATE_UNLOADED;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
}
