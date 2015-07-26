#ifndef INCLUDED_AGTA_EVENTSYSTEM_H
#define INCLUDED_AGTA_EVENTSYSTEM_H

#include <agta_engine.h>
#include <agta_system.h>
#include <agtm_rect.h>
#include <agtui_window.h>
#include <actp_mutex.h>
#include <afth_uuid.h>
#include <deque>
#include <functional>
#include <memory>

namespace agta {

class EventSystem : public agta::System
{
public:
    typedef std::function<void (afth::UUID const&)> Callback;

    EventSystem();

    virtual ~EventSystem();

    void queueEvent(afth::UUID const& id, Callback callback);

protected:
    virtual void doPreUpdate(agta::Engine::Context& context);
    virtual void doUpdate(agta::Engine::SpacePtr space, agta::Engine::Context& context);
    virtual void doPostUpdate(agta::Engine::Context& context);

private:
    typedef std::deque<std::pair<afth::UUID, Callback> > EventList;

    void swapEventLists();
    
    actp::Mutex m_mutex;
    EventList* m_nextEvents;
    EventList* m_currentEvents;
};

} // namespace

#endif // INCLUDED
