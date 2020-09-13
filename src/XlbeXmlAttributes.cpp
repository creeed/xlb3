#include "XlbeException.h"
#include "XlbeXmlAttributes.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

///////////////////////////////////////////////////////////////////////////////////////////////////////
Xml_Attributes::Xml_Attributes()
{
}

Xml_Attributes::~Xml_Attributes()
{
}

void Xml_Attributes::insert(const std::string& attr_name, const std::string& attr_value)
{
	Base::insert(std::pair<std::string, std::string>(attr_name, attr_value));
}

void Xml_Attributes::erase(const std::string& attr_name)
{
	iterator iter = find(attr_name);

	if (iter != end())
		Base::erase(iter);
}

bool Xml_Attributes::exists(const std::string& attr_name) const
{
	return find(attr_name) != end();
}

const std::string& Xml_Attributes::key(size_t index) const
{
	if (index >= size())
	{
		throw_xml_error("The specified index is out of range for this Xml_Attributes block.");
	}

	const_iterator iter = begin();
	std::advance(iter, index);

	return (*iter).first;
}

const std::string& Xml_Attributes::value(size_t index) const
{
	if (index >= size())
	{
		throw_xml_error("The specified index is out of range for this Xml_Attributes block.");
	}

	const_iterator iter = begin();
	std::advance(iter, index);

	return (*iter).second;
}

const std::string& Xml_Attributes::value(const std::string& attr_name) const
{
        const_iterator iter = find(attr_name);

        if (iter != end())
        {
            return (*iter).second;
        }
        else
        {
            throw_xml_error(attr_name + " no value exists for an attribute named.");
        }
}

const std::string& Xml_Attributes::get_value_as_string(const std::string& attr_name, const std::string& def) const
{
	 return (exists(attr_name)) ? value(attr_name) : def;
}

bool Xml_Attributes::get_value_as_bool(const std::string& attr_name, bool def) const
{
        if (!exists(attr_name))
        {
            return def;
        }

		const std::string& val = value(attr_name);

        if (val == "false" || val == "0")
        {
            return false;
        }
        else if (val == "true" || val == "1")
        {
            return true;
        }
        else
        {
            throw_xml_error("failed to convert attribute with value to bool.");
        }
}

int Xml_Attributes::get_value_as_integer(const std::string& attr_name, int def) const
{
	if (!exists(attr_name))
	{
		return def;
	}

	int val;
	std::istringstream strm(value(attr_name).c_str());

	strm >> val;

	if (strm.fail())
	{
		throw_xml_error("failed to convert attribute " + attr_name + " with value " + value(attr_name) + " to integer.");
	}

	return val;
}

float Xml_Attributes::get_value_as_float(const std::string& attr_name, float def) const
{
	if (!exists(attr_name))
	{
		return def;
	}

	float val;
	std::istringstream strm(value(attr_name).c_str());

	strm >> val;

	if (strm.fail())
	{
		throw_xml_error("failed to convert attribute " + attr_name + " with value " + value(attr_name) + " to float.");
	}

	return val;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
}
