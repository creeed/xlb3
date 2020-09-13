#ifndef __XLBE_CONTAINER_FILE_H__
#define __XLBE_CONTAINER_FILE_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeRawDataContainer.h"

////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Container_File
{
public:
	Container_File(Raw_Data_Container *container)
        :pos_(0), raw_data_container_(container)
	{
	}

	~Container_File() 
	{ 
	}

public:
    int pos_;
    Raw_Data_Container *raw_data_container_;
};

////////////////////////////////////////////////////////////////////////////////////////////////
static Container_File* cfopen(Raw_Data_Container *container) 
{
    Container_File* file = new Container_File(container);

    return file;
}

static int cfclose(Container_File* file)
{
    if (file == 0)
        return -1;

    delete file;
    return 0;
}

static int cfseek(Container_File* file, long offset, int origin) 
{
    if (file == 0)
        return -1;

    if (SEEK_CUR == origin)
    {
        file->pos_ += offset;
    }
    else if (SEEK_END == origin)
    {
        file->pos_ = file->raw_data_container_->get_size() - offset;
    }
    else
    {
        file->pos_ = offset;
    }

    file->pos_ = std::max(std::min(file->pos_, file->raw_data_container_->get_size()), 0);

    return 0;
}

static int cftell(Container_File* file) 
{
   if (file == 0)
        return -1;

    return file->pos_;
}

static size_t cfread(void* data, int elemsize, int count, Container_File* file)
{
    if (file == 0)
        return -1;

    int size_byte = std::min(elemsize*count, file->raw_data_container_->get_size() - file->pos_);
    std::memcpy(data, file->raw_data_container_->get_data_ptr() + file->pos_, size_byte);

    file->pos_ += size_byte;

    return size_byte/elemsize;
}

static size_t cfwrite(const void* data, int elemsize, int count, Container_File* file)
{	
    if (file == 0)
        return -1;

    int size_byte = std::min(elemsize*count, file->raw_data_container_->get_size() - file->pos_);
    std::memcpy(file->raw_data_container_->get_data_ptr() + file->pos_, data, size_byte);

    file->pos_ += size_byte;

    return size_byte/elemsize;
}

static int cfeof(Container_File* file) 
{
    if (file == 0)
        return -1;

    return (file->pos_ >= file->raw_data_container_->get_size());
}

////////////////////////////////////////////////////////////////////////////////////////////////
} 

#endif	