#include <agtui_boxsizer.h>

namespace agtui {

BoxSizer::Flags::Flags()
: m_sizeMode(BoxSizer::SizeMode_RELATIVE),
  m_size(1.0f)
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
: m_direction(direction),
  m_cachedSize(0.0f, 0.0f)
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

    size(m_cachedSize);

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

    size(m_cachedSize);

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

    size(m_cachedSize);
    
    return Status_OK;
}

agtm::Size2d<float> BoxSizer::doSize() const
{
    return agtm::Size2d<float>(-1, -1);
}

void BoxSizer::doSize(agtm::Size2d<float> const& size)
{
    m_cachedSize = size;
    agtm::Size2d<float> minSize = doMinSize();

    float totalMajorSize = getSizeInMajorDirection(size);
    float totalMinorSize = getSizeInMinorDirection(size);
    float totalProp = 0.0f;
    float minMajorSize = getSizeInMajorDirection(minSize);
    //float minMinorSize = getSizeInMinorDirection(minSize);

    float remaining = totalMajorSize;

    std::vector<float> majorSizes(m_widgets.size(), getSizeInMajorDirection(Widget::DEFAULT_SIZE));

    if (totalMajorSize < minMajorSize)
    {
        // if there's not enought space to satisfy the minimum size
        // we should first allocate what space we can to fixed size
        // elements, then distribute the rest to the proportional
        // elements until there's nothing left.
    }
    else
    {
        WidgetList::iterator it = m_widgets.begin();
        WidgetList::iterator end = m_widgets.end();
        int n = 0;

        // Loop throuh the children and calculate the total proportions as well
        // as the initial values for fixed size widgets
        for (; it != end; ++it, ++n)
        {
            float majorSize = getSizeInMajorDirection(it->second->actualMinSize());
            if (it->first.flags.sizeMode() == SizeMode_RELATIVE)
            {
                totalProp += it->first.flags.size();
            }
            else
            {
                majorSizes[n] = majorSize;
                remaining -= majorSize;
            }
        }

        // TODO:
        // loop through the children until all conditions of proportions,
        // fixed, min and max sizes are satisfied
        // For now, just allocate the proportional amounts to the relative
        // size children, without regard for min/max size requirements
        for (it = m_widgets.begin(), n = 0; it != end; ++it, ++n)
        {
            if (it->first.flags.sizeMode() == SizeMode_RELATIVE)
            {
                majorSizes[n] = (remaining / totalProp) * it->first.flags.size();
            }
        }

        // Make the final pass through the children to set their new sizes
        for (it = m_widgets.begin(), n = 0; it != end; ++it, ++n)
        {
            it->second->size(getSize(majorSizes[n], totalMinorSize));
        }
    }
}

agtm::Size2d<float> BoxSizer::doMinSize() const
{
    //float width = -1;
    //float height = -1;
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
            totalProp += it->first.flags.size();
            float minSizeToProp = widgetMajorSize / it->first.flags.size();
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

    return getSize(majorSize, minorSize);
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

agtm::Size2d<float> BoxSizer::getSize(float sizeInMajorDirection, float sizeInMinorDirection) const
{
    return m_direction == Direction_VERTICAL ?
        agtm::Size2d<float>(sizeInMinorDirection, sizeInMajorDirection) :
        agtm::Size2d<float>(sizeInMajorDirection, sizeInMinorDirection);
}

} // namespace
