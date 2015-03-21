#ifndef INCLUDED_AGTA_SYSTEM_H
#define INCLUDED_AGTA_SYSTEM_H

namespace agta {

class Engine;
class Engine::Context;

class System
{
public:
    System(int updatePriority);

    virtual ~System();

    void preUpdate(Engine::Context& context);

    void update(Engine::Context& context);

    void postUpdate(Engine::Context& context);

    void updatePriority(int priority);

    int updatePriority() const;

protected:
    virtual void doPreUpdate(Engine::Context& context) = 0;
    virtual void doUpdate(Engine::Context& context) = 0;
    virtual void doPostUpdate(Engine::Context& context) = 0;

private:
    System();

    int m_priority;
};

} // namespace

#endif // INCLUDED
