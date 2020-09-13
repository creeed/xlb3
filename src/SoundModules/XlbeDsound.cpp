#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeDsound.h"
#include "XlbeDsoundManager.h"
#include "XlbeContainerFile.h"

#include "ogg/ivorbiscodec.h"
#include "ogg/ivorbisfile.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

#define SOUND_FLAGS (DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME |  DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE | DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLFREQUENCY)

//////////////////////////////////////////////////////////////////////////////////////////////////////
DSound::DSound(const std::string& name, const std::string& filename, const std::string& resource_group, DSound_Manager *mgr)
{
    name_ = name;
    size_ = 0;
    filename_ = filename;
    resource_group_ = resource_group;

    volume_ = 1.0;
    pan_ = 0;
    source_sound_ = 0;
    sound_manager_ = mgr;

    load_state_ = LOADSTATE_UNLOADED;
}

DSound::~DSound()
{
}

void DSound::prepare()
{
    /*load_state_ = LOADSTATE_PREPARED;*/
}

void DSound::unprepare()
{
    /*load_state_ = LOADSTATE_PREPARING;*/
}

void DSound::load()
{
    if (!is_loaded())
    {
       load_sound(filename_, resource_group_);

       load_state_ = LOADSTATE_LOADED;
    }
}

void DSound::unload()
{
    if (source_sound_)
    {
        source_sound_->Release();
        source_sound_ = 0;
    }

    load_state_ = LOADSTATE_UNLOADED;
}

void DSound::load_sound(const std::string& file, const std::string& resource_group)
{
    if (!load_ogg_sound(file, resource_group))
        throw_sound_error(file + " Load ogg sound failed.");
}

static int c_fseek64_wrap(Container_File *f,ogg_int64_t off,int whence)
{
	if(f==NULL) return(-1);
	return cfseek(f,(long)off,whence);
}

int ov_pak_open(Container_File *f,OggVorbis_File *vf,char *initial,long ibytes)
{
	  ov_callbacks callbacks = {
		         (size_t (*)(void *, size_t, size_t, void *))  cfread,
		         (int (*)(void *, ogg_int64_t, int))           c_fseek64_wrap,
		         (int (*)(void *))                             cfclose,
		         (long (*)(void *))                            cftell
	  };

	return ov_open_callbacks((void *)f, vf, initial, ibytes, callbacks);
}

bool DSound::load_ogg_sound(const std::string& file, const std::string& resource_group)
{
	Root* root = Root::singleton();

    if (!root)
        throw_scene_error("root object has not been created!");

	if (!sound_manager_->get_direct_sound())
	{
		return true;
	}

    Raw_Data_Container data_container;
    root->resource_provider()->load_raw_data_container(file, data_container, resource_group);

    OggVorbis_File vf;
    int current_section;

    Container_File *cf = cfopen(&data_container);

    if(ov_pak_open(cf, &vf, NULL, 0) < 0) 
    {
        cfclose(cf);
        return false;
    }

    vorbis_info *info = ov_info(&vf,-1);

    PCMWAVEFORMAT format;
    DSBUFFERDESC desc;    			

    memset(&format, 0, sizeof(PCMWAVEFORMAT));
    format.wf.wFormatTag = WAVE_FORMAT_PCM;
    format.wf.nChannels = info->channels;
    format.wf.nSamplesPerSec = info->rate;
    format.wBitsPerSample = 16;
    format.wf.nBlockAlign = format.wf.nChannels*format.wBitsPerSample/8;
    format.wf.nAvgBytesPerSec = format.wf.nSamplesPerSec * format.wf.nBlockAlign;	

    int len = (int) (ov_pcm_total(&vf,-1) * format.wf.nBlockAlign);	
    memset(&desc, 0, sizeof(DSBUFFERDESC)); 

    size_ = len;

    desc.dwSize = sizeof(DSBUFFERDESC);
    desc.dwFlags = SOUND_FLAGS;
    desc.dwBufferBytes = len;
    desc.lpwfxFormat =(LPWAVEFORMATEX)&format;	

    if (sound_manager_->get_direct_sound()->CreateSoundBuffer(&desc, &source_sound_, 0) != DS_OK)
    {
        ov_clear(&vf);
        return false;
    }

    char* buf;
    DWORD bytes;
    if (source_sound_->Lock(0, len, (LPVOID*)&buf, &bytes, NULL, NULL, 0) != DS_OK)
    {
        ov_clear(&vf);
        return false;
    }

    char *ptr = buf;
    int numbytes = bytes;
    while(numbytes > 0)
    {		
        long ret=ov_read(&vf,ptr,numbytes,&current_section);
        if (ret == 0)
            break;
        else if (ret < 0) 
            break;
        else 
        {
            ptr += ret;
            numbytes -= ret;
        }
    }

    source_sound_->Unlock(buf, bytes, NULL, 0);
    ov_clear(&vf);

    root->resource_provider()->unload_raw_data_container(data_container);

    return numbytes == 0; 
}

bool DSound::load_fmod_sound(const std::string& file, const std::string& resource_group)
{
    return false;
}

bool DSound::load_wav_sound(const std::string& file, const std::string& resource_group)
{
    return false;
}

bool DSound::load_av_sound(const std::string& file, const std::string& resource_group)
{
    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
}
