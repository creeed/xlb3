#include "XlbeException.h"
#include "XlbeXmlSerializer.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

///////////////////////////////////////////////////////////////////////////////////////////////////////
Xml_Serializer::Xml_Serializer(std::ostream& out, size_t indent_space)
: error_(false), depth_(0), indent_space_(indent_space), 
 need_close_(false), last_is_text_(false), stream_(out)
{
	stream_ << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
	error_ = ! stream_;
}


Xml_Serializer::~Xml_Serializer()
{
	if (!error_ || !tag_stack_.empty())
	{
		stream_ << std::endl;
	}
}

Xml_Serializer& Xml_Serializer::open_tag(const std::string& name)
{
	if (! error_)
	{
		++tag_count_;
		if (need_close_)
		{
			stream_ << '>';	  
		}
		if (!last_is_text_)
		{
			stream_ << std::endl;
			indent_line();
		}
		stream_ << '<' << name.c_str() << ' ';
		tag_stack_.push_back(name);
		++depth_;
		need_close_ = true;
		last_is_text_ = false;
		error_ = ! stream_;
	}

	return *this;
}

Xml_Serializer& Xml_Serializer::close_tag()
{
	std::string back =  tag_stack_.back();

	if (! error_)
	{
		--depth_;
		if (need_close_)
		{
			stream_ << "/>";
		}
		else if (! last_is_text_)
		{
			stream_ << std::endl;
			indent_line();
			stream_ << "</" << back.c_str() << '>';
		}
		else
		{
			stream_ << "</" << back.c_str() << '>';
		}
		last_is_text_ = false;
		need_close_ = false;
		tag_stack_.pop_back();
		error_ = ! stream_;
	}

	return *this;
}


Xml_Serializer& Xml_Serializer::attribute(const std::string& name, const std::string& value)
{
	if (!need_close_)
	{
		error_ = true;
	}
	if (!error_)
	{
		stream_ << name.c_str() << "=\""
			<< convert_entity_in_attribute(value).c_str()
			<< "\" ";
		last_is_text_ = false;
		error_ = ! stream_;
	}

	return *this;
}


Xml_Serializer& Xml_Serializer::text(const std::string& text)
{
	if (! error_)
	{
		if (need_close_)
		{
			stream_ << '>';
			need_close_ = false;
		}
		stream_ << convert_entity_in_text(text).c_str();
		last_is_text_ = true;
		error_ = ! stream_;
	}

	return *this;
}

void Xml_Serializer::indent_line()
{
	size_t space_count = depth_ * indent_space_;

	for (size_t i = 0 ; i < space_count ; ++i)
	{
		stream_ << ' ';
	}  
}

std::string Xml_Serializer::convert_entity_in_text(const std::string& text)
{
	std::string res;
	res.reserve(text.size()*2);
	const std::string::const_iterator iter_end = text.end();
	for (std::string::const_iterator iter = text.begin(); iter != iter_end ; ++iter)
	{
		switch(*iter)
		{  
		case '<':
			res += "&lt;";
			break;

		case '>':
			res += "&gt;";
			break;

		case '&':
			res +=  "&amp;";
			break;

		case '\'':
			res +=  "&apos;";
			break;

		case '"':
			res +=  "&quot;";
			break;

		default:
			res += *iter;
		}
	}

	return res;
}

std::string Xml_Serializer::convert_entity_in_attribute(const std::string& attribute_value)
{
	std::string res;
	res.reserve(attribute_value.size()*2);
	const std::string::const_iterator iter_end = attribute_value.end();
	for (std::string::const_iterator iter = attribute_value.begin(); iter != iter_end ; ++iter)
	{
		switch(*iter)
		{  
		case '<':
			res += "&lt;";
			break;

		case '>':
			res += "&gt;";
			break;

		case '&':
			res +=  "&amp;";
			break;

		case '\'':
			res +=  "&apos;";
			break;

		case '"':
			res +=  "&quot;";
			break;

		case '\n':
			res += "\\n";
			break;
		default:
			res += *iter;
		}
	}

	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
}