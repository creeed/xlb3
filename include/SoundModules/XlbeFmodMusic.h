// xlbe - 2D硬件加速引擎
// 版权所有 (C) 2011-2012, 徐林炳
// 联系方式: 徐林炳 <creednew2000@163.com>

#ifndef __XLBE_FMOD_MUSIC_H__
#define __XLBE_FMOD_MUSIC_H__

////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeXmlHandler.h"
#include "XlbeMusic.h"

struct FMUSIC_MODULE;
struct FSOUND_SAMPLE;
struct FSOUND_STREAM;

////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

class Fmod_Music_Manager;

////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Fmod_Music : public Music
{
public:
	Fmod_Music(const std::string& name);
    virtual ~Fmod_Music();

public:
	virtual void prepare();
	virtual void unprepare();
	virtual void load();
	virtual void unload();

public:
	virtual bool play_music(int offset = 0, bool loop = false);	
	virtual void stop_music();
	virtual void pause_music();
	virtual void resume_music();
	
	virtual void fade_in(int offset = -1, double speed = 0.002, bool loop = false);
	virtual void fade_out(bool stop = true, double speed = 0.004);

	virtual float get_volume() const { return volume_; }
	virtual void set_volume(float volume);

	virtual float get_master_volume() const { return master_volume_; }	
    virtual void set_master_volume(float volume);

	virtual bool is_playing();

    void update();

	const std::string &get_music_filename() const { return music_filename_; }
	void set_music_filename(const std::string &filename) { music_filename_ = filename; }

private:
    FSOUND_STREAM *stream_;
	int channel_;
	float volume_;
	float master_volume_;
	float volume_add_;		
	float volume_cap_;		
	bool stop_on_fade_;
	bool repeats_;

	std::string music_filename_;
	Raw_Data_Container data_container_;
};

////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif 