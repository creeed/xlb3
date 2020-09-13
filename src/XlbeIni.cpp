#include "XlbeException.h"
#include "XlbeIni.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

/////////////////////////////////////////////////////////////////////////////////////////
Ini::Ini(const std::string &file)
{
	file_ = file;
	parse_file(file);
}

Ini::~Ini()
{
}

std::string Ini::read_string(const std::string &section, const std::string &key, const std::string &value)
{
	std::string temp_key;
	std::string temp_value;
	std::string temp_section;
	
	for(int i = 0; i < lines_.size(); ++i)
	{
		std::string &section_line = lines_[i];
		int section_begin_pos = section_line.find('[');

		if(section_begin_pos == std::string::npos || section_begin_pos != 0)
		{
			continue;
		}

		int section_end_pos = section_line.find(']', section_begin_pos);
		if( section_end_pos == std::string::npos )
		{
			continue;
		}

		temp_section = section_line.substr(section_begin_pos + 1, section_end_pos - section_begin_pos - 1);
		temp_section.erase(0, temp_section.find_first_not_of(" "));  
        temp_section.erase(temp_section.find_last_not_of(" ") + 1); 

		if(section != temp_section)
		{
			continue;
		}

		for( ++i; i < lines_.size(); ++i )
		{
			std::string &key_line = lines_[i];
			int sec_pos = key_line.find('[');
			if( sec_pos != std::string::npos && sec_pos == 0 )
			{
				--i;  
				break;
			}

			int key_begin_pos = key_line.find(key);
			if( key_begin_pos == std::string::npos )
			{
				continue;
			}

			int equal_pos = key_line.find( '=', key_begin_pos );
			if( equal_pos == std::string::npos )
			{
				continue;
			}

			temp_key = key_line.substr(key_begin_pos, equal_pos - key_begin_pos);
			temp_key.erase(0, temp_key.find_first_not_of(" "));  
			temp_key.erase(temp_key.find_last_not_of(" ") + 1); 

			if(key != temp_key)
			{
				continue;
			}

			int comment_pos = key_line.find( "#", equal_pos + 1 );
			if( comment_pos != std::string::npos )
			{
				temp_value = key_line.substr(equal_pos + 1, comment_pos - equal_pos - 1);
				temp_value.erase(0, temp_value.find_first_not_of(" "));  
				temp_value.erase(temp_value.find_last_not_of(" ") + 1); 

				return temp_value;
			}

			temp_value = key_line.substr(equal_pos + 1);
			temp_value.erase(0, temp_value.find_first_not_of(" "));  
			temp_value.erase(temp_value.find_last_not_of(" ") + 1);

			return temp_value;
		}
	}

	return value;
}

int Ini::read_int(const std::string &section, const std::string &key, int value)
{
	std::string str = read_string( section, key, "" );
	if( "" == str )
	{
		return value;
	}

	std::istringstream in( str.c_str() );
	int ret = 0;
	in >> ret;
	return ret;
}

bool Ini::read_bool(const std::string &section, const std::string &key, bool value)
{
	std::string str = read_string( section, key, "" );
	if( "" == str )
	{
		return value;
	}

	std::istringstream in( str.c_str() );
	int ret = 0;
	in >> ret;
	return ret;
}

float Ini::read_float(const std::string &section, const std::string &key, float value)
{
	std::string str = read_string( section, key, "" );
	if( "" == str )
	{
		return value;
	}

	std::istringstream in( str.c_str() );
	float ret = 0;
	in >> ret;
	return ret;
}

bool Ini::write_string(const std::string &section, const std::string &key, const std::string &value)
{
	std::string temp_key;
	std::string temp_value;
	std::string temp_section;
	
	for(int i = 0; i < lines_.size(); ++i)
	{
		std::string &section_line = lines_[i];
		int section_begin_pos = section_line.find('[');

		if(section_begin_pos == std::string::npos || section_begin_pos != 0)
		{
			continue;
		}

		int section_end_pos = section_line.find(']', section_begin_pos);
		if( section_end_pos == std::string::npos )
		{
			continue;
		}

		temp_section = section_line.substr(section_begin_pos + 1, section_end_pos - section_begin_pos - 1);
		temp_section.erase(0, temp_section.find_first_not_of(" "));  
        temp_section.erase(temp_section.find_last_not_of(" ") + 1); 

		if(section != temp_section)
		{
			continue;
		}

		for( ++i; i < lines_.size(); ++i )
		{
			std::string &key_line = lines_[i];
			int sec_pos = key_line.find('[');
			if( sec_pos != std::string::npos && sec_pos == 0 )
			{
				--i;  
				break;
			}

			int key_begin_pos = key_line.find(key);
			if( key_begin_pos == std::string::npos )
			{
				continue;
			}

			int equal_pos = key_line.find( '=', key_begin_pos );
			if( equal_pos == std::string::npos )
			{
				continue;
			}

			temp_key = key_line.substr(key_begin_pos, equal_pos - key_begin_pos);
			temp_key.erase(0, temp_key.find_first_not_of(" "));  
			temp_key.erase(temp_key.find_last_not_of(" ") + 1); 

			if(key != temp_key)
			{
				continue;
			}

			int comment_pos = key_line.find( "#", equal_pos + 1 );
			temp_value = key_line.substr( 0, equal_pos + 1 ) + value;

			if( comment_pos != std::string::npos )
			{
				temp_value += key_line.substr( comment_pos );
			}

			key_line = temp_value;

			return true;
		}

		lines_.insert( lines_.begin() + i, key + "=" + value ); 

		return true;
	}

	lines_.insert( lines_.end(), "" );
	lines_.insert( lines_.end(), "[" + section + "]" );
	lines_.insert( lines_.end(), key + "=" + value );

	return true;
}

bool Ini::write_int(const std::string &section, const std::string &key, int value)
{
	std::ostringstream out;
	out << value;

	return write_string( section, key, out.str() );
}

bool Ini::write_bool(const std::string &section, const std::string &key, bool value)
{
	std::ostringstream out;
	out << (int)value;

	return write_string( section, key, out.str() );
}

bool Ini::write_float(const std::string &section, const std::string &key, float value)
{
	std::ostringstream out;
	out << value;

	return write_string( section, key, out.str() );
}

void Ini::delete_section(const std::string &section)
{
	std::string temp_key;
	std::string temp_value;
	std::string temp_section;
	
	for(int i = 0; i < lines_.size(); ++i)
	{
		std::string &section_line = lines_[i];
		int section_begin_pos = section_line.find('[');

		if(section_begin_pos == std::string::npos || section_begin_pos != 0)
		{
			continue;
		}

		int section_end_pos = section_line.find(']', section_begin_pos);
		if( section_end_pos == std::string::npos )
		{
			continue;
		}

		temp_section = section_line.substr(section_begin_pos + 1, section_end_pos - section_begin_pos - 1);
		temp_section.erase(0, temp_section.find_first_not_of(" "));  
        temp_section.erase(temp_section.find_last_not_of(" ") + 1); 

		if(section != temp_section)
		{
			continue;
		}

		int delete_begin = i;
		for( ++i ; i < lines_.size(); ++i )
		{
			std::string &next_section = lines_[i];
			int next_pos = next_section.find('[');
			if( next_pos == std::string::npos || next_pos != 0 )
			{
				continue;
			}

			break;
		}

		lines_.erase( lines_.begin() + delete_begin, lines_.begin() + i );

		return ;
	}
}

void Ini::delete_key(const std::string &section, const std::string &key)
{
    std::string temp_key;
	std::string temp_value;
	std::string temp_section;
	
	for(int i = 0; i < lines_.size(); ++i)
	{
		std::string &section_line = lines_[i];
		int section_begin_pos = section_line.find('[');

		if(section_begin_pos == std::string::npos || section_begin_pos != 0)
		{
			continue;
		}

		int section_end_pos = section_line.find(']', section_begin_pos);
		if( section_end_pos == std::string::npos )
		{
			continue;
		}

		temp_section = section_line.substr(section_begin_pos + 1, section_end_pos - section_begin_pos - 1);
		temp_section.erase(0, temp_section.find_first_not_of(" "));  
        temp_section.erase(temp_section.find_last_not_of(" ") + 1); 

		if(section != temp_section)
		{
			continue;
		}

		for( ++i ; i < lines_.size(); ++i )
		{
			std::string &key_line = lines_[i];
			int key_pos = key_line.find( key );
			if( key_pos == std::string::npos || key_pos != 0 )
			{
				continue;
			}
			else
			{
				lines_.erase( lines_.begin() + i );

				return ;
			}
		}

		return ;
	}
}

bool Ini::parse_file(const std::string &file)
{
	std::ifstream ifs(file.c_str());

	if (!ifs.is_open())
		return false;
	
	std::string line;
	while( std::getline(ifs, line) )
	{
		lines_.push_back(line);
	}

	return true;
}

void Ini::save_file(const std::string &file)
{
	std::ofstream out(file.c_str());

	for( int i = 0; i < lines_.size(); ++i )
	{
		out << lines_[i] << std::endl;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
}



