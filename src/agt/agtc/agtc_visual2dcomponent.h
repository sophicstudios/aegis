#ifndef INCLUDED_AGTC_VISUAL2dCOMPONENT_H
#define INCLUDED_AGTC_VISUAL2dCOMPONENT_H

#include <agta_sprite2dmaterial.h>
#include <agta_mesh.h>
#include <agtg_renderingcontext.h>
#include <agtg_shaderprogram.h>
#include <afth_uuid.h>
#include <memory>

namespace agtc {

class Visual2dComponent
{
public:
    typedef std::shared_ptr<agta::Mesh> MeshPtr;
    typedef std::shared_ptr<agta::Sprite2dMaterial> Sprite2dMaterialPtr;
    typedef std::shared_ptr<agtg::ShaderProgram> ShaderProgramPtr;

    Visual2dComponent();

    ~Visual2dComponent();

    afth::UUID const& id() const;

    void mesh(MeshPtr mesh);

    MeshPtr mesh() const;

    void material(Sprite2dMaterialPtr material);

    Sprite2dMaterialPtr material() const;
    
    void draw(agtg::RenderingContext& renderingContext);

private:
    afth::UUID m_id;
    MeshPtr m_mesh;
    Sprite2dMaterialPtr m_material;
    
};

} // namespace

#endif // INCLUDED
