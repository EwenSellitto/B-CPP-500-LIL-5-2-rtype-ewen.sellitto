
/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** World.hpp
*/

#pragma once

#include "Entity.hpp"
#include "EventSubscriber.hpp"
#include "Utilities.hpp"
#include <memory>
#include <unordered_map>

namespace ECS
{

    /**
     * @class World
     * @brief Represents the world in an Entity-Component-System (ECS) architecture, managing entities and global
     * entities.
     */
    class World
    {
        public:
            /**
             * @brief Construct a new World object.
             */
            World() : _entities(), _global_entities(), _subscribers() {}

            /**
             * @brief Destroy the World object.
             * @note This will also destroy all entities and global entities within the world.
             */
            ~World() = default;

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
                type_t id = Utils::getNewId<Entity>();
                _entities.emplace(id, std::move(entity));
                return id;
            }

            /**
             * @brief Remove an entity from the world.
             *
             * @param id The unique identifier of the entity to be removed.
             * @note The entity will be properly destroyed when removed.
             */
            void removeEntity(id_t id)
            {
                _entities.erase(id);
            }

            /**
             * @brief Get an immutable reference to an entity.
             *
             * @param id The unique identifier of the entity to get.
             * @return const Entity& An immutable reference to the entity.
             */
            const Entity &getEntity(id_t id) const
            {
                return *_entities.at(id);
            }

            /**
             * @brief Get a mutable reference to an entity.
             *
             * @param id The unique identifier of the entity to get.
             * @return Entity& A mutable reference to the entity.
             * @warning This function is meant to be used by the systems only.
             */
            Entity &getMutEntity(id_t id)
            {
                return *_entities.at(id);
            }

            /**
             * @brief Add a global entity to the world.
             *
             * @param entity A unique pointer to the GlobalEntity to be added. Ownership of the global entity is
             * transferred to the World.
             * @return id_t The unique identifier for the added global entity.
             */
            id_t addGlobalEntity(std::unique_ptr<GlobalEntity> entity)
            {
                type_t id = Utils::getNewId<GlobalEntity>();
                _global_entities.emplace(id, std::move(entity));
                return id;
            }

            /**
             * @brief Remove a global entity from the world.
             *
             * @param id The unique identifier of the global entity to be removed.
             * @note The global entity will be properly destroyed when removed from all the worlds.
             */
            void removeGlobalEntity(id_t id)
            {
                _global_entities.erase(id);
            }

            /**
             * @brief Get an immutable reference to a global entity.
             *
             * @param id The unique identifier of the global entity to get.
             * @return const GlobalEntity& An immutable reference to the global entity.
             */
            const GlobalEntity &getGlobalEntity(id_t id)
            {
                return *_global_entities.at(id);
            }

            /**
             * @brief Get a mutable reference to a global entity.
             *
             * @param id The unique identifier of the global entity to get.
             * @return GlobalEntity& A mutable reference to the global entity.
             */
            GlobalEntity &getMutGlobalEntity(id_t id)
            {
                return *_global_entities.at(id);
            }

            /**
             * @brief Subscribe an event subscriber to a specific event type.
             *
             * @param subscriber A pointer to the EventSubscriber object.
             * @return id_t The unique identifier for the subscription.
             * @note This method allows for the dynamic subscription of event handlers to specific event types.
             */
            template <typename T> id_t subscribe(const EventSubscriber<T> *subscriber)
            {
                auto type_id = ECS_TYPEID(T);
                auto uuid    = Utils::getNewId<T>();

                if (_subscribers.find(type_id) == _subscribers.end())
                    _subscribers.emplace(type_id, std::unordered_map<id_t, BaseEventSubscriber *>());

                _subscribers[type_id].emplace(
                    uuid, static_cast<BaseEventSubscriber *>(const_cast<EventSubscriber<T> *>(subscriber)));
                return uuid;
            }

            /**
             * @brief Unsubscribe an event subscriber from a specific event type.
             *
             * @param uuid The unique identifier for the subscription to be removed.
             * @note This method allows for the removal of previously subscribed event handlers.
             */
            template <typename T> void unsubscribe(id_t uuid)
            {
                auto type_id = ECS_TYPEID(T);

                if (_subscribers.find(type_id) == _subscribers.end()) return;
                _subscribers[type_id].erase(uuid);
            }

            template <typename T> void broadcastEvent(T &data, const std::string &name = "")
            {
                const std::unordered_map<id_t, BaseEventSubscriber *> &subscribers = _subscribers[ECS_TYPEID(T)];
                for (auto &subscriber : subscribers) {
                    auto *sub = static_cast<EventSubscriber<T> *>(subscriber.second);
                    sub->receiveEvent(name, data);
                }
            }

        private:
            std::unordered_map<id_t, std::unique_ptr<Entity>>                           _entities;
            std::unordered_map<id_t, std::unique_ptr<GlobalEntity>>                     _global_entities;
            std::unordered_map<type_t, std::unordered_map<id_t, BaseEventSubscriber *>> _subscribers;
    };
} // namespace ECS
