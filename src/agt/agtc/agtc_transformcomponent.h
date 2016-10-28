#ifndef INCLUDED_AGTC_TRANSFORMCOMPONENT_H
#define INCLUDED_AGTC_TRANSFORMCOMPONENT_H

#include <agtm_matrix4.h>
#include <agtm_vector3.h>

namespace agtc {

class TransformComponent
{
public:
    TransformComponent();

    virtual ~TransformComponent();

    agtm::Matrix4<float> const& transform() const;

    TransformComponent& transform(agtm::Matrix4<float> const& mat);

    TransformComponent& translate(agtm::Vector3<float> const& vec);

    TransformComponent& scale(agtm::Vector3<float> const& scale);

private:
    agtm::Matrix4<float> m_transform;
};

} // namespace

#endif // INCLUDED
