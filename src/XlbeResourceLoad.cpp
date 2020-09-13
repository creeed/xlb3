#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeResourceManager.h"
#include "XlbeFontManager.h"
#include "XlbeMusicManager.h"
#include "XlbeSoundManager.h"
#include "XlbeSpriteResourceManager.h"
#include "XlbeAnimationResourceManager.h"
#include "XlbeResourceLoad.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

template<> Resource_Load* Singleton<Resource_Load>::singleton_ = 0;
Resource_Load* Resource_Load::singleton()
{
   return singleton_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Resource_Load::Resource_Load()
{
}

Resource_Load::~Resource_Load()
{
}

void Resource_Load::load_script(const std::string &xml_file, std::vector<Resource*> *resources)
{
   char drive[_MAX_DRIVE];
   char dir[_MAX_DIR];
   char fname[_MAX_FNAME];
   char ext[_MAX_EXT];

	_splitpath( xml_file.c_str(), drive, dir, fname, ext);

	if (strcmp(ext, ".font") == 0)
	{
		Font_Manager::singleton()->load_script(xml_file, resources);
	}
	else if (strcmp(ext, ".sound") == 0)
	{
		Root::singleton()->sound_manager()->load_script(xml_file, resources);
		//Root::singleton()->music_manager()->load_script(xml_file, resources);
	}
	else if (strcmp(ext, ".sprite") == 0)
	{
		Sprite_Resource_Manager::singleton()->load_script(xml_file, resources);
		Animation_Resource_Manager::singleton()->load_script(xml_file, resources);
	}
	else if (strcmp(ext, ".music") == 0)
	{
		//Root::singleton()->sound_manager()->load_script(xml_file, resources);
		Root::singleton()->music_manager()->load_script(xml_file, resources);
	}
}

int Resource_Load::number_resource()
{
	return Font_Manager::singleton()->number_resource() + Sprite_Resource_Manager::singleton()->number_resource() +
		Animation_Resource_Manager::singleton()->number_resource() + Root::singleton()->sound_manager()->number_resource() + Root::singleton()->music_manager()->number_resource();
}

bool Resource_Load::is_all_loaded_resource()
{
	return false;
}

void Resource_Load::load_all_resource() 
{
	Sprite_Resource_Manager::singleton()->load_all_resource();
	Animation_Resource_Manager::singleton()->load_all_resource();
	Font_Manager::singleton()->load_all_resource();
	Root::singleton()->sound_manager()->load_all_resource();
	Root::singleton()->music_manager()->load_all_resource();

}

void Resource_Load::unload_all_resource() 
{
	Sprite_Resource_Manager::singleton()->unload_all_resource();
	Animation_Resource_Manager::singleton()->unload_all_resource();
	Font_Manager::singleton()->unload_all_resource();
	Root::singleton()->sound_manager()->unload_all_resource();
	Root::singleton()->music_manager()->unload_all_resource();
}

void Resource_Load::destroy_all_resource()
{
	Sprite_Resource_Manager::singleton()->destroy_all_resource();
	Animation_Resource_Manager::singleton()->destroy_all_resource();
	Font_Manager::singleton()->destroy_all_resource();
	Root::singleton()->sound_manager()->destroy_all_resource();
	Root::singleton()->music_manager()->destroy_all_resource();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
}