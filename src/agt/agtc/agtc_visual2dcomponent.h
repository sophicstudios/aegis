#ifndef INCLUDED_AEGIS_AGTC_VISUAL2dCOMPONENT_H
#define INCLUDED_AEGIS_AGTC_VISUAL2dCOMPONENT_H

#include <agta_assetpool.h>
#include <agta_mesh.h>
#include <agta_material.h>
#include <agtg_shaderprogram.h>
#include <afth_uuid.h>

namespace agtc {

class Visual2dComponent
{
public:
    Visual2dComponent();

    ~Visual2dComponent();

    void shaderId(size_t shaderId);

    size_t shaderId() const;

    void meshId(size_t meshId);

    size_t meshId() const;

    void materialId(size_t materialId);

    size_t materialId() const;

    void spriteSize(agtm::Size2d<float> const& size);

    agtm::Size2d<float> spriteSize() const;

    void spriteOffset(agtm::Vector2<float> const& offset);

    agtm::Vector2<float> spriteOffset() const;

private:
    size_t m_shaderId;
    size_t m_meshId;
    size_t m_materialId;
    agtm::Size2d<float> m_spriteSize;
    agtm::Vector2<float> m_spriteOffset;
};

bool operator<(Visual2dComponent const& lhs, Visual2dComponent const& rhs);

} // namespace

#endif // INCLUDED
