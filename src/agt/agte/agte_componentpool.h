#ifndef INCLUDED_AGTE_COMPONENTPOOL_H
#define INCLUDED_AGTE_COMPONENTPOOL_H

#include <agte_space.h>
#include <exception>
#include <memory>
#include <vector>

namespace agte {

class BaseComponentPool
{
public:
    static size_t typeCounter;

    virtual void destroyComponent(agte::Entity entity) = 0;
};

/**
 * @class ComponentPool
 *
 * Handles the efficient containment of a specific component type for a set
 * of entities.
 */
template<typename T>
class ComponentPool : public BaseComponentPool
{
public:
    static size_t type();

    /**
     * Constructor. Creates a ComponentPool to hold components with a default
     * initial batch size of 500 components.
     */
    ComponentPool(std::shared_ptr<agte::Space> space);

    /**
     * Constructor. Creates a ComponentPool to hold components. The batchSize
     * parameter can be used to modify how many components are initially
     * pre-allocated.
     *
     * @param batchSize Size of each batch of components
     */
    ComponentPool(std::shared_ptr<agte::Space> space, size_t batchSize);

    /**
     * Destructor.
     */
    ~ComponentPool();

    /**
     * 
     */
    T& createComponent(agte::Entity entity);

    /**
     *
     */
    T& createComponent(agte::Entity entity, T const& initialState);

    /**
     *
     */
    virtual void destroyComponent(agte::Entity entity);

    /**
     *
     */
     T& componentForEntity(Entity entity);

private:
    static const size_t DEFAULT_BATCH_SIZE = 500;

    typedef std::vector<T> ComponentList;
    typedef std::vector<size_t> EntityComponentMap;
    typedef std::vector<size_t> ComponentEntityMap;

    std::shared_ptr<agte::Space> m_space;
    ComponentList m_components;
    size_t m_batchSize;
    size_t m_count;
    ComponentEntityMap m_componentEntityMap;
    EntityComponentMap m_entityComponentMap;
};

template<typename T>
size_t ComponentPool<T>::type()
{
    static size_t typeCount = typeCounter++;
    return typeCount;
}

template<typename T>
ComponentPool<T>::ComponentPool(std::shared_ptr<agte::Space> space)
: m_space(space),
  m_count(0),
  m_batchSize(DEFAULT_BATCH_SIZE),
  m_components(DEFAULT_BATCH_SIZE),
  m_componentEntityMap(DEFAULT_BATCH_SIZE, std::numeric_limits<size_t>::max()),
  m_entityComponentMap(DEFAULT_BATCH_SIZE, std::numeric_limits<size_t>::max())
{}

template<typename T>
ComponentPool<T>::ComponentPool(std::shared_ptr<agte::Space> space, size_t batchSize)
: m_space(space),
  m_count(0),
  m_batchSize(batchSize),
  m_components(batchSize),
  m_componentEntityMap(batchSize, std::numeric_limits<size_t>::max()),
  m_entityComponentMap(batchSize, std::numeric_limits<size_t>::max())
{}

template<typename T>
ComponentPool<T>::~ComponentPool()
{}

template<typename T>
T& ComponentPool<T>::createComponent(agte::Entity entity)
{
    // if component for entity already exists, throw exception
    if (m_entityComponentMap[entity.id()] != std::numeric_limits<size_t>::max())
    {
        throw std::exception();
    }

    T& component = m_components[m_count];
    m_entityComponentMap[entity.id()] = m_count;
    m_componentEntityMap[m_count] = entity.id();

    ++m_count;

    m_space->addComponentToEntity(entity, type());

    return component;
}

template<typename T>
T& ComponentPool<T>::createComponent(agte::Entity entity, T const& initialState)
{
    T& component = createComponent(entity);

    component = initialState;

    return component;
}

template<typename T>
void ComponentPool<T>::destroyComponent(agte::Entity entity)
{
    size_t componentIndex = m_entityComponentMap[entity.id()];
    if (componentIndex == std::numeric_limits<size_t>::max())
    {
        throw std::exception();
    }

    // swap the destroyed component with the last active component
    std::swap(m_components[componentIndex], m_components[m_count]);
    size_t otherEntityId = m_componentEntityMap[componentIndex] = m_componentEntityMap[m_count];
    m_entityComponentMap[otherEntityId] = componentIndex;

    // remove the entity/component mappings
    m_entityComponentMap[entity.id()] = std::numeric_limits<size_t>::max();
    m_componentEntityMap[m_count] = std::numeric_limits<size_t>::max();

    --m_count;
}

template<typename T>
T& ComponentPool<T>::componentForEntity(agte::Entity entity)
{
    size_t componentIndex = m_entityComponentMap[entity.id()];
    if (componentIndex == std::numeric_limits<size_t>::max())
    {
        throw std::exception();
    }

    return m_components[componentIndex];
}

} // namespace

#endif // INCLUDED
