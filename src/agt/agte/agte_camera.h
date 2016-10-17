#ifndef INCLUDED_AGTE_CAMERA_H
#define INCLUDED_AGTE_CAMERA_H

#include <agtm_matrix4.h>
#include <agtm_rect.h>
#include <memory>

namespace agte {

class Camera
{
public:
    virtual ~Camera() = 0;

    void lookAt(agtm::Vector3<float> const& vec);

    void translate(float x, float y, float z);

    void translate(agtm::Vector3<float> const& vec);

    agtm::Matrix4<float> const& projection() ;

    agtm::Matrix4<float> const& view();

    agtm::Rect<float> const& viewport();

    void viewport(agtm::Rect<float> const& viewport);

protected:
    Camera(agtm::Rect<float> const& viewport, agtm::Matrix4<float> const& projection);

    void update();

    virtual void updateProjection(agtm::Matrix4<float>& projection) = 0;

private:
    Camera();
    
    bool m_dirty;
    agtm::Vector3<float> m_position;
    agtm::Vector3<float> m_direction;
    agtm::Vector3<float> m_up;
    agtm::Matrix4<float> m_projection;
    agtm::Matrix4<float> m_view;
    agtm::Rect<float> m_viewport;
};

} // namespace

#endif // INCLUDED
