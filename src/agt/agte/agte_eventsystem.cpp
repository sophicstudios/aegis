#include <agte_eventsystem.h>
#include <aftthr_scopedlock.h>
#include <functional>

namespace agte {

namespace {

} // namespace

EventSystem::EventSystem()
{}

EventSystem::EventSystem(int updatePriority)
: System(updatePriority)
{}

EventSystem::~EventSystem()
{}

void EventSystem::queueEvent(afth::UUID const& id, EventSystem::Callback callback)
{
    aftthr::ScopedLock<aftthr::Mutex> lock(m_mutex);
    m_nextEvents->push_back(std::make_pair(id, callback));
}

void EventSystem::doPreUpdate(agte::Engine::Context& context)
{}

void EventSystem::doUpdate(agte::Engine::SpacePtr space, agte::Engine::Context& context)
{
    swapEventLists();

    EventList::iterator it = m_currentEvents->begin();
    EventList::iterator end = m_currentEvents->end();
    for (; it != end; ++it) {
        Callback& callback = it->second;
        callback(it->first);
    }
}

void EventSystem::doPostUpdate(agte::Engine::Context& context)
{}

void EventSystem::swapEventLists()
{
    aftthr::ScopedLock<aftthr::Mutex> lock(m_mutex);
    std::swap(m_currentEvents, m_nextEvents);
}

} // namespace
