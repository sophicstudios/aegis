#ifndef INCLUDED_AGTUI_SIZER_H
#define INCLUDED_AGTUI_SIZER_H

#include <agtui_widget.h>
#include <agtm_rect.h>
#include <memory>
#include <string>
#include <vector>

namespace agtui {

class Sizer
{
public:
    typedef std::shared_ptr<Widget> WidgetPtr;
    typedef std::vector<WidgetPtr> WidgetList;
    
    Sizer();
    
    virtual ~Sizer() = 0;
    
    virtual bool addWidget(std::string const& id, WidgetPtr child);
    
    virtual WidgetPtr remove(std::string const& id);

    virtual const WidgetPtr child(std::string const& id);

protected:
    
};

} // namespace

#endif // INCLUDED
