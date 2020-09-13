// xlbe - 2D硬件加速引擎
// 版权所有 (C) 2011-2012, 徐林炳
// 联系方式: 徐林炳 <creednew2000@163.com>

#ifndef __XLBE_FMOD_SOUND_RESOURCE_H__
#define __XLBE_FMOD_SOUND_RESOURCE_H__

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeSoundResource.h"

struct FMUSIC_MODULE;
struct FSOUND_SAMPLE;
struct FSOUND_STREAM;

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Fmod_Sound_Resource : public Sound_Resource
{
public:
	Fmod_Sound_Resource(const std::string& name);
    virtual ~Fmod_Sound_Resource();

public:
	virtual void prepare();
	virtual void unprepare();
	virtual void load();
	virtual void unload();

	FSOUND_SAMPLE *get_sample() { return sample_; }
	void set_sample(FSOUND_SAMPLE *sample) { sample_ = sample; }

	const std::string &get_sound_filename() const { return sound_filename_; }
	void set_sound_filename(const std::string &filename) { sound_filename_ = filename; }

private:
	std::string sound_filename_;
    FSOUND_SAMPLE *sample_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif