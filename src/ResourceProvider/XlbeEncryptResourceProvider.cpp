#include "XlbeException.h"
#include "XlbeEncryptResourceProvider.h"

////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

#define PAKCET_KEY "gfdg9i9gflewirer"

#define ENCRYPT(x,xlen,KEY,BeginPlace)	if( (x)!=NULL ) \
		{ \
		\
			CHAR* t_pBuffer = (x); \
			CHAR* pKey = {KEY}; \
			UINT KeyLen = (UINT)strlen(pKey); \
			for (UINT i = 0; i < (xlen); i++) \
			{ \
				*t_pBuffer ^= pKey[(i+BeginPlace)%KeyLen]; \
				t_pBuffer++; \
			} \
		}



////////////////////////////////////////////////////////////////////////////////////////////////
void Encrypt_Resource_Provider::load_raw_data_container(const std::string& filename, Raw_Data_Container& output) 
{
    if (filename.empty())
        throw_resource_error("File name supplied for data loading must be valid");

    FILE* file = fopen(filename.c_str(), "rb");

    if (file == 0)
        throw_resource_error(filename + " does not exist");

    fseek(file, 0, SEEK_END);
    const long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = new  char[size];

    const size_t size_read = fread(buffer, sizeof(char), size, file);
    fclose(file);

    if (size_read != size)
    {
        delete[] buffer;
        throw_resource_error(filename + "A problem occurred while reading file");
    }

	char ext[_MAX_EXT];  
    _splitpath( filename.c_str(), 0, 0, 0, ext ); 
	if (strcmp(ext, ".sprite") == 0 || strcmp(ext, ".png") == 0)
	    ENCRYPT(buffer, size_read, PAKCET_KEY, 0);

    output.set_data((uint8_t*)buffer);
    output.set_size(size);
}

void Encrypt_Resource_Provider::unload_raw_data_container(Raw_Data_Container &data)  
{ 
    uint8_t* const ptr = data.get_data_ptr();
    delete[] ptr;
    data.set_data(0);
    data.set_size(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////
} 
