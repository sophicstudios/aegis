#include <agtui_boxsizer.h>

namespace agtui {

BoxSizer::BoxSizer(BoxSizer::Direction direction)
: m_direction(direction)
{}

BoxSizer::~BoxSizer()
{}

void BoxSizer::addWidget(Sizer::WidgetPtr widget, size_t position, BoxSizer::SizeMode sizeMode)
{
}

agtm::Size2d<float> BoxSizer::doSize() const
{
}

void BoxSizer::doSize(agtm::Size2d<float> const& size)
{
}

agtm::Size2d<float> BoxSizer::doMinSize() const
{
}

agtm::Size2d<float> BoxSizer::doMaxSize() const
{
}

agtm::Size2d<float> BoxSizer::doBestSize() const
{
}

} // namespace
