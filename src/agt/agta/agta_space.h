#ifndef INCLUDED_AGTA_SPACE_H
#define INCLUDED_AGTA_SPACE_H

#include <agta_entity.h>
#include <agtg_camera.h>
#include <afth_uuid.h>
#include <cstdint>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

namespace agta {

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
                     size_t index);

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
            Space::EntityInfoList* m_entities;
            Entity::ComponentSet const* m_componentSet;
            size_t m_index;
        };

        EntityView(
            Space::EntityInfoList& entities,
            Entity::ComponentSet const& componentSet);

        ~EntityView();

        Iterator begin() const;

        Iterator end() const;

    private:
        EntityInfoList& m_entities;
        Entity::ComponentSet const& m_componentSet;
    };

    Space();

    ~Space();

    afth::UUID const& id() const;
    
    Entity createEntity();

    void destroyEntity(Entity entity);

    void addComponentToEntity(Entity entity, size_t componentType);

    void removeComponentFromEntity(Entity entity, size_t componentType);
    
    EntityView getEntitiesForComponents(Entity::ComponentSet const& components);

private:
    typedef std::vector<size_t> FreeEntityIdList;
    typedef std::vector<Entity::ComponentSet> ComponentSetList;

    afth::UUID m_id;
    FreeEntityIdList m_freeEntityIds;
    EntityInfoList m_entities;
};

} // namespace

#endif // INCLUDED
