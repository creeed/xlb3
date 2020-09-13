#ifndef __XLBE_RENDER_SYSTEM_D3D9_H__
#define __XLBE_RENDER_SYSTEM_D3D9_H__

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include <d3d9.h>
#include <d3dx9.h>

#include "XlbePrereqs.h"
#include "XlbeConfigOption.h"
#include "XlbeRenderSystem.h"
#include "XlbeRenderTextureD3d9.h"
#include "XlbeRenderWindowD3d9.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////////////////////////
class Render_System_D3d9 : public Render_System
{
public:
	typedef std::map<std::string, Render_Texture_D3d9*> Textures;

public:
    Render_System_D3d9();
    virtual ~Render_System_D3d9();

public:
    virtual Render_Window *initialise(const std::string& title, unsigned int width, unsigned int height, bool fullscreen);
    virtual void shutdown();

    virtual void set_texture_filter(bool filter) ;

	virtual void setup_view_matrix();
	virtual void setup_projection_matrix() ;
	virtual void set_camera(const Vector3 &pos, const Vector3 &view, const Vector3 &up);

    virtual bool begin_scene() ;
    virtual void end_scene() ;
    virtual void clear(unsigned long color) ;

    virtual void render_line(Render_Line *line) ;
    virtual void render_triple(Render_Triple *triple) ;
    virtual void render_quad(Render_Quad *quad) ;

    virtual Render_Texture* create_texture(const std::string& name, int width, int height);
	virtual Render_Texture* create_texture(const std::string& filename);
	virtual Render_Texture* get_texture(const std::string& name);
	virtual void destroy_texture(const std::string& name);
    virtual void destroy_all_textures();

    virtual void *get_device() const { return device(); }

public:
    IDirect3D9 *d3d() const { return d3d_; }
    IDirect3DDevice9 *device() const { return device_; }
    void set_d3d(IDirect3D9 *d3d) { d3d_ = d3d; }
    void set_device(IDirect3DDevice9 *device) { device_ = device; }

    void initialise_buffer();
    void destroy_buffer();

    bool is_device_lost() { return device_lost_; }      
    void restore_lost_device();
    void notify_device_lost () { device_lost_ = true; }

    void set_blend_mode(Render_Blend blend);
    void set_texture(Render_Texture *tex);

	void render_batch(bool end_scene);

private:
    IDirect3D9*	d3d_;
    IDirect3DDevice9* device_;
    IDirect3DVertexBuffer9 *vertex_buffer_;
    IDirect3DIndexBuffer9  *index_buffer_;

    D3DXMATRIX view_matrix_;
    D3DXMATRIX projection_matrix_;

	int	prim_count_;
	Vertex*	vertarray_;
	Textures textures_;
    Render_Blend blend_mode_ ;  
    Render_Texture *render_texture_;
    
    bool device_lost_;
    Render_Window_D3d9 *primary_window_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////

}
#endif