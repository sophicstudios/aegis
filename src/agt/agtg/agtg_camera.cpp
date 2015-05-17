#include <agtg_camera.h>

namespace agtg {

Camera::Camera()
{}

Camera::Camera(agtm::Rect<float> const& viewport, agtm::Matrix4<float> const& projection)
: m_viewport(viewport),
  m_projection(projection),
  m_view(agtm::Matrix4<float>::identity())
{}

Camera::~Camera()
{}

agtm::Matrix4<float> const& Camera::projection()
{
    if (m_dirty) {
        update();
    }

    return m_projection;
}

agtm::Matrix4<float> const& Camera::view()
{
    if (m_dirty) {
        update();
    }

    return m_view;
}

agtm::Rect<float> const& Camera::viewport()
{
    return m_viewport;
}

void Camera::viewport(agtm::Rect<float> const& viewport)
{
    m_viewport = viewport;
    m_dirty = true;
}

void Camera::lookAt(agtm::Vector3<float> const& vec)
{
    m_dirty = true;
}

void Camera::translate(float x, float y, float z)
{
    translate(agtm::Vector3<float>(x, y, z));
}

void Camera::translate(agtm::Vector3<float> const& vec)
{
    m_position += vec;
    m_dirty = true;
}

void Camera::update()
{
    updateProjection(m_projection);
    
    // apply rotation

    // apply translation
    m_view(0, 3) += m_position.x();
    m_view(1, 3) += m_position.y();
    m_view(2, 3) += m_position.z();

    m_dirty = false;
}

} // namespace
