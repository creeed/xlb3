// xlbe - 2D硬件加速引擎
// 版权所有 (C) 2011-2012, 徐林炳
// 联系方式: 徐林炳 <creednew2000@163.com>

#ifndef __XLBE_FMOD_MUSIC_MANAGER_H__
#define __XLBE_FMOD_MUSIC_MANAGER_H__

////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeXmlHandler.h"
#include "XlbeMusicManager.h"

////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

class Fmod_Music;

////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Fmod_Music_Manager : public Music_Manager
{
public:
	Fmod_Music_Manager();
	virtual ~Fmod_Music_Manager();

public:
	virtual bool load_script(const std::string &xml_file, std::vector<Resource*> *resources);
	virtual Resource *create_resource(const std::string &name, int type);

	virtual void stop_all_music();		

	float get_master_volume() const;	
    void set_master_volume(float volume);

	void update();

private:
    float master_volume_;
};

////////////////////////////////////////////////////////////////////////////////////////////////

}
#endif