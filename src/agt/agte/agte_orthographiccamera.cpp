#include <agte_orthographiccamera.h>
#include <agtm_vector3.h>
#include <iostream>

namespace agte {

namespace {

agtm::Matrix4<float> calculateOrthographicProjection(agtm::Rect<float> const& rect)
{
    std::cout << "rect: " << rect << std::endl;
    
    float left = rect.x();
    float right = left + rect.width();
    float top = rect.y();
    float bottom = top + rect.height();
    // float near = -1.0f;
    // float far = 1.0f;

    agtm::Matrix4<float> projection(
        2.0f / (right - left), 0.0f,                  0.0f, 0.0f,
        0.0f,                  2.0 / (bottom - top),  0.0f, 0.0f,
        0.0f,                  0.0f,                 -1.0f, 0.0,
        0.0f,                  0.0f,                  0.0f, 1.0f);

    std::cout << "projection: " << projection << std::endl;

    return projection;
}

} // namespace

OrthographicCamera::OrthographicCamera(agte::Camera::SurfacePtr surface)
: Camera(surface)
{}


OrthographicCamera::~OrthographicCamera()
{}

void OrthographicCamera::translate(float x, float y)
{
    Camera::translate(agtm::Vector3<float>(x, y, 0.0f));
}

void OrthographicCamera::translate(agtm::Vector2<float> const& vec)
{
    Camera::translate(agtm::Vector3<float>(vec.x(), vec.y(), 0.0f));
}

void OrthographicCamera::updateProjection(agtm::Matrix4<float> &projection)
{
    agtm::Rect<float> const& vp = viewport();

    projection = calculateOrthographicProjection(agtm::Rect<float>::fromXYWidthHeight(-vp.width()/2.0f, -vp.height()/2.0f, vp.width(), vp.height()));
}

} // namespace
