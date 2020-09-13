#ifndef __XLB_PACK_INTERFACE_H__
#define __XLB_PACK_INTERFACE_H__

//////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////
class Pack_Collection
{
public:
    HANDLE file_handle_;
    HANDLE mapping_handle_;
    void* data_;
};

class Pack_Record
{
public:
    Pack_Collection* collection_;
    std::string file_name_;
    FILETIME file_time_;
    int start_pos_;
    int size_;	
};

struct Pack_File
{
    Pack_Record* record_;
    int  pos_;
    FILE* file_;
};

typedef std::map<std::string, Pack_Record> Pack_Record_Map;
typedef std::list<Pack_Collection> Pack_Collection_List;

//////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Pack_Interface
{
public:
    Pack_Interface() {}
    virtual ~Pack_Interface() {}

public:
    virtual void insert_pack_file(const std::string &file) ;
	virtual void remove_pack_file(const std::string &file) ;

    virtual Pack_File* pfopen(const char* filename, const char* access) ;
    virtual int pfclose(Pack_File* file) ;

    virtual int	pfseek(Pack_File* file, long offset, int origin) ;
    virtual int pftell(Pack_File* file) = 0;

    virtual size_t pfread(void* data, int elemsize, int count, Pack_File* file) ;

    virtual int pfgetc(Pack_File* file) ;
    virtual int pungetc(int c, Pack_File* file) ;
    virtual char* pfgets(char* s, int size, Pack_File* file) ;

    virtual int pfeof(Pack_File* file) ;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif
