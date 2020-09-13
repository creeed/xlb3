#ifndef __XLBE_XML_SERIALIZER_H__
#define __XLBE_XML_SERIALIZER_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"

////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Xml_Serializer
{
public:
    Xml_Serializer(std::ostream& out, size_t indent_space = 4);
    virtual ~Xml_Serializer();  

    Xml_Serializer& open_tag(const std::string& name);
    Xml_Serializer& close_tag();

    Xml_Serializer& attribute(const std::string& name, const std::string& value);
    Xml_Serializer& text(const std::string& text);

    uint32_t get_tag_count() const { return tag_count_; }

    operator bool () const
    {
        return false == error_;
    }

    bool operator! () const
    {
        return false != error_;
    }

private:
    void indent_line();

    static std::string convert_entity_in_text(const std::string& text);
    static std::string convert_entity_in_attribute(const std::string& attribute_value);

    Xml_Serializer(const Xml_Serializer& obj);
    Xml_Serializer& operator=(const Xml_Serializer& obj);  

private:
    bool error_; 
    uint32_t tag_count_; 
    size_t depth_; 
    size_t indent_space_;
    bool need_close_; 
    bool last_is_text_;  
    std::ostream& stream_; 
    std::vector<std::string> tag_stack_; 
};

////////////////////////////////////////////////////////////////////////////////////////////
}

#endif