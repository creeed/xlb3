#ifndef __XLBE_RENDER_TEXTURE_H__
#define __XLBE_RENDER_TEXTURE_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

///////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeSize.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

///////////////////////////////////////////////////////////////////////////////////////////////////////
class  Render_Texture
{
public:
    virtual ~Render_Texture() {}

	virtual const Size& get_size() const = 0;
	virtual const Size& get_original_data_size() const = 0;

    virtual uint32_t *lock(bool readonly, int left=0, int top=0, int width=0, int height=0) = 0;
    virtual void unlock() = 0;

    virtual void ckeck_loaded() = 0;

	virtual void create(int width, int height) = 0;
	virtual void load_from_file(const std::string& filename) = 0;
    virtual void load_from_memory(const void* buffer, size_t buffer_size) = 0;
    virtual void save_to_memory(void* buffer) = 0;
	virtual void save_to_file(const std::string file) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif
