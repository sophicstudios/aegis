#ifndef INCLUDED_AGTA_COMPONENTMANAGER_H
#define INCLUDED_AGTA_COMPONENTMANAGER_H

#include <vector>
#include <list>

namespace agta {

/**
 * @class ComponentManager
 *
 * Handles the efficient containment of a specific component type for a set
 * of entities.
 */
template<typename T>
class ComponentManager
{
public:
    typedef std::vector<size_t> EntityList;

    /**
     * Creates a ComponentManager to hold components. An initial
     * chunk of memory to hold 'batchSize' components will be created during
     * construction.
     *
     * @param batchSize Size of each batch of components
     */
    ComponentManager(size_t batchSize);

    /**
     * Destructor
     */
    ~ComponentManager();

    /**
     * Adds a component for the specified 'entityId' to the ComponentManager and
     * returns a reference to the component.
     *
     * @param entityId The id of the component's entity.
     * @result A reference to the added component.
     */
    T& addComponentForEntity(size_t entityId);

    /**
     * Adds a component for the specified entityId to the ComponentManager,
     * sets the initial state to the value of 'component' and returns a
     * reference to the component.
     *
     * @param entityId The id of the component's entity.
     * @param component The initial state of the created component.
     * @result A reference to the added component.
     */
    T& addComponentForEntity(size_t entityId, T const& component);

    /**
     * @param entityId The id of the component's entity.
     */
    void removeComponentForEntity(size_t entityId);

    /**
     * @param entityId The id of the component's entity.
     */
    T& componentForEntity(size_t entityId);

    /**
     * @result A list of entities with components in this ComponentManager.
     */
    EntityList const& entityList() const;

private:
    struct ComponentInfo
    {
        ComponentInfo() : active(false) {}

        T component;
        bool active;
    };

    ComponentInfo& activateComponent(size_t entityId);
    void precreateComponents(size_t maxEntityId);

    typedef std::vector<ComponentInfo> ComponentList;
    typedef std::vector<ComponentList> ComponentListList;
    ComponentListList m_components;
    size_t m_batchSize;

    EntityList m_entities;
    std::vector<size_t> m_entityComponentMap;
    std::list<size_t> m_freeComponents;
};

template<typename T>
ComponentManager<T>::ComponentManager(size_t batchSize)
: m_batchSize(batchSize)
{
    // create initial batch of components
    ComponentList componentList(batchSize);
    m_components.push_back(componentList);
}

template<typename T>
ComponentManager<T>::~ComponentManager()
{}

template<typename T>
T& ComponentManager<T>::addComponentForEntity(size_t entityId)
{
    if (!m_freeComponents.empty()) {
    }

    return activateComponent(entityId).component;
}

template<typename T>
T& ComponentManager<T>::addComponentForEntity(size_t entityId, T const& component)
{
    ComponentInfo& info = activateComponent(entityId);
    info.component = component;
    return info.component;
}


template<typename T>
void ComponentManager<T>::removeComponentForEntity(size_t entityId)
{
    assert(entityId < m_components.size() * m_batchSize);

    m_components[static_cast<size_t>(entityId / m_batchSize)][entityId % m_batchSize].active = false;

    EntityList::iterator it = m_entities.begin(), end = m_entities.end();
    while (it != end) {
        if (*it == entityId) {
            m_entities.erase(it);
            break;
        }

        ++it;
    }

}

template<typename T>
T& ComponentManager<T>::componentForEntity(size_t entityId)
{
    return m_components[static_cast<size_t>(entityId / m_batchSize)][entityId % m_batchSize].component;
}

template<typename T>
typename ComponentManager<T>::ComponentInfo& ComponentManager<T>::activateComponent(size_t entityId)
{
    precreateComponents(entityId);

    ComponentList& componentList = m_components[static_cast<size_t>(entityId / m_batchSize)];

    ComponentInfo& componentInfo = componentList[entityId % m_batchSize];
    componentInfo.active = true;

    m_entities.push_back(entityId);

    return componentInfo;
}

template<typename T>
void ComponentManager<T>::precreateComponents(size_t maxEntityId)
{
    while (m_components.size() * m_batchSize < maxEntityId) {
        ComponentList componentList(m_batchSize);
        m_components.push_back(componentList);
    }
}

} // namespace

#endif // INCLUDED
