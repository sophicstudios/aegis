#ifndef INCLUDED_AGTUI_DISPLAYTIMER_H
#define INCLUDED_AGTUI_DISPLAYTIMER_H

#include <functional>

namespace agtui {

class DisplayTimer
{
public:
    typedef std::function<void ()> Callback;
    
    DisplayTimer();
    
    virtual ~DisplayTimer() = 0;

    virtual void registerCallback(Callback const& callback) = 0;

    virtual void start() = 0;
    
    virtual void stop() = 0;
};

} // namespace

#endif // INCLUDED
