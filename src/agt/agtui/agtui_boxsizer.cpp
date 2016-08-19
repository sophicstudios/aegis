#include <agtui_boxsizer.h>

namespace agtui {

BoxSizer::Flags::Flags()
{}

BoxSizer::Flags::~Flags()
{}

BoxSizer::Flags& BoxSizer::Flags::sizeMode(BoxSizer::SizeMode sizeMode)
{
    m_sizeMode = sizeMode;
    return *this;
}

BoxSizer::SizeMode BoxSizer::Flags::sizeMode() const
{
    return m_sizeMode;
}

BoxSizer::Flags& BoxSizer::Flags::size(float size)
{
    m_size = size;
    return *this;
}

float BoxSizer::Flags::size() const
{
    return m_size;
}

BoxSizer::BoxSizer(BoxSizer::Direction direction)
: m_direction(direction)
{}

BoxSizer::~BoxSizer()
{}

BoxSizer::Status BoxSizer::push_front(std::shared_ptr<agtui::Widget> widget, BoxSizer::Flags flags)
{
    std::pair<WidgetMap::iterator, bool> mapResult = m_widgetMap.insert(widget->id());

    if (!mapResult.second) {
        return Status_ERROR_WIDGET_ALREADY_EXISTS;
    }

    Info info;
    info.flags = flags;
    info.size = 0;

    m_widgets.push_front(std::make_pair(info, widget));

    return Status_OK;
}

BoxSizer::Status BoxSizer::push_back(std::shared_ptr<agtui::Widget> widget, BoxSizer::Flags flags)
{
    std::pair<WidgetMap::iterator, bool> mapResult = m_widgetMap.insert(widget->id());

    if (!mapResult.second) {
        return Status_ERROR_WIDGET_ALREADY_EXISTS;
    }

    Info info;
    info.flags = flags;
    info.size = 0;

    m_widgets.push_back(std::make_pair(info, widget));

    return Status_OK;
}

BoxSizer::Status BoxSizer::insert(std::shared_ptr<agtui::Widget> widget, size_t position, BoxSizer::Flags flags)
{
    std::pair<WidgetMap::iterator, bool> mapResult = m_widgetMap.insert(widget->id());

    if (!mapResult.second) {
        return Status_ERROR_WIDGET_ALREADY_EXISTS;
    }

    Info info;
    info.flags = flags;
    info.size = 0;


    WidgetList::iterator it = m_widgets.begin();
    size_t i = 0;
    while (it != m_widgets.end() && i < position) {
        ++it;
        ++i;
    }

    m_widgets.insert(it, std::make_pair(info, widget));

    return Status_OK;
}

agtm::Size2d<float> BoxSizer::doSize() const
{
    return agtm::Size2d<float>(-1, -1);
}

void BoxSizer::doSize(agtm::Size2d<float> const& size)
{
    agtm::Size2d<float> minSize = doMinSize();

    float totalMajorSize = getSizeInMajorDirection(size);
    float totalMinorSize = getSizeInMinorDirection(size);
    float minMajorSize = getSizeInMajorDirection(minSize);
    float minMinorSize = getSizeInMinorDirection(minSize);

    float remaining = totalMajorSize;

    std::vector<float> majorSizes(m_widgets.size(), -1.0f);

    if (totalMajorSize < minMajorSize)
    {
        // if there's not enought space to satisfy the minimum size
        // we should first allocate what space we can to fixed size
        // elements, then distribute the rest to the proportional
        // elements until there's nothing left.
    }
    else
    {
        std::vector<int> majorSizes(m_widgets.size(), Widget::DEFAULT_SIZE);
        WidgetList::iterator it;
        int n;
        for (it = m_widgets.begin(), n = 0; ; ++it, ++n)
        {
            float majorSize = getSizeInMajorDirection(it->second->actualMinSize());
            if (it->first.flags.sizeMode() == SizeMode_RELATIVE)
            {
            }
        }

        // loop through the children until all conditions of proportions,
        // fixed, min and max sizes are satisfied
        
    }
}

agtm::Size2d<float> BoxSizer::doMinSize() const
{
    float width = -1;
    float height = -1;
    float minorSize = 0;
    float majorSize = 0;
    float largestMinSizeToProp = 0;
    float totalProp = 0;

    WidgetList::const_iterator it = m_widgets.begin();
    WidgetList::const_iterator end = m_widgets.end();

    for (; it != end; ++it)
    {
        // In major direction, there are two cases.
        // if proportional, find the largest widget min size / proportion
        // ratio to satisfy.
        // if fixed, just sum up the min sizes
        SizeMode sizeMode = it->first.flags.sizeMode();
        float widgetMajorSize = getSizeInMajorDirection(it->second->actualMinSize());
        if (sizeMode == SizeMode_RELATIVE)
        {
            totalProp += it->first.size;
            float minSizeToProp = widgetMajorSize / it->first.size;
            if (minSizeToProp > largestMinSizeToProp)
            {
                largestMinSizeToProp = minSizeToProp;
            }
        }
        else if (sizeMode == SizeMode_FIXED)
        {
            majorSize += widgetMajorSize == -1 ? 0 : widgetMajorSize;
        }

        // In minor direction, just find the largest min size
        float widgetMinorSize = getSizeInMinorDirection(it->second->actualMinSize());
        if (widgetMinorSize > minorSize)
        {
            minorSize = widgetMinorSize;
        }
    }

    majorSize += (largestMinSizeToProp * totalProp);

    return m_direction == Direction_VERTICAL ?
        agtm::Size2d<float>(minorSize, majorSize) : agtm::Size2d<float>(majorSize, minorSize);
}

agtm::Size2d<float> BoxSizer::doMaxSize() const
{
    return agtm::Size2d<float>(-1.0f, -1.0f);
}

float BoxSizer::getSizeInMajorDirection(agtm::Size2d<float> const& size) const
{
    return m_direction == Direction_VERTICAL ? size.height() : size.width();
}

float BoxSizer::getSizeInMinorDirection(agtm::Size2d<float> const& size) const
{
    return m_direction == Direction_VERTICAL ? size.width() : size.height();
}

} // namespace
