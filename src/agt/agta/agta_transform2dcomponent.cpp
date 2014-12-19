#include <agta_transform2dcomponent.h>

namespace agta {

Transform2dComponent::Transform2dComponent(agtm::Matrix3<float> const& initialTransform)
: m_transform(initialTransform)
{}

Transform2dComponent::~Transform2dComponent()
{}

void Transform2dComponent::update()
{
    // nothing to do
}

agtm::Matrix3<float> const& Transform2dComponent::transform() const
{
    return m_transform;
}

void Transform2dComponent::rotate(float theta)
{
    float cosTheta = cos(theta);
    float sinTheta = sin(theta);

    m_transform *= agtm::Matrix3<float>(
        cosTheta, -sinTheta, 0,
        cosTheta,  sinTheta, 0,
        0,         0,        1);
}

void Transform2dComponent::translate(agtm::Vector2<float> const& vec)
{
    m_transform += agtm::Matrix3<float>(
        1, 0, vec.x(),
        0, 1, vec.y(),
        0, 0, 1);
}

} // namespace
