#ifndef INCLUDED_AEGIS_AGTE_EVENTSYSTEM_H
#define INCLUDED_AEGIS_AGTE_EVENTSYSTEM_H

#include <agte_engine.h>
#include <agte_system.h>
#include <agtm_rect.h>
#include <aftthr_mutex.h>
#include <afth_uuid.h>
#include <deque>
#include <functional>
#include <memory>

namespace agte {

class EventSystem : public agte::System
{
public:
    typedef std::function<void (afth::UUID const&)> Callback;

    EventSystem();

    EventSystem(int updatePriority);

    virtual ~EventSystem();

    void queueEvent(afth::UUID const& id, Callback callback);

protected:
    virtual void doPreUpdate(agte::Engine::Context& context);
    virtual void doUpdate(agte::Engine::SpacePtr space, agte::Engine::Context& context);
    virtual void doPostUpdate(agte::Engine::Context& context);

private:
    typedef std::deque<std::pair<afth::UUID, Callback> > EventList;

    void swapEventLists();
    
    aftthr::Mutex m_mutex;
    EventList* m_nextEvents;
    EventList* m_currentEvents;
};

} // namespace

#endif // INCLUDED
