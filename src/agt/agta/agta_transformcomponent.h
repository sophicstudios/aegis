#ifndef INCLUDED_AGTA_TRANSFORMCOMPONENT_H
#define INCLUDED_AGTA_TRANSFORMCOMPONENT_H

#include <agtm_matrix4.h>
#include <agtm_vector3.h>

namespace agta {

class TransformComponent
{
public:
    TransformComponent();

    virtual ~TransformComponent();

    agtm::Matrix4<float> const& transform() const;

    TransformComponent& x(float x);

    TransformComponent& y(float y);

    TransformComponent& z(float z);

    TransformComponent& transform(agtm::Matrix4<float> const& mat);

    TransformComponent& translate(agtm::Vector3<float> const& vec);

private:
    agtm::Matrix4<float> m_transform;
};

} // namespace

#endif // INCLUDED
