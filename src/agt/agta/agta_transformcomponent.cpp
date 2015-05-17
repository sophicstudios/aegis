#include <agta_transformcomponent.h>

namespace agta {

TransformComponent::TransformComponent()
: m_transform(agtm::Matrix4<float>::identity())
{}

TransformComponent::TransformComponent(agtm::Matrix4<float> const& initialTransform)
: m_transform(initialTransform)
{}

TransformComponent::~TransformComponent()
{}

agtm::Matrix4<float> const& TransformComponent::transform() const
{
    return m_transform;
}

void TransformComponent::translate(agtm::Vector3<float> const& vec)
{
    m_transform(0, 3) += vec.x();
    m_transform(1, 3) += vec.y();
    m_transform(2, 3) += vec.z();
}

} // namespace
