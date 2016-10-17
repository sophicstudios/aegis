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

TransformComponent& TransformComponent::x(float x)
{
    m_transform(0, 3) = x;

    return *this;
}

TransformComponent& TransformComponent::y(float y)
{
    m_transform(1, 3) = y;

    return *this;
}

TransformComponent& TransformComponent::z(float z)
{
    m_transform(2, 3) = z;

    return *this;
}

TransformComponent& TransformComponent::transform(agtm::Matrix4<float> const& mat)
{
    m_transform = mat;

    return *this;
}

TransformComponent& TransformComponent::translate(agtm::Vector3<float> const& vec)
{
    m_transform(0, 3) += vec.x();
    m_transform(1, 3) += vec.y();
    m_transform(2, 3) += vec.z();

    return *this;
}

} // namespace
