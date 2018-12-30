#ifndef INCLUDED_AEGIS_AGTE_SPACE_H
#define INCLUDED_AEGIS_AGTE_SPACE_H

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
public:
    class Entity
    {
        friend class Space;

        friend bool operator==(Entity const& lhs, Entity const& rhs);
        friend bool operator<(Entity const& lhs, Entity const& rhs);
        friend bool operator>(Entity const& lhs, Entity const& rhs);
        friend bool operator<=(Entity const& lhs, Entity const& rhs);
        friend bool operator>=(Entity const& lhs, Entity const& rhs);

    public:
        static const int MAX_COMPONENTS = sizeof(size_t);
        typedef std::bitset<MAX_COMPONENTS> ComponentSet;

        struct Hash
        {
            size_t operator()(Entity const& entity);
        };

        ~Entity();

        size_t id() const;

        std::string const& name() const;

        void name(std::string const& name);

        template<typename T>
        void assign(T const& component);

        template<typename T>
        void remove(T const& component);

        template<typename T>
        T& get();
        
    protected:
        Entity(Space* space, size_t id);

    private:
        Entity();

        Space* _space;
        size_t _id;
        std::string _name;
    };

private:
    struct EntityInfo
    {
        Entity entity;
        bool active;
        Entity::ComponentSet components;
    };

    typedef std::vector<EntityInfo> EntityInfoList;

public:
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

            Entity* operator->();

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
    void addComponentToEntity(Entity const& entity, T const& component);

    /**
     * Disassociates a component from an Entity.
     * 
     * @param entity The Entity
     */
    template<typename T>
    void removeComponentFromEntity(Entity const& entity, T const& component);
    
    template<typename T>
    T& getComponentForEntity(Entity const& entity);

    /**
     * 
     */
    EntityView entitiesForComponents(Entity::ComponentSet const& components);

private:
    struct PoolInfo
    {
        PoolInfo()
        : active(false)
        {}

        ~PoolInfo()
        {}

        bool active;
        std::shared_ptr<agte::BasePool> pool;
    };

    typedef std::vector<size_t> FreeEntityIdList;
    typedef std::vector<Entity::ComponentSet> ComponentSetList;
    typedef std::vector<PoolInfo> ComponentPools;

    template<typename T>
    std::shared_ptr<agte::Pool<T>> _getComponentPool(size_t i);

    afth::UUID _id;
    FreeEntityIdList _freeEntityIds;
    EntityInfoList _entities;
    ComponentPools _componentPools;
};

template<typename T>
void Space::Entity::assign(T const& component)
{
    _space->addComponentToEntity(*this, component);
}

template<typename T>
void Space::Entity::remove(T const& component)
{
    _space->removeComponentFromEntity(*this, component);
}

template<typename T>
T& Space::Entity::get()
{
    return _space->getComponentForEntity<T>(*this);
}

bool operator==(Space::Entity const& lhs, Space::Entity const& rhs);

bool operator<(Space::Entity const& lhs, Space::Entity const& rhs);

bool operator>(Space::Entity const& lhs, Space::Entity const& rhs);

bool operator<=(Space::Entity const& lhs, Space::Entity const& rhs);

bool operator>=(Space::Entity const& lhs, Space::Entity const& rhs);

template<typename T>
void Space::addComponentToEntity(Space::Entity const& entity, T const& component)
{
    size_t entityId = entity.id();
    EntityInfo& entityInfo = _entities[entityId];

    size_t componentType = agtc::ComponentHandle<T>::typeId();

    // If component type is already associated with this Entity, that's an error
    if (entityInfo.components.test(componentType)) {
        throw std::exception();
    }

    std::shared_ptr<agte::Pool<T> > pool = _getComponentPool<T>(componentType);
    pool->resize(entityId + 1);

    T* c = static_cast<T*>(pool->at(entityId));
    *c = component;

    entityInfo.components.set(componentType);
}

template<typename T>
void Space::removeComponentFromEntity(Space::Entity const& entity, T const& component)
{
    size_t entityId = entity.id();
    EntityInfo& entityInfo = _entities[entityId];

    size_t componentType = agtc::ComponentHandle<T>::typeId();

    if (!entityInfo.components.test(componentType)) {
        throw std::exception();
    }

    std::shared_ptr<agte::Pool<T> > pool = _getComponentPool<T>(componentType);
    pool->destroy(entityId);

    entityInfo.components.reset(componentType);
}

template<typename T>
T& Space::getComponentForEntity(Space::Entity const& entity)
{
    size_t entityId = entity.id();
    EntityInfo& entityInfo = _entities[entityId];

    size_t componentType = agtc::ComponentHandle<T>::typeId();

    if (!entityInfo.components.test(componentType)) {
        throw std::exception();
    }

    std::shared_ptr<agte::Pool<T> > pool = _getComponentPool<T>(componentType);

    T* c = static_cast<T*>(pool->at(entityId));
    return *c;
}

template<typename T>
std::shared_ptr<agte::Pool<T> > Space::_getComponentPool(size_t i)
{
    if (_componentPools.size() <= i) {
        _componentPools.resize(i + 1);
    }

    PoolInfo& poolInfo = _componentPools[i];
    if (!poolInfo.active) {
        poolInfo.pool = std::make_shared<agte::Pool<T>>();
        poolInfo.active = true;
    }

    return std::static_pointer_cast<agte::Pool<T> >(poolInfo.pool);
}

} // namespace

#endif // INCLUDED
