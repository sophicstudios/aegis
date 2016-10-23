#ifndef INCLUDED_AGTE_CAMERA_H
#define INCLUDED_AGTE_CAMERA_H

#include <agte_surface.h>
#include <agtm_matrix4.h>
#include <agtm_rect.h>
#include <actp_mutex.h>
#include <afth_uuid.h>
#include <memory>

namespace agte {

class Camera
{
public:
    typedef std::shared_ptr<agte::Surface> SurfacePtr;

    virtual ~Camera() = 0;

    afth::UUID const& id() const;

    void lookAt(agtm::Vector3<float> const& vec);

    void translate(float x, float y, float z);

    void translate(agtm::Vector3<float> const& vec);

    agtm::Matrix4<float> const& projection() ;

    agtm::Matrix4<float> const& view();

    agtm::Rect<float> viewport();

    void update();

protected:
    Camera(SurfacePtr surface);

    virtual void updateProjection(agtm::Matrix4<float>& projection) = 0;

    void dirty(bool value);

    bool dirty() const;

private:
    Camera();

    void onBoundsChanged(agtm::Rect<float> const& bounds);

    afth::UUID m_id;
    SurfacePtr m_surface;
    actp::Mutex m_boundsMutex;
    agtm::Rect<float> m_bounds;
    agtm::Rect<float> m_dirtyBounds;
    bool m_boundsDirty;
    bool m_dirty;
    agtm::Vector3<float> m_position;
    agtm::Vector3<float> m_direction;
    agtm::Vector3<float> m_up;
    agtm::Matrix4<float> m_projection;
    agtm::Matrix4<float> m_view;
};

} // namespace

#endif // INCLUDED
