#include <agtc_transformcomponent.h>

namespace agtc {

TransformComponent::TransformComponent()
: m_transform(agtm::Matrix4<float>::identity())
{}

TransformComponent::~TransformComponent()
{}

agtm::Matrix4<float> const& TransformComponent::transform() const
{
    return m_transform;
}

TransformComponent& TransformComponent::transform(agtm::Matrix4<float> const& mat)
{
    m_transform = mat;

    return *this;
}

TransformComponent& TransformComponent::scale(agtm::Vector3<float> const& vec)
{
    m_transform *= agtm::Matrix4<float>(
        vec.x(), 0.0f,    0.0f,    0.0f,
        0.0f,    vec.y(), 0.0f,    0.0f,
        0.0f,    0.0f,    vec.z(), 0.0f,
        0.0f,    0.0f,    0.0f,    1.0f);

    return *this;
}

TransformComponent& TransformComponent::translate(agtm::Vector3<float> const& vec)
{
    m_transform *= agtm::Matrix4<float>(
        1.0f, 0.0f, 0.0f, vec.x(),
        0.0f, 1.0f, 0.0f, vec.y(),
        0.0f, 0.0f, 1.0f, vec.z(),
        0.0f, 0.0f, 0.0f, 1.0f);

    return *this;
}

} // namespace
