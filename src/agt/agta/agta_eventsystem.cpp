#include <agta_eventsystem.h>
#include <actp_scopedlock.h>
#include <functional>

namespace agta {

namespace {

} // namespace

EventSystem::EventSystem()
: System(0)
{
}

EventSystem::~EventSystem()
{}

void EventSystem::queueEvent(afth::UUID const& id, EventSystem::Callback callback)
{
    actp::ScopedLock<actp::Mutex> lock(m_mutex);
    m_nextEvents->push_back(std::make_pair(id, callback));
}

void EventSystem::doPreUpdate(agta::Engine::Context& context)
{}

void EventSystem::doUpdate(agta::Engine::SpacePtr space, agta::Engine::Context& context)
{
    swapEventLists();

    EventList::iterator it = m_currentEvents->begin();
    EventList::iterator end = m_currentEvents->end();
    for (; it != end; ++it) {
        Callback& callback = it->second;
        callback(it->first);
    }
}

void EventSystem::doPostUpdate(agta::Engine::Context& context)
{}

void EventSystem::swapEventLists()
{
    actp::ScopedLock<actp::Mutex> lock(m_mutex);
    std::swap(m_currentEvents, m_nextEvents);
}

} // namespace
