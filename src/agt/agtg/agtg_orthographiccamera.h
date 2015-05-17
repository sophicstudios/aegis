#ifndef INCLUDED_AGTG_ORTHOGRAPHICCAMERA_H
#define INCLUDED_AGTG_ORTHOGRAPHICCAMERA_H

#include <agtg_camera.h>
#include <agtm_rect.h>
#include <agtm_size2d.h>
#include <agtm_vector2.h>

namespace agtg {

class OrthographicCamera : public agtg::Camera
{
public:
    OrthographicCamera(float width, float height);
    
    OrthographicCamera(agtm::Size2d<float> const& viewport);

    OrthographicCamera(agtm::Rect<float> const& viewport);
    
    virtual ~OrthographicCamera();

    void translate(float x, float y);

    void translate(agtm::Vector2<float> const& vec);

protected:
    virtual void updateProjection(agtm::Matrix4<float>& projection) = 0;
};


} // namespace

#endif // INCLUDED
