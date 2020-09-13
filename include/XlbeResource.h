#ifndef __XLBE_RESOURCE_H__
#define __XLBE_RESOURCE_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"

////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Resource
{
public:
    enum Loading_State
    {
		LOADSTATE_NULL,
        LOADSTATE_UNLOADED,
        LOADSTATE_LOADING,
        LOADSTATE_LOADED,
        LOADSTATE_UNLOADING,
        LOADSTATE_UNPREPARED,
        LOADSTATE_PREPARING,
		LOADSTATE_PREPARED,
		LOADSTATE_UNPREPARING,
    };

public:
	Resource() { load_state_ = LOADSTATE_NULL; }
    virtual ~Resource() {}

public:
	const std::string &get_resource_type() { return resource_type_; }

    const std::string& get_name() const { return name_; }
    void set_name(const std::string &name) { name_ = name; } 

    size_t get_size() const { return size_ ; }

	bool is_preparing() const { return (load_state_ == LOADSTATE_PREPARING); }
    bool is_prepared() const { return (load_state_ == LOADSTATE_PREPARED); }
    bool is_loading() const { return (load_state_ == LOADSTATE_LOADING); }
    bool is_loaded() const { return (load_state_ == LOADSTATE_LOADED); }

    Loading_State get_load_state() const { return load_state_; }

    virtual void prepare() = 0;
    virtual void unprepare() = 0;
    virtual void load() = 0;
    virtual void unload() = 0;

protected:
    std::string name_; 
    size_t size_;
    Loading_State load_state_;

	std::string resource_type_;
};

////////////////////////////////////////////////////////////////////////////////////////////////
} 

#endif	