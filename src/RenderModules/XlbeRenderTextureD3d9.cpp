#include "XlbeException.h"
#include "XlbeRoot.h"
#include "XlbeRawDataContainer.h"
#include "XlbeRenderTextureD3d9.h"
#include "XlbeRenderSystemD3d9.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////////////////
Render_Texture_D3d9::Render_Texture_D3d9(Render_System_D3d9& owner, const std::string& name, int width, int height)
:owner_(owner),
name_(name),
texture_(0),
size_(width, height),
is_loaded_(false)
{
}

Render_Texture_D3d9::Render_Texture_D3d9(Render_System_D3d9& owner, const std::string& filename)
:owner_(owner),
name_(filename),
texture_(0),
size_(0, 0),
is_loaded_(false)
{
    load_from_file(filename);
}

Render_Texture_D3d9::~Render_Texture_D3d9()
{
    if (data_container_.get_data_ptr())
    {
        Root::singleton()->resource_provider()->unload_raw_data_container(data_container_);
    }

    cleanup_direct_d3d9_texture();
}

const Size& Render_Texture_D3d9::get_size() const
{
    return size_;
}

const Size& Render_Texture_D3d9::get_original_data_size() const 
{
	return size_;
}

void Render_Texture_D3d9::ckeck_loaded()
{
    if (!is_loaded_ )
    {
		if (data_container_.get_data_ptr() != 0)
		{
            load_from_memory(data_container_.get_data_ptr(), data_container_.get_size());
            Root::singleton()->resource_provider()->unload_raw_data_container(data_container_);
		}
		else
		{
			create(size_.width_, size_.height_);
		}

        is_loaded_ = true;
    }
}

void Render_Texture_D3d9::create(int width, int height) 
{
	D3DSURFACE_DESC desc;
	IDirect3DDevice9 *device = (IDirect3DDevice9 *)owner_.get_device();

	HRESULT hr = D3DXCreateTexture(device, width, height,1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &texture_);

	if (FAILED(hr))
	{
		throw_render_error("Render_Texture_D3d9::create - D3DXCreateTexture Failed  ");
	}

	if(FAILED(texture_->GetLevelDesc(0, &desc))) 
		throw_render_error("Render_Texture_D3d9::create - GetLevelDesc Failed  ");

	size_.width_ = desc.Width;
	size_.height_ = desc.Height;
}

void Render_Texture_D3d9::load_from_file(const std::string& filename) 
{
	Root* root = Root::singleton();

    if (!root)
        throw_render_error(" Root::singleton object has not been created!");

    root->resource_provider()->load_raw_data_container(filename, data_container_);
}

void Render_Texture_D3d9::load_from_memory(const void* buffer, size_t buffer_size) 
{
    cleanup_direct_d3d9_texture();

    D3DFORMAT fmt1, fmt2;
    D3DXIMAGE_INFO info;
    D3DSURFACE_DESC desc;

    IDirect3DDevice9 *device = owner_.device();

    if(*(DWORD*)buffer == 0x20534444) 
    {
        fmt1=D3DFMT_UNKNOWN;
        fmt2=D3DFMT_A8R8G8B8;
    }
    else
    {
        fmt1=D3DFMT_A8R8G8B8;
        fmt2=D3DFMT_UNKNOWN;
    }

    if( FAILED( D3DXCreateTextureFromFileInMemoryEx(device, buffer, buffer_size, D3DX_DEFAULT, D3DX_DEFAULT,
        1, 0, fmt1, D3DPOOL_MANAGED,D3DX_FILTER_NONE, D3DX_DEFAULT,	0, &info, NULL, &texture_)))
        if( FAILED( D3DXCreateTextureFromFileInMemoryEx( device, buffer, buffer_size, D3DX_DEFAULT, D3DX_DEFAULT,
            1, 0, fmt2, D3DPOOL_MANAGED, D3DX_FILTER_NONE,	D3DX_DEFAULT,	0, &info, NULL,&texture_)))
        {	
            throw_render_error("CreateTexture failed ");
        }


   if(FAILED(texture_->GetLevelDesc(0, &desc))) 
       throw_render_error("GetLevelDesc Failed  ");

    size_.width_ = desc.Width;
    size_.height_ = desc.Height;
}

void Render_Texture_D3d9::save_to_memory(void* buffer) 
{
}

void Render_Texture_D3d9::save_to_file(const std::string file)
{
	D3DXSaveTextureToFileA(file.c_str(), D3DXIFF_PNG, texture_, 0);
}

void Render_Texture_D3d9::set_direct_d3d9_texture(LPDIRECT3DTEXTURE9 tex)
{
    if (texture_ != tex)
    {
        cleanup_direct_d3d9_texture();

        texture_ = tex;
        if (texture_)
            texture_->AddRef();
    }
}

LPDIRECT3DTEXTURE9 Render_Texture_D3d9::get_direct_d3d9_texture() const
{
    return texture_;
}

void Render_Texture_D3d9::cleanup_direct_d3d9_texture()
{
    if (texture_)
    {
        texture_->Release();
        texture_ = 0;
    }
}

uint32_t *Render_Texture_D3d9::lock(bool readonly, int left, int top, int width, int height)
{
	if (texture_ == 0)
		return 0;

    int flags;
    RECT region, *prec;
    D3DSURFACE_DESC tdesc;
    D3DLOCKED_RECT trect;

    texture_->GetLevelDesc(0, &tdesc);
    if(tdesc.Format!=D3DFMT_A8R8G8B8 && tdesc.Format!=D3DFMT_X8R8G8B8) return 0;

    if(width && height)
    {
        region.left=left;
        region.top=top;
        region.right=left+width;
        region.bottom=top+height;
        prec=&region;
    }
    else prec=0;

    if(readonly) flags=D3DLOCK_READONLY;
    else flags=0;

    if(FAILED(texture_->LockRect(0, &trect, prec, flags)))
    {
        return 0;
    }

    return (uint32_t *)trect.pBits;
}

void Render_Texture_D3d9::unlock()
{
	if (texture_ == 0)
		return ;

    texture_->UnlockRect(0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
