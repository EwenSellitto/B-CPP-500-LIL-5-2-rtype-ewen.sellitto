
/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** World.hpp
*/

#pragma once

#include "Entity.hpp"
#include "Utilities.hpp"
#include <memory>
#include <unordered_map>

namespace ECS {

/**
 * @class World
 * @brief Represents the world in an Entity-Component-System (ECS) architecture, managing entities and global entities.
 */
class World
{
    public:
        /**
         * @brief Construct a new World object.
         */
        World();

        /**
         * @brief Destroy the World object.
         * @note This will also destroy all entities and global entities within the world.
         */
        ~World();

        /**
         * @brief Add an entity to the world.
         *
         * @param entity A unique pointer to the Entity to be added. Ownership of the entity is transferred to the
         * World.
         * @return id_t The unique identifier for the added entity.
         * @note The World class takes ownership of the Entity, ensuring proper management and cleanup.
         */
        id_t addEntity(std::unique_ptr<Entity> entity)
        {
            id_t id = Utils::getNewId<Entity>();
            _entities.emplace(id, std::move(entity));
            return id;
        }

        /**
         * @brief Remove an entity from the world.
         *
         * @param id The unique identifier of the entity to be removed.
         * @note The entity will be properly destroyed when removed.
         */
        void removeEntity(id_t id) { _entities.erase(id); }

        /**
         * @brief Get an immutable reference to an entity.
         *
         * @param id The unique identifier of the entity to get.
         * @return cosnt Entity& An immutable reference to the entity.
         */
        const Entity &getEntity(id_t id) { return *_entities.at(id); }

        /**
         * @brief Get a mutable reference to an entity.
         *
         * @param id The unique identifier of the entity to get.
         * @return Entity& A mutable reference to the entity.
         * @warning This function is meant to be used by the systems only.
         */
        Entity &getMutEntity(id_t id) { return *_entities.at(id); }

        /**
         * @brief Add a global entity to the world.
         *
         * @param entity A unique pointer to the GlobalEntity to be added. Ownership of the global entity is transferred
         * to the World.
         * @return id_t The unique identifier for the added global entity.
         */
        id_t addGlobalEntity(std::unique_ptr<GlobalEntity> entity)
        {
            id_t id = Utils::getNewId<GlobalEntity>();
            _global_entities.emplace(id, std::move(entity));
            return id;
        }

        /**
         * @brief Remove a global entity from the world.
         *
         * @param id The unique identifier of the global entity to be removed.
         * @note The global entity will be properly destroyed when removed from all the worlds.
         */
        void removeGlobalEntity(id_t id) { _global_entities.erase(id); }

        /**
         * @brief Get an immutable reference to a global entity.
         *
         * @param id The unique identifier of the global entity to get.
         * @return cosnt GlobalEntity& An immutable reference to the global entity.
         */
        const GlobalEntity &getGlobalEntity(id_t id) { return *_global_entities.at(id); }

        /**
         * @brief Get a mutable reference to a global entity.
         *
         * @param id The unique identifier of the global entity to get.
         * @return GlobalEntity& A mutable reference to the global entity.
         */
        GlobalEntity &getMutGlobalEntity(id_t id) { return *_global_entities.at(id); }

    private:
        std::unordered_map<id_t, std::unique_ptr<Entity>> _entities; ///< Map of entities, indexed by their unique IDs.
        std::unordered_map<id_t, std::unique_ptr<GlobalEntity>>
            _global_entities; ///< Map of global entities, indexed by their unique IDs.
};
} // namespace ECS
