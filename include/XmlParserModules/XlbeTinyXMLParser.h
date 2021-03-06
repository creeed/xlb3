#ifndef __XLBE_TINY_XML_PARSER_H__
#define __XLBE_TINY_XML_PARSER_H__

///////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbeXmlParser.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

///////////////////////////////////////////////////////////////////////////////////////////////////
class Tiny_Xml_Parser : public Xml_Parser
{
public:
    Tiny_Xml_Parser();
    virtual ~Tiny_Xml_Parser();

    virtual void parse_xml_file(Xml_Handler& handler, const std::string& filename) ;

protected:
    virtual bool initialise_impl() ;
    virtual void cleanup_impl();
};

///////////////////////////////////////////////////////////////////////////////////////////////////
} 

#endif  