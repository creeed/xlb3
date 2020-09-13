#include "XlbeException.h"
#include "XlbeIni.h"
#include "XlbeRoot.h"
#include "XlbeWindowEventUtilities.h"
#include "XlbeTinyXmlParser.h"
#include "XlbeDefualtResourceProvider.h"
#include "XlbeEncryptResourceProvider.h"
#include "XlbeRenderSystemD3d9.h"
#include "XlbeFmodSoundManager.h"
#include "XlbeFmodMusicManager.h"
#include "XlbeScene.h"
#include "XlbeTimeManager.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {	

/////////////////////////////////////////////////////////////////////////////////////////////////

template<> Root* Singleton<Root>::singleton_ = 0;
Root* Root::singleton()
{
    return singleton_;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
Root::Root(const std::string &config)
:queue_end_(false),
next_frame_(0),
fixed_delta_(0),
render_window_(0),
config_(config)
{
	time_manager_ = new Time_Manager;
	time_manager_->initialise();

    xml_parser_ = new Tiny_Xml_Parser;
	resource_load_ = new Resource_Load;
	default_resource_provider_ = new Default_Resource_Provider;
	encrypt_resource_provider_ = new Encrypt_Resource_Provider;
    resource_provider_ = default_resource_provider_;

    render_system_ = new Render_System_D3d9;

    sound_manager_  = new Fmod_Sound_Manager;
    music_manager_  = new Fmod_Music_Manager;
    font_manager_ = new Font_Manager;
	sprite_resource_manager_ = new Sprite_Resource_Manager;
    animation_resource_manager_ = new Animation_Resource_Manager;
    
	mouse_cursor_ = new Mouse_Cursor;
	widget_manager_ = new Widget_Manager;
    scene_manager_ = new Scene_Manager;
}

Root::~Root()
{
    cleanup(); 
}

void Root::save_config()
{
    Ini ini(config_);

	options_.sound_value_ = ini.write_float("Sound", "Value", sound_manager_->get_master_volume());
	options_.music_value_ = ini.write_float("Music", "Value", music_manager_->get_master_volume());

	ini.save_file(config_);
}

void Root::restore_config()
{
    Ini ini(config_);

	options_.nfs_ = ini.read_int("Root", "Fps", 40);
	options_.render_width_ = ini.read_int("Render", "Width", 1024);
	options_.render_height_ = ini.read_int("Render", "Height", 768);
	options_.render_geometry_width_ = ini.read_int("Render", "GeometryWidth", 1024);
	options_.render_geometry_height_ = ini.read_int("Render", "GeometryHeight", 768);
	options_.full_screen_ = ini.read_int("Render", "FullScreen", false);
	options_.deactivated_ = ini.read_bool("Render", "Deactivated", false);
	options_.hide_mouse_ = ini.read_bool("Render", "Hidemouse", false);
	options_.texture_filter_ = ini.read_bool("Render", "TextureFilter", false);
	options_.sound_enable_  = ini.read_bool("Sound", "Enable", false);
	options_.sound_value_ = ini.read_float("Sound", "Value", 1.0f);
	options_.music_enable_ = ini.read_bool("Music", "Enable", false);
	options_.music_value_ = ini.read_float("Music", "Value", 1.0f);

	std::string caption = ini.read_string("Render", "Caption", "0,0,1024,30");
	std::sscanf(caption.c_str(), "%f,%f,%f,%f", &options_.caption_.left_, &options_.caption_.top_, &options_.caption_.right_, &options_.caption_.bottom_);
}

Render_Window * Root::initialise(const std::string& title)
{
	frame_tick_.reset();
	frame_started_tick_.reset();
	frame_rendering_tick_.reset();
	frame_ended_tick_.reset();

	set_fps(options_.nfs_);

	render_system_->set_geometry_width(options_.render_geometry_width_);
	render_system_->set_geometry_height(options_.render_geometry_height_);
	render_system_->set_texture_filter(options_.texture_filter_);

    render_window_ = render_system_->initialise(title, options_.render_width_, options_.render_height_, options_.full_screen_);
	render_window_->set_hide_mouse(options_.hide_mouse_);
	render_window_->set_deactivated_on_focus_change(options_.deactivated_);
	render_window_->set_caption_rect(options_.caption_);

    mouse_cursor_->set_constraint_area(&render_system()->get_geometry_rect());

	sound_manager_->set_master_volume(options_.sound_value_);
	music_manager_->set_master_volume(options_.music_value_);

    return render_window_;
}

void Root::cleanup()
{
	SAFE_DELETE(mouse_cursor_);
    SAFE_DELETE(scene_manager_);
	SAFE_DELETE(font_manager_);
	SAFE_DELETE(sprite_resource_manager_);
    SAFE_DELETE(animation_resource_manager_);
	SAFE_DELETE(widget_manager_);

	SAFE_DELETE(render_system_);
    SAFE_DELETE(render_window_);
    SAFE_DELETE(sound_manager_);
    SAFE_DELETE(music_manager_);

    SAFE_DELETE(xml_parser_);
    SAFE_DELETE(default_resource_provider_);
	SAFE_DELETE(encrypt_resource_provider_);
	SAFE_DELETE(resource_load_);
}

void Root::add_frame_listener(Frame_Listener *listener)
{
    frame_listeners_.push_back(listener);
}

void Root::remove_frame_listener(Frame_Listener *listener)
{
    Frame_Listeners::iterator i = frame_listeners_.begin();
    for (; i!=frame_listeners_.end(); ++i)
    {
        if ((*i) == listener)
        {
            frame_listeners_.erase(i);
            return;
        }
    }
}

void Root::queue_end_rendering()
{
    queue_end_ = true;  
}

int Root::get_fps()  
{ 
    if (fixed_delta_ > 0)
    {
        return 1000.0 / fixed_delta_;
    }
    else return 0;  
}

void Root::set_fps(int nfs)
{
    if (nfs > 0)
    {
        fixed_delta_ = 1000.0/nfs;
    }
    else fixed_delta_ = 0; 
}

bool Root::get_encrypt_resource() const
{
	return (resource_provider_ == encrypt_resource_provider_);
}

void Root::set_encrypt_resource(bool encrypt_resource)
{
	if (encrypt_resource)
		resource_provider_ = encrypt_resource_provider_;
	else
		resource_provider_ = default_resource_provider_;

}

void Root::start_rendering()
{
    queue_end_ = false;

    while( !queue_end_ )
    {
		if (Window_Event_Utilities::message_pump())
		{
		}
		else
		{
			render_one_frame();

			if (render_window_->drag_caption() && render_window_->draging_caption())
			{
				POINT mouse_cur_pos;
				RECT window_cur_pos; 

				GetCursorPos(&mouse_cur_pos); 
				GetWindowRect((HWND)render_window_->window_handle(), &window_cur_pos);

				window_cur_pos.left = mouse_cur_pos.x - Window_Event_Utilities::drag_caption_delta_.x_ ;
				window_cur_pos.top = mouse_cur_pos.y - Window_Event_Utilities::drag_caption_delta_.y_ ;

				SetWindowPos((HWND)render_window_->window_handle(), HWND_NOTOPMOST, window_cur_pos.left, window_cur_pos.top, window_cur_pos.right, window_cur_pos.bottom, SWP_NOSIZE);
			}
		}

		Scene *scene = scene_manager_->get_run_scene();
		if (scene)
		{
			scene->process_input();
		}

		widget_manager_->process_input();
    }
}

void Root::render_one_frame()
{
    uint32_t daltetime = 0;
	daltetime = frame_tick_.get_milli_seconds(); 

	//static unsigned long oldtime = 0;
    //static unsigned long daltetime = 0;
	//do { daltetime = frame_tick_.get_milli_seconds() - oldtime; } while(daltetime < 1);

    if (daltetime >= fixed_delta_)
    {
        fire_frame_started();	
        fire_frame_rendering();
        fire_frame_ended();

		frame_tick_.reset();
    }
    else
    {
		Sleep(1);

        //if (fixed_delta_ && (daltetime + 3) < fixed_delta_) Sleep(0);
    }
}

void Root::fire_frame_started()
{
	uint32_t utime = Time_Manager::singleton()->current_time();
	uint32_t daltetime = frame_started_tick_.get_milli_seconds();
	frame_started_tick_.reset();

    Frame_Listeners::iterator i = frame_listeners_.begin();
    for (; i!=frame_listeners_.end(); ++i)
    {
        if(!(*i)->frame_started(utime / 1000.0f, daltetime / 1000.0f))
        {
            queue_end_rendering();
        }
    }
}

void Root::fire_frame_rendering()
{
	uint32_t utime = Time_Manager::singleton()->current_time();
	uint32_t daltetime = frame_rendering_tick_.get_milli_seconds();
	float dt = daltetime / 1000.0f;
	float ftime = utime / 1000.0f;
	frame_rendering_tick_.reset();

    if (render_window_->active())
    {
		Frame_Listeners::iterator iend = frame_listeners_.end();
		for (Frame_Listeners::iterator i = frame_listeners_.begin(); i != iend; ++i)
        {
            if(!(*i)->frame_rendering(ftime, dt))
            {
                queue_end_rendering();
            }
        }

        if (!render_system_->begin_scene())
		{
            return;
		}

		render_system_->clear(0x00000000);
		scene_manager_->draw_scene(utime, dt);

		widget_manager_->update(utime, dt);
		widget_manager_->draw();

		mouse_cursor_->draw();

        render_system_->end_scene();
    }
    else
        Sleep(1);
}

void Root::fire_frame_ended()
{
	uint32_t utime = Time_Manager::singleton()->current_time();
	uint32_t daltetime = frame_ended_tick_.get_milli_seconds();
    frame_ended_tick_.reset();

    Frame_Listeners::iterator i = frame_listeners_.begin();
    for (; i!=frame_listeners_.end(); ++i)
    {
        if(!(*i)->frame_ended(utime / 1000.0f, daltetime / 1000.0f))
        {
            queue_end_rendering();
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
}
