#include <agtui_sizer.h>

namespace agtui {

Sizer::Sizer()
{}

Sizer::~Sizer()
{}

agtm::Size2d<float> Sizer::size() const
{
    return doSize();
}

void Sizer::size(agtm::Size2d<float> const& size)
{
    doSize(size);
}

agtm::Size2d<float> Sizer::minSize() const
{
    return doMinSize();
}

agtm::Size2d<float> Sizer::maxSize() const
{
    return doMaxSize();
}

agtm::Size2d<float> Sizer::bestSize() const
{
    return doBestSize();
}

} // namespace
