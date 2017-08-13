#ifndef INCLUDED_AGTC_VISUAL2dCOMPONENT_H
#define INCLUDED_AGTC_VISUAL2dCOMPONENT_H

#include <agta_mesh.h>
#include <agtg_renderingcontext.h>
#include <agtg_shaderprogram.h>
#include <agtm_matrix4.h>
#include <afth_uuid.h>
#include <memory>

namespace agtc {

class Visual2dComponent
{
public:
    typedef std::shared_ptr<agta::Mesh> MeshPtr;
    typedef std::shared_ptr<agtg::ShaderProgram> ShaderProgramPtr;

    Visual2dComponent();

    ~Visual2dComponent();

    afth::UUID const& id() const;

    void projectionMatrix(agtm::Matrix4<float> const& matrix);

    void modelViewMatrix(agtm::Matrix4<float> const& matrix);

private:
    afth::UUID m_id;
    ShaderProgramPtr m_shaderProgrem;
    MeshPtr m_mesh;
};

bool operator<(Visual2dComponent const& lhs, Visual2dComponent const& rhs);

} // namespace

#endif // INCLUDED
