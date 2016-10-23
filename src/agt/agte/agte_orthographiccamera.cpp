#include <agte_orthographiccamera.h>
#include <agtm_vector3.h>
#include <iostream>

namespace agte {

namespace {

agtm::Matrix4<float> calculateOrthographicProjection(agtm::Rect<float> const& rect)
{
    // set up orthographic projection
    float l = rect.x();
    float r = rect.x() + rect.width();
    float b = rect.y();
    float t = rect.y() + rect.height();
    float n = -1.0f;
    float f = 1.0f;

    std::cout << "updateProjectionMatrix: ["
        << " l: " << l
        << " r: " << r
        << " t: " << t
        << " b: " << b
        << " ]" << std::endl;

    agtm::Matrix4<float> projection(
        2.0f / (r - l), 0.0f,            0.0f,           -((r + l) / (r - l)),
        0.0f,           2.0f / (t - b),  0.0f,           -((t + b) / (t - b)),
        0.0f,           0.0f,           -2.0f / (f - n), -((f + n) / (f - n)),
        0.0f,           0.0f,            0.0f,           1.0f);

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
