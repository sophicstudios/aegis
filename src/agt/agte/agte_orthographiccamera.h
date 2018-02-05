#ifndef INCLUDED_AEGIS_AGTE_ORTHOGRAPHICCAMERA_H
#define INCLUDED_AEGIS_AGTE_ORTHOGRAPHICCAMERA_H

#include <agte_camera.h>
#include <agtm_rect.h>
#include <agtm_size2d.h>
#include <agtm_vector2.h>

namespace agte {

class OrthographicCamera : public agte::Camera
{
public:
    OrthographicCamera(agte::Camera::SurfacePtr surface);
    
    virtual ~OrthographicCamera();

    void translate(float x, float y);

    void translate(agtm::Vector2<float> const& vec);

protected:
    virtual void updateProjection(agtm::Matrix4<float>& projection);
};

} // namespace

#endif // INCLUDED
