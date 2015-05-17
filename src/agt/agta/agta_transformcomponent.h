#ifndef INCLUDED_AGTA_TRANSFORMCOMPONENT_H
#define INCLUDED_AGTA_TRANSFORMCOMPONENT_H

#include <agtm_matrix4.h>
#include <agtm_vector3.h>

namespace agta {

class TransformComponent
{
public:
    TransformComponent();

    TransformComponent(agtm::Matrix4<float> const& initialTransform);

    virtual ~TransformComponent();

    agtm::Matrix4<float> const& transform() const;

    void translate(agtm::Vector3<float> const& vec);

private:
    agtm::Matrix4<float> m_transform;
};

} // namespace

#endif // INCLUDED
