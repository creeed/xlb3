#include "XlbeException.h"
#include "XlbeXmlParser.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

///////////////////////////////////////////////////////////////////////////////////////////////////////	

Xml_Parser::Xml_Parser()
:identifier_("Unknown Xml parser (vendor did not set the ID string!)"),
initialised_(false)
{
}

Xml_Parser::~Xml_Parser()
{
}

bool Xml_Parser::initialise()
{
	if (!initialised_)
	{
		initialised_ = initialise_impl();
	}

	return initialised_;
}

void Xml_Parser::cleanup()
{
	if (initialised_)
	{
		cleanup_impl();
		initialised_ = false;
	}
}

const std::string& Xml_Parser::get_identifier() const
{
	return identifier_;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
}
