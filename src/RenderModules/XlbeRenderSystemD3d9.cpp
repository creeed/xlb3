#include "XlbeException.h"
#include "XlbeRenderSystemD3d9.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////////////////////
Render_System_D3d9::Render_System_D3d9()
:d3d_(0),
device_(0),
vertex_buffer_(0),
index_buffer_(0),
blend_mode_(BLEND_COLORMUL_ALPHABLEND), 
render_texture_(0),
device_lost_(false),
primary_window_(0),
prim_count_(0),
vertarray_(0)
{
}

Render_System_D3d9::~Render_System_D3d9()
{
    shutdown();
}

Render_Window *Render_System_D3d9::initialise(const std::string& title, unsigned int width, unsigned int height, bool fullscreen)
{
    d3d_ = Direct3DCreate9(D3D_SDK_VERSION); 
    if(d3d_== 0)
    {
        throw_render_error("Can't create D3D interface");
    }

    Render_Window *rw = new Render_Window_D3d9(GetModuleHandle(0), this);
    rw->create(title, width, height, fullscreen);

    primary_window_ = (Render_Window_D3d9 *)rw;

	initialise_buffer();
	
	setup_projection_matrix();
	setup_view_matrix();

	return rw;
}

void Render_System_D3d9::shutdown()
{
	destroy_buffer();

    if(device_)
    {
        device_->Release();
        device_=0; 
    }

    if(d3d_)
    { 
        d3d_->Release();
        d3d_=0;    
    }
}


void Render_System_D3d9::set_texture_filter(bool filter) 
{
	__super::set_texture_filter(filter);

	if (device_)
	{
		render_batch(false);

		if (texture_filter_ == false)
		{
			device_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_NONE);
			device_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_NONE);
		}
		else
		{
			device_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
			device_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
		}
	}
}

void Render_System_D3d9::set_camera(const Vector3 &pos, const Vector3 &view, const Vector3 &up)
{
	render_batch(false);

	D3DXVECTOR3 aeye(pos.x_, pos.y_, pos.z_);
	D3DXVECTOR3 aat(view.x_, view.y_, view.z_);
	D3DXVECTOR3 aup(up.x_, up.y_, up.z_);

	D3DXMatrixIdentity(&view_matrix_);
	D3DXMatrixLookAtRH(&view_matrix_, &aeye, &aat, &aup);

	device_->SetTransform(D3DTS_VIEW, &view_matrix_);
}

bool Render_System_D3d9::begin_scene()
{
    //if (device_lost_)
    //{
        HRESULT hr = device_->TestCooperativeLevel();
		if (FAILED(hr))
		{
			if (hr == D3DERR_DEVICELOST )
			{
				Sleep(50);
				return false;
			}
			else if( hr == D3DERR_DEVICENOTRESET )
			{
				restore_lost_device();

				if (is_device_lost())
				{
					Sleep(50);
					return false;
				}
			}
			else
			{
				throw_render_error("Render_System_D3d9::begin_scene -- Reset error");
			}
		}
		else
		{
			device_lost_ = false;
		}

    //}

    device_->BeginScene();
	device_->SetTransform(D3DTS_VIEW, &view_matrix_);
	vertex_buffer_->Lock( 0, 0, (VOID**)&vertarray_, 0 );

    return true;
}

void Render_System_D3d9::end_scene()
{
	render_batch(true);
    device_->EndScene();
	
    HRESULT hr = device_->Present( NULL, NULL, NULL, NULL );

    if (D3DERR_DEVICELOST == hr )
    {
        notify_device_lost();
    }
    else if (FAILED(hr))
    {
        throw_render_error("Render_System_D3d9::end_scene -- Error Presenting surfaces");

        return;
    }
}

void Render_System_D3d9::clear(unsigned long color)
{
    device_->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 1.0f, 0 );
}

void Render_System_D3d9::render_line(Render_Line *line) 
{
    //set_texture(0);
    //set_blend_mode(line->blend_);

    //Vertex*	vertarray;
    //vertex_buffer_->Lock(0, 0, (VOID **)&vertarray, 0);
    //memcpy(vertarray, line->vertex_, sizeof(Vertex)*Render_Line::count_);
    //vertex_buffer_->Unlock();      

    //device_->DrawPrimitive(D3DPT_LINELIST, 0, 1);
}

void Render_System_D3d9::render_triple(Render_Triple *triple) 
{
}

void Render_System_D3d9::render_quad(Render_Quad *quad)
{
	if(vertex_buffer_)
	{
		if(prim_count_ >= 1000 || render_texture_ != quad->texture_ || blend_mode_ != quad->blend_)
		{
			render_batch(false);

			set_texture(quad->texture_);
            set_blend_mode(quad->blend_);
		}

		memcpy(&vertarray_[prim_count_*4], quad->vertex_, sizeof(Vertex)*Render_Quad::count_);
		prim_count_++;
	}
}

Render_Texture* Render_System_D3d9::create_texture(const std::string& name, int width, int height)
{
    Textures::iterator iter = textures_.find(name);

    if (iter != textures_.end())
        throw_render_error(name + ": texture is create. ");

	Render_Texture_D3d9* tex = new Render_Texture_D3d9(*this, name, width, height);
    textures_[name] = tex;

    return tex;
}

Render_Texture* Render_System_D3d9::create_texture(const std::string& filename)
{
    Textures::iterator iter = textures_.find(filename);

    if (iter != textures_.end())
	{
        //throw_render_error(filename + ": texture is create. ");
		return iter->second;
	}

	Render_Texture_D3d9* tex = new Render_Texture_D3d9(*this, filename);
    textures_[filename] = tex;

    return tex;
}

Render_Texture* Render_System_D3d9::get_texture(const std::string& name)
{
    Textures::iterator iter = textures_.find(name);

    if (iter == textures_.end())
        throw_render_error(name + ": texture is not find. ");

	return iter->second;
}

void Render_System_D3d9::destroy_texture(const std::string& name)
{
    Textures::iterator iter = textures_.find(name);

    if (iter != textures_.end())
	{
		textures_.erase(iter);
	}
}

void Render_System_D3d9::destroy_all_textures()
{
    Textures::iterator iend = textures_.begin();
	for(Textures::iterator i = textures_.begin(); i != iend; ++i)
	{
		delete i->second;
	}

	textures_.clear();
}

void Render_System_D3d9::set_blend_mode(Render_Blend blend)
{
    if (blend == blend_mode_)
    {
        return;
    }

    if (blend == BLEND_COLORMUL_ALPHAADD)
    {
        device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
        device_->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
    }
    else if (blend == BLEND_COLORADD_ALPHAADD)
    {
        device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
        device_->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_ADD);
    }
    else if (blend == BLEND_COLORMUL_ALPHABLEND)
    {
        device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
        device_->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
    }
    else if (blend == BLEND_COLORADD_ALPHABLEND)
    {
        device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
        device_->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_ADD);
    }
	else if (blend == BLEND_COLORSUBTRACT_ALPHABLEND)
    {
        device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
        device_->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SUBTRACT);
    }

    blend_mode_ = blend;
}

void Render_System_D3d9::set_texture(Render_Texture *tex)
{
    if (tex == render_texture_)
    {
        return;
    }

    render_texture_ = tex;

    if (render_texture_)
    {
        //render_texture_->ckeck_loaded();
        device_->SetTexture( 0, ((Render_Texture_D3d9 *)tex)->get_direct_d3d9_texture() );
    }
    else
    {
        device_->SetTexture( 0, 0 );
    }
}

void Render_System_D3d9::setup_view_matrix()
{
	render_batch(false);

	const float fov = 0.523598776f;
	const float w = geometry_width_;
	const float h = geometry_height_;
	const float aspect = w / h;
	const float midx = w * 0.5f;
	const float midy = h * 0.5f;
	float view_distance = midx / (aspect * 0.267949192431123f) ;

	D3DXVECTOR3 eye(midx, midy, -view_distance);
	D3DXVECTOR3 at(midx, midy, 1);
	D3DXVECTOR3 up(0, -1, 0);

	D3DXMatrixIdentity(&view_matrix_);
	D3DXMatrixLookAtRH(&view_matrix_, &eye, &at, &up);

	//const float w = geometry_width_;
	//const float h = geometry_height_;
	//D3DXMATRIX tmp;
	//D3DXMatrixIdentity(&tmp);
	//D3DXMatrixIdentity(&view_matrix_);
	//D3DXMatrixScaling(&view_matrix_, 1.0f, -1.0f, 1.0f);
	//D3DXMatrixTranslation(&tmp, -0.5f, h + 0.5f, 0.0f);
	//D3DXMatrixMultiply(&view_matrix_, &view_matrix_, &tmp);
	//D3DXMatrixOrthoOffCenterLH(&tmp, 0, (float)w, 0, (float)h, 0.0f, 1.0f);
	//D3DXMatrixMultiply(&view_matrix_, &view_matrix_, &tmp);

	device_->SetTransform(D3DTS_VIEW, &view_matrix_);
}

void Render_System_D3d9::setup_projection_matrix()
{
	render_batch(false);

	const float w = geometry_width_;
	const float h = geometry_height_;
	const float fov = 0.523598776f;
	const float aspect = w / h;
	const float midx = w * 0.5f;
	const float midy = h * 0.5f;
	float view_distance = midx / (aspect * 0.267949192431123f);
	D3DXMatrixIdentity(&projection_matrix_);
	D3DXMatrixOrthoOffCenterRH(&projection_matrix_, -midx+0.5f, midx, -midy-0.5f, (float)midy, view_distance*0.5f, view_distance*2.0f);
	//D3DXMatrixPerspectiveFovRH(&projection_matrix_, fov, aspect, view_distance*0.5f, view_distance*2.0f);

	device_->SetTransform( D3DTS_PROJECTION, &projection_matrix_ );
}

void Render_System_D3d9::initialise_buffer()
{
    unsigned long length = 4000 * sizeof(Vertex);

    if (FAILED(device_->CreateVertexBuffer(length, 0, 0, D3DPOOL_DEFAULT, &vertex_buffer_,0)))
        throw_render_error("Render_System_D3d9::initialise_buffer() -- CreateVertexBuffer failure ");

    if( FAILED( device_->CreateIndexBuffer(4000 * 6 / 4 * sizeof(WORD),D3DUSAGE_WRITEONLY,
        D3DFMT_INDEX16, D3DPOOL_DEFAULT, &index_buffer_,0 )))
    {
        throw_render_error("Render_System_D3d9::initialise_buffer() -- CreateIndexBuffer failure ");
    }

    WORD *indices, n = 0;
    if( FAILED( index_buffer_->Lock(0, 0, (VOID**)&indices, 0)))
    {
        throw_render_error("Render_System_D3d9::initialise_buffer() -- Lock IndexBuffer failure ");
    }

    for(int i=0; i < 4000 / 4; i++) 
    {
        *indices++ = n;
        *indices++ = n+1;
        *indices++ = n+2;
        *indices++ = n+2;
        *indices++ = n+3;
        *indices++ = n;

        n += 4;
    }

    index_buffer_->Unlock();

    device_->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 );
    device_->SetStreamSource( 0, vertex_buffer_, 0, sizeof(Vertex) );
    device_->SetIndices(index_buffer_);

    device_->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
    device_->SetRenderState( D3DRS_LIGHTING, FALSE );

    device_->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
    device_->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
    device_->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

    device_->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );
    device_->SetRenderState( D3DRS_ALPHAREF, 0x01 );
    device_->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL );

    device_->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
    device_->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    device_->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

    device_->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );
    device_->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
    device_->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );

    set_texture_filter(texture_filter_);
}

void Render_System_D3d9::destroy_buffer()
{
    if(index_buffer_)
    {
        device_->SetIndices(0);
        index_buffer_->Release();
        index_buffer_ = 0;
    }

    if(vertex_buffer_)
    {
        device_->SetStreamSource( 0, 0, 0, sizeof(Vertex) );
        vertex_buffer_->Release();
        vertex_buffer_ = 0;
    }
}

void Render_System_D3d9::restore_lost_device()
{
    destroy_buffer();

    D3DPRESENT_PARAMETERS* pres_params = primary_window_->presentation_parameters();
    HRESULT hr = device_->Reset(pres_params);

    if (hr == D3DERR_DEVICELOST)
    {
        return;
    }
    else if (FAILED(hr))
    {
        throw_render_error("Render_System_D3d9::restore_lost_device -- Reset error");
    }

    initialise_buffer();
	setup_projection_matrix();
	setup_view_matrix();

	device_lost_ = false;
}

void Render_System_D3d9::render_batch(bool end_scene)
{
	if(vertarray_)
	{
		vertex_buffer_->Unlock();
		
		if(prim_count_)
		{
			device_->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, prim_count_ << 2, 0, prim_count_ << 1);
			prim_count_ = 0;
		}

		if(end_scene) vertarray_ = 0;
		else vertex_buffer_->Lock( 0, 0, (VOID**)&vertarray_, 0 );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
}