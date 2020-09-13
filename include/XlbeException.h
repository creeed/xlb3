#ifndef __XLBE_EXCEPTION_H__
#define __XLBE_EXCEPTION_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

//////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////
class base_error : public std::exception 
{
public:
    inline base_error(const std::string& msg, int line, const char *file):msg_(msg), line_(line), file_(file){} 
    virtual ~base_error() throw() {} 

	virtual int line() const throw() { return line_; } 
    virtual const char* file() const throw() { return file_; }  

    virtual const char* what() const throw()    { return msg_.c_str(); } 
    void set(const std::string& msg)            { msg_ = msg; }

private: 
    std::string msg_;
	const int line_;
	const char* file_;
};

class render_error : public base_error
{
public:  
    render_error(const std::string& msg, int line, const char *file) : base_error(msg, line, file) {}
};

class scene_error : public base_error
{
public:  
    scene_error(const std::string& msg, int line, const char *file) : base_error(msg, line, file) {}
};

class root_error : public base_error
{
public:  
    root_error(const std::string& msg, int line, const char *file) : base_error(msg, line, file) {}
};

class resource_error : public base_error
{
public:
    resource_error(const std::string& msg, int line, const char *file) : base_error(msg, line, file) {}
};

class sound_error : public base_error
{
public:
    sound_error(const std::string& msg, int line, const char *file) : base_error(msg, line, file) {}
};

class font_error : public base_error
{
public:
    font_error(const std::string& msg, int line, const char *file) : base_error(msg, line, file) {}
};

class xml_error : public base_error
{
public:
    xml_error(const std::string& msg, int line, const char *file) : base_error(msg, line, file) {}
};

class ui_error : public base_error
{
public:
    ui_error(const std::string& msg, int line, const char *file) : base_error(msg, line, file) {}
};

class widget_manager_error : public base_error
{
public:
    widget_manager_error(const std::string& msg, int line, const char *file) : base_error(msg, line, file) {}
};

#define throw_render_error(str) throw( xlbe::render_error(str, __LINE__, __FILE__) )
#define throw_scene_error(str) throw( xlbe::scene_error(str, __LINE__, __FILE__) )
#define throw_root_error(str) throw( xlbe::root_error(str, __LINE__, __FILE__) )
#define throw_resource_error(str) throw( xlbe::resource_error(str, __LINE__, __FILE__) )
#define throw_sound_error(str) throw( xlbe::sound_error(str, __LINE__, __FILE__) )
#define throw_font_error(str) throw( xlbe::font_error(str, __LINE__, __FILE__) )
#define throw_xml_error(str) throw( xlbe::xml_error(str, __LINE__, __FILE__) )
#define throw_ui_error(str) throw( xlbe::ui_error(str, __LINE__, __FILE__) )
#define throw_widget_manager_error(str) throw( xlbe::widget_manager_error(str, __LINE__, __FILE__) )

//////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif