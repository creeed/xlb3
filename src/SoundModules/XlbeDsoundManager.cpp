#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeDSound.h"
#include "XlbeDSoundXmlHandler.h"
#include "XlbeDSoundManager.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

///////////////////////////////////////////////////////////////////////////////////////////////////////
DSound_Manager::DSound_Manager()
{
    resource_type_ = "sound";
    file_pattern_ = "*.sound";

    Config_Option value;
    Config_Option enable;

    value.name = "Value";
    value.value = "1.0";

    enable.name = "Enable";
    enable.value = "true";

    options_[value.name] = value;
    options_[enable.name] = enable;
  
    volume_ = 1.0;
    pan_ = 0;
    last_release_tick_ = 0;
    initialised_ = false;

    for (int i = 0; i < MAX_CHANNELS; i++)
        playing_sounds_[i] = 0;

    dsound_dll_ = LoadLibrary("dsound.dll");
    typedef HRESULT (WINAPI *DirectSoundCreateFunc)(LPCGUID lpcGuid, LPDIRECTSOUND * ppDS, LPUNKNOWN  pUnkOuter);
    DirectSoundCreateFunc aDirectSoundCreateFunc = (DirectSoundCreateFunc)GetProcAddress(dsound_dll_,"DirectSoundCreate");

    if (aDirectSoundCreateFunc != NULL && aDirectSoundCreateFunc(NULL, &direct_sound_, NULL) == DS_OK)
    {
    }
	else
	{
		direct_sound_ = 0;
	}
}

DSound_Manager::~DSound_Manager()
{
}

void DSound_Manager::set_config_options(const std::string &name, const std::string &value)
{
    bool val = false;

    if (value == "false")
    {
        val = false;
    }
    else if (value == "true")
    {
        val = true;
    }

    Config_Option_Map::iterator i = options_.find(name);
    if (i != options_.end())
    {
        i->second.value = value;
    }
    else
    {
        throw_render_error("set_config_option -- name not exsit");
    }

    if (name == "Value")
    {
		float value;
        std::sscanf(options_[name].value.c_str(), "%f", &value);
       
        volume_ = value;
    }
}

Resource *DSound_Manager::create_resource_impl(const std::string &xml_file, const std::string &resource_group) 
{
    DSound_Xml_Handler handler(xml_file, resource_group, this);

    return &handler.get_object();
}

Sound_Instance*	DSound_Manager::sound_instance(const std::string &name) 
{
    if (!direct_sound_)
		return 0;

	if (!initialised_)
    {
        initialised_ = true;

        // should modify later.
        HWND hwnd = (HWND)Root::singleton()->render_window()->window_handle();
        direct_sound_->SetCooperativeLevel(hwnd, DSSCL_NORMAL);
    }

    DSound *sound = static_cast<DSound*>(get_resource(name));
       
    int channel = find_free_channel();

    if (channel >= MAX_CHANNELS)
		return 0;

	DSound_Instance* sound_instance = new DSound_Instance(this, sound);
	if (sound_instance->is_initialised())
        playing_sounds_[channel] = sound_instance;
	else
	{
		delete sound_instance;
		return 0;
	}

    return playing_sounds_[channel];
}

void DSound_Manager::release_channels()
{
    for (int i = 0; i < MAX_CHANNELS; i++)
    {
        if (playing_sounds_[i] != 0)
        {
            delete playing_sounds_[i];
            playing_sounds_[i] = 0;
        }
    }
}

double DSound_Manager::get_master_volume() 
{
    MIXERCONTROLDETAILS mcd;
    MIXERCONTROLDETAILS_UNSIGNED mxcd_u;
    MIXERLINECONTROLS mxlc;
    MIXERCONTROL mlct;
    MIXERLINE mixerLine;
    HMIXER hmx;
    MIXERCAPS pmxcaps;	

    mixerOpen((HMIXER*) &hmx, 0, 0, 0, MIXER_OBJECTF_MIXER);
    mixerGetDevCaps(0, &pmxcaps, sizeof(pmxcaps));

    mxlc.cbStruct = sizeof(mxlc);	
    mxlc.cbmxctrl = sizeof(mlct);
    mxlc.pamxctrl = &mlct;
    mxlc.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
    mixerLine.cbStruct = sizeof(mixerLine);
    mixerLine.dwComponentType = MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT;
    mixerGetLineInfo((HMIXEROBJ) hmx, &mixerLine, MIXER_GETLINEINFOF_COMPONENTTYPE);
    mxlc.dwLineID = mixerLine.dwLineID;
    mixerGetLineControls((HMIXEROBJ) hmx, &mxlc, MIXER_GETLINECONTROLSF_ONEBYTYPE);	

    mcd.cbStruct = sizeof(mcd);
    mcd.dwControlID = mlct.dwControlID;
    mcd.cChannels = 1;
    mcd.cMultipleItems = 0;
    mcd.cbDetails = sizeof(mxcd_u);
    mcd.paDetails = &mxcd_u;

    mixerGetControlDetails((HMIXEROBJ) hmx, &mcd, 0L);	

    mixerClose(hmx);

    return mxcd_u.dwValue / (double) 0xFFFF;
}

void DSound_Manager::set_master_volume(double volume) 
{
    MIXERCONTROLDETAILS mcd;
    MIXERCONTROLDETAILS_UNSIGNED mxcd_u;
    MIXERLINECONTROLS mxlc;
    MIXERCONTROL mlct;
    MIXERLINE mixerLine;
    HMIXER hmx;
    MIXERCAPS pmxcaps;	

    mixerOpen((HMIXER*) &hmx, 0, 0, 0, MIXER_OBJECTF_MIXER);
    mixerGetDevCaps(0, &pmxcaps, sizeof(pmxcaps));

    mxlc.cbStruct = sizeof(mxlc);	
    mxlc.cbmxctrl = sizeof(mlct);
    mxlc.pamxctrl = &mlct;
    mxlc.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
    mixerLine.cbStruct = sizeof(mixerLine);
    mixerLine.dwComponentType = MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT;
    mixerGetLineInfo((HMIXEROBJ) hmx, &mixerLine, MIXER_GETLINEINFOF_COMPONENTTYPE);
    mxlc.dwLineID = mixerLine.dwLineID;
    mixerGetLineControls((HMIXEROBJ) hmx, &mxlc, MIXER_GETLINECONTROLSF_ONEBYTYPE);	

    mcd.cbStruct = sizeof(mcd);
    mcd.dwControlID = mlct.dwControlID;
    mcd.cChannels = 1;
    mcd.cMultipleItems = 0;
    mcd.cbDetails = sizeof(mxcd_u);
    mcd.paDetails = &mxcd_u;

    mxcd_u.dwValue = (int) (0xFFFF * volume);
    mixerSetControlDetails((HMIXEROBJ) hmx, &mcd, 0L);

    mixerClose(hmx);
}

int DSound_Manager::volume_to_db(double volume)
{
    int vol = (int) ((std::log10(1 + volume*9) - 1.0) * 2333);
    if (vol < -2000)
        vol = -10000;

    return vol;
}

void DSound_Manager::set_volume(double volume) 
{ 
	volume_ = volume;

    for (int i = 0; i < MAX_CHANNELS; i++)
    {		
        if (playing_sounds_[i] != 0)
            playing_sounds_[i]->rehup_volume();
    }
}

int DSound_Manager::find_free_channel()
{
    DWORD tick = GetTickCount();
    if (tick - last_release_tick_ > 1000)
    {
        release_free_channels();
        last_release_tick_ = tick;
    }

    for (int i = 0; i < MAX_CHANNELS; i++)
    {		
        if (playing_sounds_[i] == 0)
            return i;

        if (playing_sounds_[i]->is_released())
        {
            delete playing_sounds_[i];
            playing_sounds_[i] = 0;

            return i;
        }
    }

    return MAX_CHANNELS;
}

void DSound_Manager::release_free_channels()
{
    for (int i = 0; i < MAX_CHANNELS; i++)
    {
        if (playing_sounds_[i] != 0 && playing_sounds_[i]->is_released())
        {
            delete playing_sounds_[i];
            playing_sounds_[i] = 0;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
}