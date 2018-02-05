#ifndef INCLUDED_AEGIS_AGTE_ENGINE_H
#define INCLUDED_AEGIS_AGTE_ENGINE_H

#include <agte_space.h>
#include <aftthr_condition.h>
#include <aftthr_mutex.h>
#include <aftthr_thread.h>
#include <atomic>
#include <memory>
#include <vector>

namespace agte {

class System;
class Platform;

class Engine
{
public:
    typedef std::shared_ptr<agte::System> SystemPtr;
    typedef std::shared_ptr<agte::Platform> PlatformPtr;
    typedef std::shared_ptr<agte::Space> SpacePtr;
    typedef std::vector<SpacePtr> SpaceList;

    class Context
    {
    public:
        Context(PlatformPtr platform, aftthr::Mutex& mutex, aftthr::Condition& condition);

        ~Context();

        void resetShouldUpdate();
        
        void flagUpdate();

        bool shouldUpdate() const;

        PlatformPtr platform() const;

    private:
        std::atomic<bool> m_shouldUpdate;
        PlatformPtr m_platform;
        aftthr::Mutex& m_mutex;
        aftthr::Condition& m_condition;
    };

    /**
     * Constructs an Engine with the specified Platform
     *
     * @param platform A pointer to a Platform that provides platform specific
     *                 functionality used by the Engine
     */
    Engine(PlatformPtr platform);

    /**
     * Destructor. If the Engine is in the running state, it will be
     * stopped during the Destructor to ensure proper cleanup
     */
    ~Engine();

    /**
     * Register a system with the Engine. The engine will call updatePriority()
     * on the System object to determine where to place the System in the
     * update queue. Systems with the same updatePriority() will be placed
     * in the order they are registered with the Engine
     * 
     * @param system A pointer to a System to be added to the queue
     */
    void registerSystem(SystemPtr system);

    /**
     * 
     */
    void addSpace(std::string const& id, SpacePtr space);

    /**
     *
     */
    void removeSpace(std::string const& id);

    /**
     * Request a single update of the Engine's systems. This is to allow for
     * more control for the application about when to update the Engine. This can
     * be useful in event driven simulations that don't need to constantly
     * be running, which can have greater energy savings. If the Engine is
     * already in a running state, this is a no-op.
     */
    void update();

private:
    void threadFunc();
    
    typedef std::vector<SystemPtr> SystemList;
    typedef std::map<std::string, SpacePtr> SpaceMap;

    std::atomic<bool> m_running;
    std::shared_ptr<aftthr::Thread> m_thread;
    aftthr::Condition m_condition;
    aftthr::Mutex m_mutex;

    Context m_context;
    PlatformPtr m_platform;

    SpaceList m_spaces;
    SpaceMap m_spaceMap;
    SystemList m_systems;
};

} // namespace

#endif // INCLUDED
