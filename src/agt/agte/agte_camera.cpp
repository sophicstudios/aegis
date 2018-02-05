#include <agte_camera.h>
#include <aftthr_scopedlock.h>

namespace agte {

Camera::Camera()
{}

Camera::Camera(SurfacePtr surface)
: m_id(afth::UUID::v4()),
  m_surface(surface),
  m_boundsDirty(true),
  m_dirty(true),
  m_projection(agtm::Matrix4<float>::identity()),
  m_view(agtm::Matrix4<float>::identity())
{
    Surface::BoundsChangedCallback cb = std::bind(&Camera::onBoundsChanged, this, std::placeholders::_1);
    m_surface->boundsChangedCallback(cb);
}

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
    return m_bounds;
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

// Can be called from another thread, so needs protection around
// dirty bounds rect and bounds dirty flag
void Camera::onBoundsChanged(agtm::Rect<float> const& bounds)
{
    aftthr::ScopedLock<aftthr::Mutex> lock(m_boundsMutex);
    m_dirtyBounds = bounds;
    m_boundsDirty = true;
}

void Camera::update()
{
    // bounds rect and bounds dirty flag need to be protected since
    // they can be written to from another thread
    {
        aftthr::ScopedLock<aftthr::Mutex> lock(m_boundsMutex);
        if (m_boundsDirty)
        {
            m_dirty = true;
            m_bounds = m_dirtyBounds;
            m_boundsDirty = false;
        }
    }

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
