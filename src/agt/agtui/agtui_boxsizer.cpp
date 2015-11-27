#include <agtui_boxsizer.h>

namespace agtui {

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

    m_widgets.insert(i, info);

    return Status_OK;
}

agtm::Size2d<float> BoxSizer::doSize() const
{
}

void BoxSizer::doSize(agtm::Size2d<float> const& size)
{
}

agtm::Size2d<float> BoxSizer::doMinSize() const
{
    float width = -1;
    float height = -1;

    WidgetList::iterator it = m_widgets.begin();
    WidgetList::iterator end = m_widget.end();

    for (; it != end; ++it) {
        
    }
}

agtm::Size2d<float> BoxSizer::doMaxSize() const
{
}

agtm::Size2d<float> BoxSizer::doBestSize() const
{
}

} // namespace
