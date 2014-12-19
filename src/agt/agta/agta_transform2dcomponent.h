#ifndef INCLUDED_AGTA_TRANSFORM2DCOMPONENT_H
#define INCLUDED_AGTA_TRANSFORM2DCOMPONENT_H

#include <agta_component.h>
#include <agtm_matrix3.h>
#include <agtm_vector2.h>

namespace agta {

class Transform2dComponent : public Component
{
public:
    Transform2dComponent();

    Transform2dComponent(agtm::Matrix3<float> const& initialTransform);

    virtual ~Transform2dComponent();

    virtual void update();

    agtm::Matrix3<float> const& transform() const;
    
    void rotate(float radians);

    void translate(agtm::Vector2<float> const& vec);

private:
    agtm::Matrix3<float> m_transform;
};

} // namespace

#endif // INCLUDED
