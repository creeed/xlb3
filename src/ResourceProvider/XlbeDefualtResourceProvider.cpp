#include "XlbeException.h"
#include "XlbeDefualtResourceProvider.h"

////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////////
void Default_Resource_Provider::load_raw_data_container(const std::string& filename, Raw_Data_Container& output) 
{
    if (filename.empty())
        throw_resource_error("File name supplied for data loading must be valid");

    FILE* file = fopen(filename.c_str(), "rb");

    if (file == 0)
        throw_resource_error(filename + " does not exist");

    fseek(file, 0, SEEK_END);
    const long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char* const buffer = new unsigned char[size];

    const size_t size_read = fread(buffer, sizeof(char), size, file);
    fclose(file);

    if (size_read != size)
    {
        delete[] buffer;
        throw_resource_error(filename + "A problem occurred while reading file");
    }

    output.set_data(buffer);
    output.set_size(size);
}

void Default_Resource_Provider::unload_raw_data_container(Raw_Data_Container &data)  
{ 
    uint8_t* const ptr = data.get_data_ptr();
    delete[] ptr;
    data.set_data(0);
    data.set_size(0);
}



////////////////////////////////////////////////////////////////////////////////////////////////
} 
