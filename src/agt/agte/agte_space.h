#ifndef INCLUDED_AEGIS_AGTE_SPACE_H
#define INCLUDED_AEGIS_AGTE_SPACE_H

#include <agte_entity.h>
#include <agte_camera.h>
#include <agte_pool.h>
#include <agtc_componenthandle.h>
#include <afth_uuid.h>
#include <cstdint>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

namespace agte {

/**
 * @class Space
 *
 * Represents a containment of entities and their associated components
 */
class Space
{
private:
    struct EntityInfo
    {
        Entity entity;
        bool active;
        Entity::ComponentSet components;
    };

    typedef std::vector<EntityInfo> EntityInfoList;

public:
    typedef std::shared_ptr<Space> Ptr;

    /**
     * @class EntityView
     *
     * A view onto a set of entities. Used to iterate over entities
     * that meet certain criterion, like having a set of components
     */
    class EntityView
    {
    public:
        /**
         * @class Iterator
         */
        class Iterator
        {
        public:
            Iterator();

            Iterator(Space::EntityInfoList* list,
                     Entity::ComponentSet const* componentSet,
                     Space::EntityInfoList::iterator iter);

            Iterator(Iterator const& rhs);

            ~Iterator();

            Iterator& operator=(Iterator const& rhs);
            
            /**
             * Prefix operator++
             * Moves to the next Entity in the view and returns
             */
            Iterator& operator++();

            Iterator operator++(int);

            Entity& operator*();

            bool operator==(Iterator const& rhs) const;

            bool operator!=(Iterator const& rhs) const;

        private:
            Space::EntityInfoList* _entities;
            Entity::ComponentSet const* _componentSet;
            Space::EntityInfoList::iterator _iter;
        };

        EntityView(
            Space::EntityInfoList& entities,
            Entity::ComponentSet const& componentSet);

        ~EntityView();

        Iterator begin() const;

        Iterator end() const;

    private:
        EntityInfoList& _entities;
        Entity::ComponentSet const& _componentSet;
    };

    /**
     * Constructor.
     */
    Space();

    /**
     * Destructor.
     */
    ~Space();

    /**
     * Returns the UUID for this Space.
     * 
     * @return The UUID
     */
    afth::UUID const& id() const;

    /**
     * Creates a new Entity.
     * 
     * @return The Entity
     */    
    Entity createEntity();

    /**
     * Destroys an Entity.
     *
     * In addition to destroying the Entity, this method
     * will also destory all associated components.
     * 
     * @param entity The Entity to destroy.
     */
    void destroyEntity(Entity entity);

    /**
     * Associates a component with an Entity.
     * 
     * @param entity The Entity
     * @param component The component to associate.
     */
    template<typename T>
    void addComponentToEntity(Entity entity, T& component);

    /**
     * Disassociates a component from an Entity.
     * 
     * @param entity The Entity
     */
    template<typename T>
    void removeComponentFromEntity(Entity entity, size_t componentType);
    
    /**
     * 
     */
    EntityView entitiesForComponents(Entity::ComponentSet const& components);

private:
    typedef std::vector<size_t> FreeEntityIdList;
    typedef std::vector<Entity::ComponentSet> ComponentSetList;
    typedef std::shared_ptr<agte::BasePool> PoolPtr;
    typedef std::vector<PoolPtr> ComponentPools;

    template<typename T>
    std::shared_ptr<agte::Pool<T>> _getComponentPool(size_t i);

    afth::UUID _id;
    FreeEntityIdList _freeEntityIds;
    EntityInfoList _entities;
    ComponentPools _componentPools;
};

template<typename T>
void Space::addComponentToEntity(Entity entity, T& component)
{
    EntityInfo& entityInfo = _entities[entity.id()];

    size_t componentType = agtc::ComponentHandle<T>::typeId();
    entityInfo.components.set(componentType);

    std::shared_ptr<agte::Pool<T> > pool = _getComponentPool<T>(componentType); 
}

template<typename T>
void Space::removeComponentFromEntity(Entity entity, size_t componentType)
{
    EntityInfo& entityInfo = _entities[entity.id()];
    entityInfo.components.reset(componentType);
}

template<typename T>
std::shared_ptr<agte::Pool<T>> Space::_getComponentPool(size_t i)
{
    if (_componentPools.size() <= i) {
        _componentPools.resize(i + 1);
        PoolPtr pool = std::make_shared<agte::Pool<T> >();
        _componentPools[i] = pool;
    }

    return static_cast<std::shared_ptr<agte::Pool<T> > >(_componentPools[i]);
}

} // namespace

#endif // INCLUDED
