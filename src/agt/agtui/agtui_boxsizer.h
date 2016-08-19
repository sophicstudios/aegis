#ifndef INCLUDED_AGTUI_BOXSIZER_H
#define INCLUDED_AGTUI_BOXSIZER_H

#include <agtui_sizer.h>
#include <agtui_widget.h>
#include <deque>
#include <memory>
#include <set>
#include <vector>

namespace agtui {

class BoxSizer : public agtui::Sizer
{
public:
    /**
     * Used to indicate the primary direction of the sizer
     */
    enum Direction
    {
        /** Allocated size horizontally */
        Direction_HORIZONTAL,

        /** Allocate size vertically */
        Direction_VERTICAL
    };

    /**
     * Used to indicate how the size flag is interpreted
     */
    enum SizeMode
    {
        /** Size is a fixed value */
        SizeMode_FIXED,

        /** Size is calculated relative to other items in the sizer */
        SizeMode_RELATIVE
    };

    /**
     * @brief Status codes for operations on BoxSizer
     */
    enum Status
    {
        /** No errors */
        Status_OK = 0,

        /** The specified widget already exists in the sizer */
        Status_ERROR_WIDGET_ALREADY_EXISTS = -1,

        /** The specified widget does not exist in the sizer */
        Status_ERROR_WIDGET_DOES_NOT_EXIST = -2
    };

    /**
     * @class BoxSizer::Flags
     *
     * This class contains flags used by the BoxSizer to perform its logic. This
     * includes such things as the size of the widget, the sizing mode, whether
     * to expand the widget to fill available space
     */
    class Flags
    {
    public:
        /**
         * Constructor
         *
         * Allocates a default Flags object
         */
        Flags();

        /**
         * @brief Destructor
         */
        ~Flags();

        /**
         * @brief sizeMode setter.
         *
         * @param sizeMode The BoxSizer::SizeMode
         * @return A reference to this
         *
         * Sets the size mode, returning a reference to this
         */
        Flags& sizeMode(BoxSizer::SizeMode sizeMode);

        /**
         * @brief sizeMode getter.
         *
         * @return
         */
        BoxSizer::SizeMode sizeMode() const;

        Flags& size(float size);

        float size() const;

    private:
        BoxSizer::SizeMode m_sizeMode;
        float m_size;
    };

    /**
     * @brief Constructs a BoxSizer.
     *
     * A BoxSizer lays out its children in either a horizontal or vertical
     * manner. By combining multiple sizers together in a hierarchy, many
     * types of widget layouts can be achieved.
     *
     * @param direction The main sizing direction of the BoxSizer, either
    *                   Direction_HORIZONTAL or Direction_VERTICAL.
     */
    BoxSizer(BoxSizer::Direction direction);

    /**
     * Destructor
     */
    virtual ~BoxSizer();

    /**
     * Adds a widget to the front of the list of contained items.
     *
     * @param widget A pointer to the widget to be added to the list.
     * @param flags How to size the added widget.
     */
    Status push_front(std::shared_ptr<agtui::Widget> widget, BoxSizer::Flags flags);

    /**
     * Adds a widget to the end of the list of contained items.
     *
     * @param widget A pointer to the widget to be added to the list.
     * @param flags How to size the added widget.
     */
    Status push_back(std::shared_ptr<agtui::Widget> widget, BoxSizer::Flags flags);

    /**
     * Adds a widget to the list of sized items at the specified position. The
     * widget is inserted before any item already at the position.
     *
     * @param
     */
    Status insert(std::shared_ptr<agtui::Widget> widget, size_t position, BoxSizer::Flags flags);

private:
    struct Info
    {
        Flags flags;
        float size;
    };

    virtual agtm::Size2d<float> doSize() const;

    virtual void doSize(agtm::Size2d<float> const& size);

    virtual agtm::Size2d<float> doMinSize() const;

    virtual agtm::Size2d<float> doMaxSize() const;

    float getSizeInMajorDirection(agtm::Size2d<float> const& size) const;

    float getSizeInMinorDirection(agtm::Size2d<float> const& size) const;
    
    typedef std::deque<std::pair<Info, std::shared_ptr<agtui::Widget> > > WidgetList;
    typedef std::set<afth::UUID> WidgetMap;

    BoxSizer::Direction m_direction;
    WidgetList m_widgets;
    WidgetMap m_widgetMap;
    float m_totalProportion;
};


} // namespace

#endif // INCLUDED
