/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** World.hpp
*/

#pragma once

#include <chrono>
#include <ctime>
#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>

#include "ECS/Components.hpp"
#include "ECS/System.hpp"
#include "Engine/Engine.hpp"
#include "Entity.hpp"
#include "EventSubscriber.hpp"
#include "Utilities.hpp"

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
            World()
                : _entities(), _global_entities(), _subscribers(), _clock(), _engine(Engine::EngineClass::getEngine())
            {
            }

            /**
             * @brief Destroy the World object.
             * @note This will also destroy all entities and global entities within the world.
             */
            ~World() = default;

            /*===================//
            //  Entity Handling  //
            //===================*/

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
                type_t                  id = Utils::getNewId<Entity>();
                Events::OnEntityCreated event{entity.get()};

                _entities.emplace(id, std::move(entity));
                if (_subscribers.find(ECS_TYPEID(Events::OnEntityCreated)) != _subscribers.end())
                    broadcastEvent<Events::OnEntityCreated>(event);
                return id;
            }

            /**
             * @brief Create an empty entity.
             *
             * @return id_t The unique identifier for the created entity.
             */
            id_t addEntity()
            {
                std::unique_ptr<Entity> entity = std::make_unique<Entity>();

                return addEntity(std::move(entity));
            }

            /**
             * @brief Create an entity with a set of components.
             *
             * @tparam Components The component types to add to the entity.
             * @param components The components to add to the entity.
             * @return id_t The unique identifier for the created entity.
             * @note This function utilizes perfect forwarding to ensure that the components are properly moved into the
             * entity.
             * @warning the components should be pointers and created with 'new'
             */
            template <typename... Components> id_t createEntity(Components &&...components)
            {
                id_t  id     = addEntity();
                auto &entity = getMutEntity(id);
                (entity.addComponent(std::forward<Components>(components)), ...);
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
                Events::OnEntityDestroyed event{_entities.at(id).get()};

                _entities.erase(id);
                if (_subscribers.find(ECS_TYPEID(Events::OnEntityDestroyed)) != _subscribers.end())
                    broadcastEvent<Events::OnEntityDestroyed>(event);
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
             * @brief get all entities that have a specific component type.
             * @tparam T The component type to filter entities.
             *
             * @return std::vector<Entity *> A vector of pointers to the entities.
             */
            template <typename T> std::unordered_map<Entity *, ComponentHandle<T>> get()
            {
                std::unordered_map<Entity *, ComponentHandle<T>> entities;
                for (auto &pair : _entities) {
                    Entity &entity = *pair.second;
                    if (entity.has<T>()) {
                        ComponentHandle<T> component = entity.getComponent<T>();
                        entities.emplace(&entity, component);
                    }
                }
                return entities;
            }

            /**
             * @brief Iterates over all entities that have a specific component type.
             *
             * @tparam T The component type to filter entities.
             * @param func The callable function that will be applied to each entity and its component.
             */
            template <typename T> void each(std::function<void(Entity *, ComponentHandle<T>)> func)
            {
                for (auto &pair : _entities) {
                    Entity &entity = *pair.second;
                    if (entity.has<T>()) {
                        ComponentHandle<T> component = entity.getComponent<T>();
                        func(&entity, component);
                    }
                }
            }

            /**
             * @brief Iterates over all entities that have a specific set of component types.
             *
             * @tparam T The component type to filter entities.
             * @tparam U The component type to filter entities.
             * @param func The callable function that will be applied to each entity and its component.
             */
            template <typename T, typename U>
            void each(std::function<void(Entity *, ComponentHandle<T>, ComponentHandle<U>)> func)
            {
                for (auto &pair : _entities) {
                    Entity &entity = *pair.second;
                    if (entity.has<T>() && entity.has<U>()) {
                        ComponentHandle<T> componentT = entity.getComponent<T>();
                        ComponentHandle<U> componentU = entity.getComponent<U>();
                        func(&entity, componentT, componentU);
                    }
                }
            }

            /**
             * @brief Iterates over all entities that have a specific set of component types.
             * @tparam T The component type to filter entities.
             * @tparam U The component type to filter entities.
             * @param func The callable function that will be applied to each entity and its component.
             */
            template <typename T, typename U, typename V>
            void each(std::function<void(Entity *, ComponentHandle<T>, ComponentHandle<U>, ComponentHandle<V>)> func)
            {
                for (auto &pair : _entities) {
                    Entity &entity = *pair.second;
                    if (entity.has<T>() && entity.has<U>()) {
                        ComponentHandle<T> componentT = entity.getComponent<T>();
                        ComponentHandle<U> componentU = entity.getComponent<U>();
                        ComponentHandle<V> componentV = entity.getComponent<V>();
                        func(&entity, componentT, componentU, componentV);
                    }
                }
            }

            /**
             * @brief Iterates over all entities that have a specific set of component types.
             *
             * @tparam Types Component types to filter entities.
             * @param func The callable function that will be applied to each entity and its components.
             * @note This function utilizes a helper function to handle the iteration and application of the function.
             */
            template <typename... Types> void each(std::function<void(Entity *, ComponentHandle<Types...>)> func)
            {
                for (auto &pair : _entities) {
                    Entity &entity = *pair.second;
                    if (entity.has<Types...>()) {
                        _eachHelper<Types...>(&entity, func);
                    }
                }
            }

            /**
             * @brief get all entities that have a set of given components.
             *
             * @tparam Types The component types to filter entities.
             * @return std::vector<Entity *> A vector of pointers to the entities.
             */
            template <typename... Types> std::vector<Entity *> getEntitiesWithComponents()
            {
                std::vector<Entity *> entities;
                for (auto &pair : _entities) {
                    Entity &entity = *pair.second;
                    if (entity.has<Types...>()) {
                        entities.push_back(&entity);
                    }
                }
                return entities;
            }

            /*=========================//
            //  GlobalEntity Handling  //
            //=========================*/

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
             * @brief Get all global entities that have a specific component type.
             *
             * @tparam T The component type to filter global entities.
             * @return std::vector<GlobalEntity *> A vector of pointers to the global entities.
             */
            template <typename T> std::unordered_map<ECS::GlobalEntity *, ComponentHandle<T>> getGlobal()
            {
                std::unordered_map<ECS::GlobalEntity *, ComponentHandle<T>> entities;
                for (auto &pair : _global_entities) {
                    GlobalEntity &entity = *pair.second;
                    if (entity.has<T>()) {
                        ComponentHandle<T> component = entity.getComponent<T>();
                        entities.emplace(&entity, component);
                    }
                }
                return entities;
            }

            // /**
            //  * @brief Iterates over all entities that have a specific component type.
            //  *
            //  * @tparam T The component type to filter entities.
            //  * @param func The callable function that will be applied to each global entity and its component.
            //  */
            // template <typename T> void each(std::function<void(GlobalEntity *, ComponentHandle<T>)> func)
            // {
            //     for (auto &pair : _global_entities) {
            //         Entity &entity = *pair.second;
            //         if (entity.has<T>()) {
            //             ComponentHandle<T> component = entity.getComponent<T>();
            //             func(&entity, component);
            //         }
            //     }
            // }
            //
            // /**
            //  * @brief Iterates over all entities that have a specific set of component types.
            //  *
            //  * @tparam Types Component types to filter entities.
            //  * @param func The callable function that will be applied to each global entity and its components.
            //  * @note This function utilizes a helper function to handle the iteration and application of the
            //  function.
            //  */
            // template <typename... Types> void each(std::function<void(GlobalEntity *, ComponentHandle<Types...>)>
            // func)
            // {
            //     for (auto &pair : _global_entities) {
            //         Entity &entity = *pair.second;
            //         if (entity.has<Types...>()) {
            //             _eachHelper<Types...>(&entity, func);
            //         }
            //     }
            // }

            /*==================//
            //  Event Handling  //
            //==================*/

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

            /**
             * @brief Broadcast an event to all subscribers of a specific event type.
             *
             * @tparam T The type of the event data to be broadcast.
             * @param data The event data to be broadcast.
             * @param name The name of the event.
             * @note This method allows for the dynamic broadcasting of events to all subscribers of a specific event
             * type.
             * @warning This method can cause infinite recursion if its broadcasting an event of type T or it broadcast
             */
            template <typename T> void broadcastEvent(T data, const std::string name = "")
            {
                using namespace std::chrono;

                const std::unordered_map<id_t, BaseEventSubscriber *> &subscribers = _subscribers[ECS_TYPEID(T)];

                std::cout << "[" << duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count()
                          << "]\tBroadcasting event of type " << ECS_TYPEID(T) << std::endl;

                for (auto &subscriber : subscribers) {
                    auto *sub = static_cast<EventSubscriber<T> *>(subscriber.second);
                    sub->receiveEvent(name, data);
                }
            }

            /*====================//
            //  Systems Handling  //
            //====================*/

            /**
             * @brief Add a system to the world.
             *
             * @tparam System The system type to be added.
             * @param name The name of the system.
             * @param args The arguments to be forwarded to the system constructor.
             * @note This method allows for the dynamic addition of systems to the world.
             */
            template <typename System, typename... types> void addSystem(std::string name, types &&...args)
            {
                _systems.emplace(name, std::make_unique<System>(*this, std::forward<types>(args)...));
            }

            /**
             * @brief Add a system to the world.
             *
             * @tparam System The system type to be added.
             * @param name The name of the system.
             */
            template <typename System> void addSystem(std::string name)
            {
                _systems.emplace(name, std::make_unique<System>(*this));
            }

            /*==================//
            //  Logic Handling  //
            //==================*/

            /**
             * @brief Give the elapsed time between two calls of this function
             *
             * @return the elapsed time between two calls of this function
             * @note on first call will give the time elapsed since the start of the programm
             */
            std::clock_t getWorldTime()
            {
                return _clock.getElapsedTime();
            }

            // TODO : implement this tick function by calling each ticks of the systems in a thread
            void tick()
            {
                for (auto &system : _systems)
                    system.second->tick();
            }

            /*===================//
            //  Getters/Setters  //
            //===================*/

            /**
             * @brief Get the engine object.
             *
             * @return Engine::EngineClass& A reference to the engine object.
             */
            std::unordered_map<std::string, std::unique_ptr<BaseSystem>> &getSystems()
            {
                return _systems;
            }

        private:
            /*====================//
            //  Helper Functions  //
            //====================*/

            /**
             * @brief Helper function to call a function on an entity with a single component type.
             *
             * @tparam T The component type.
             * @param entity Pointer to the entity.
             * @param func The function to be applied to the entity and its component.
             */
            template <typename T>
            void _eachHelper(Entity *entity, std::function<void(Entity *, ComponentHandle<T>)> func)
            {
                func(&entity, entity->getComponent<T>());
            }

            /**
             * @brief Recursive helper function to call a function on an entity with multiple component types.
             *
             * @tparam T The current component type being processed.
             * @tparam V The next component type to be processed.
             * @tparam Types Remaining component types to be processed.
             * @param entity Pointer to the entity.
             * @param func The function to be applied to the entity and its component.
             * @note This function recursively iterates through the component types.
             */
            template <typename T, typename V, typename... Types>
            void _eachHelper(Entity *entity, std::function<void(Entity *, ComponentHandle<T>)> func)
            {
                entity->has<T>() ? _eachHelper<T>(entity, func) : nullptr;
                _eachHelper<V, Types...>(entity, func);
            }

            /**
             * @brief Helper function to call a function on a global entity with a single component type.
             *
             * @tparam T The component type.
             * @param g_entity Pointer to the entity.
             * @param func The function to be applied to the global entity and its component.
             */
            template <typename T>
            void _eachHelper(GlobalEntity *g_entity, std::function<void(GlobalEntity *, ComponentHandle<T>)> func)
            {
                func(&g_entity, g_entity->getComponent<T>());
            }

            /**
             * @brief Recursive helper function to call a function on a global entity with multiple component types.
             *
             * @tparam T The current component type being processed.
             * @tparam V The next component type to be processed.
             * @tparam Types Remaining component types to be processed.
             * @param g_entity Pointer to the entity.
             * @param func The function to be applied to the global entity and its component.
             * @note This function recursively iterates through the component types.
             */
            template <typename T, typename V, typename... Types>
            void _eachHelper(GlobalEntity *g_entity, std::function<void(GlobalEntity *, ComponentHandle<T>)> func)
            {
                g_entity->has<T>() ? _eachHelper<T>(g_entity, func) : nullptr;
                _eachHelper<V, Types...>(g_entity, func);
            }

            /*==============//
            //  Attributes  //
            //==============*/

            std::unordered_map<id_t, std::unique_ptr<Entity>>                           _entities;
            std::unordered_map<id_t, std::unique_ptr<GlobalEntity>>                     _global_entities;
            std::unordered_map<type_t, std::unordered_map<id_t, BaseEventSubscriber *>> _subscribers;
            std::unordered_map<std::string, std::unique_ptr<BaseSystem>>                _systems;
            Clock                                                                       _clock;
            Engine::EngineClass                                                        &_engine;
    };
} // namespace ECS
