#ifndef INCLUDED_AGTA_ENGINE_H
#define INCLUDED_AGTA_ENGINE_H

#include <memory>
#include <vector>

namespace agta {

class System;
class Platform;

class Engine
{
public:
    typedef std::shared_ptr<agta::System> SystemPtr;
    typedef std::shared_ptr<agta::Platform> PlatformPtr;

    class Context
    {
    public:
        Context(PlatformPtr platform);

        ~Context();

        void resetShouldUpdate();
        
        void flagUpdate();

        bool shouldUpdate() const;

        PlatformPtr platform() const;

    private:
        bool m_shouldUpdate;
        PlatformPtr m_platform;
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
     * Puts the Engine into a running state, where it will continuously
     * update its Systems. The Engine can be stopped by calling the stop()
     * method. If the Engine is already in a running state, this is a no-op.
     */
    void run();

    /**
     * Takes the Engine out of a running state. If the Engine is already not
     * in a running state, this is a no-op.
     */
    void stop();

    /**
     * Request a single update of the Engine's systems. This is to allow for
     * more control for the application about when to update the Engine. This can
     * be useful in event driven simulations that don't need to constantly
     * be running, which can have greater energy savings. If the Engine is
     * already in a running state, this is a no-op.
     */
    void step();

private:
    typedef std::vector<SystemPtr> SystemList;

    void onDisplayTimer();

    Context m_context;
    SystemList m_systems;
    PlatformPtr m_platform;
    bool m_running;
};

} // namespace

#endif // INCLUDED
