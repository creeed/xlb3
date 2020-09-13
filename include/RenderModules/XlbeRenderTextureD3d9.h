#ifndef __XLBE_RENDER_TEXTURE_D3D9_H__
#define __XLBE_RENDER_TEXTURE_D3D9_H__

/////////////////////////////////////////////////////////////////////////////////////////////
#include <d3d9.h>
#include <d3dx9.h>

#include "XlbePrereqs.h"
#include "XlbeSize.h"
#include "XlbeRawDataContainer.h"

/////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

class Render_System_D3d9;

/////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Render_Texture_D3d9 : public Render_Texture
{
public:
    Render_Texture_D3d9(Render_System_D3d9& owner, const std::string& name, int width, int height);
    Render_Texture_D3d9(Render_System_D3d9& owner, const std::string& filename);
    virtual ~Render_Texture_D3d9();

    virtual const Size& get_size() const;
    virtual const Size& get_original_data_size() const ;

    virtual uint32_t *lock(bool readonly, int left=0, int top=0, int width=0, int height=0);
    virtual void unlock();

    virtual void ckeck_loaded();

	virtual void create(int width, int height) ;
    virtual void load_from_file(const std::string& filenam) ;
    virtual void load_from_memory(const void* buffer, size_t buffer_size) ;
    virtual void save_to_memory(void* buffer) ;
	virtual void save_to_file(const std::string file);

    void set_direct_d3d9_texture(LPDIRECT3DTEXTURE9 tex);
    LPDIRECT3DTEXTURE9 get_direct_d3d9_texture() const;

    void cleanup_direct_d3d9_texture();

private:
    Render_System_D3d9& owner_;
    LPDIRECT3DTEXTURE9 texture_;

    bool is_loaded_;
    Raw_Data_Container data_container_;

    Size size_;
	std::string name_;
};

/////////////////////////////////////////////////////////////////
}
#endif