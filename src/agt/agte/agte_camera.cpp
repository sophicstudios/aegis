#include <agte_camera.h>

namespace agte {

Camera::Camera()
{}

Camera::Camera(SurfacePtr surface)
: m_id(afth::UUID::v4()),
  m_surface(surface),
  m_projection(agtm::Matrix4<float>::identity()),
  m_view(agtm::Matrix4<float>::identity())
{}

Camera::~Camera()
{}

afth::UUID const& Camera::id() const
{
    return m_id;
}

agtm::Matrix4<float> const& Camera::projection()
{
    return m_projection;
}

agtm::Matrix4<float> const& Camera::view()
{
    return m_view;
}

agtm::Rect<float> Camera::viewport()
{
    return m_surface->viewport();
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
    if (m_dirty)
    {
        updateProjection(m_projection);
        
        // apply rotation

        // apply translation
        m_view(0, 3) += m_position.x();
        m_view(1, 3) += m_position.y();
        m_view(2, 3) += m_position.z();

        m_dirty = false;
    }
}

} // namespace
