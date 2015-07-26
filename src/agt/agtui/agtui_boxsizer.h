#ifndef INCLUDED_AGTUI_BOXSIZER_H
#define INCLUDED_AGTUI_BOXSIZER_H

#include <agtui_sizer.h>
#include <agtui_widget.h>
#include <memory>
#include <vector>

namespace agtui {

class BoxSizer : public agtui::Sizer
{
public:
    enum Direction
    {
        Direction_HORIZONTAL,
        Direction_VERTICAL
    };

    enum SizeMode
    {
        SizeMode_FIXED,
        SizeMode_RELATIVE
    };

    BoxSizer(BoxSizer::Direction direction);
    
    virtual ~BoxSizer();

    void add(std::shared_ptr<agtui::Widget> widget, size_t position, BoxSizer::SizeMode sizeMode, float size);

private:
    virtual agtm::Size2d<float> doSize() const;

    virtual void doSize(agtm::Size2d<float> const& size);

    virtual agtm::Size2d<float> doMinSize() const;

    virtual agtm::Size2d<float> doMaxSize() const;

    virtual agtm::Size2d<float> doBestSize() const;

    typedef std::vector<std::pair<BoxSizer::SizeMode, std::shared_ptr<agtui::Widget> > WidgetList;

    BoxSizer::Direction m_direction;
    WidgetList m_widgets;
};


} // namespace

#endif // INCLUDED
