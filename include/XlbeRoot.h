#ifndef __XLBE_ROOT_H__
#define __XLBE_ROOT_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeSingleton.h"
#include "XlbeTick.h"
#include "XlbeFrameListener.h"
#include "XlbeXmlParser.h"
#include "XlbeResourceProvider.h"
#include "XlbeRenderWindow.h"
#include "XlbeRenderSystem.h"
#include "XlbeFontManager.h"
#include "XlbeSoundManager.h"
#include "XlbeMusicManager.h"
#include "XlbeResourceLoad.h"
#include "XlbeSceneManager.h"
#include "XlbeMouseCursor.h"
#include "XlbeSpriteResourceManager.h"
#include "XlbeAnimationResourceManager.h"
#include "XlbeWidgetManager.h"
#include "XlbeTimeManager.h"


////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Root : public Singleton<Root>
{
public:
    typedef std::stack<Scene*> Scenes;
    typedef std::vector<Frame_Listener *> Frame_Listeners;

public:
    Root(const std::string &config);
    ~Root();

    static Root* singleton();

public:
    Render_Window *initialise(const std::string& title);
    void cleanup();

    Config_Option* config_options() { return &options_; }
	void set_config_options(Config_Option *options) { options_ = *options; }

    void save_config();
    void restore_config();

    void start_rendering();
    void render_one_frame();

    int get_fps();
    void set_fps(int nfs);

	bool get_encrypt_resource() const;
	void set_encrypt_resource(bool encrypt_resource);

    void queue_end_rendering();
    
    void add_frame_listener(Frame_Listener *listener);
    void remove_frame_listener(Frame_Listener *listener);

public:
	Render_Window *render_window() { return render_window_; }
    Render_System *render_system() { return render_system_; }
    Sound_Manager *sound_manager() { return sound_manager_; }
    Music_Manager *music_manager() { return music_manager_; }
	Xml_Parser *xml_parser() { return xml_parser_;}
	Resource_Provider *resource_provider() { return resource_provider_; }

private:
    void fire_frame_started();
    void fire_frame_rendering();
    void fire_frame_ended();

private:
	Tick frame_tick_;
	Tick frame_started_tick_;
	Tick frame_rendering_tick_;
	Tick frame_ended_tick_;

    bool queue_end_;
    uint32_t next_frame_;
    uint32_t fixed_delta_;

	std::string config_;
    Config_Option options_;
    
    Render_Window *render_window_;
    Render_System *render_system_;
    
	Resource_Load *resource_load_;

	Sprite_Resource_Manager *sprite_resource_manager_;
	Animation_Resource_Manager *animation_resource_manager_;
	Font_Manager *font_manager_;

    Sound_Manager *sound_manager_;
    Music_Manager *music_manager_;
    
	Mouse_Cursor *mouse_cursor_;
	Scene_Manager *scene_manager_;
	Widget_Manager *widget_manager_;

	Xml_Parser *xml_parser_;
	Resource_Provider *resource_provider_;
	Resource_Provider *default_resource_provider_;
	Resource_Provider *encrypt_resource_provider_;

	Time_Manager *time_manager_;

	Frame_Listeners frame_listeners_;
};


////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif 