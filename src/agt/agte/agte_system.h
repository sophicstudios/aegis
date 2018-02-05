#ifndef INCLUDED_AEGIS_AGTE_SYSTEM_H
#define INCLUDED_AEGIS_AGTE_SYSTEM_H

#include <agte_engine.h>

namespace agte {

class System
{
public:
    System(int updatePriority = 0);

    virtual ~System();

    void preUpdate(agte::Engine::Context& context);

    void update(agte::Engine::SpacePtr space, agte::Engine::Context& context);

    void postUpdate(agte::Engine::Context& context);

    void updatePriority(int priority);

    int updatePriority() const;

protected:
    virtual void doPreUpdate(agte::Engine::Context& context) = 0;
    virtual void doUpdate(agte::Engine::SpacePtr space, agte::Engine::Context& context) = 0;
    virtual void doPostUpdate(agte::Engine::Context& context) = 0;

private:
    System();

    int m_priority;
};

} // namespace

#endif // INCLUDED
