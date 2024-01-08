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

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
typedef long int Int64;
#endif

#ifndef PRINT_EVENTS
#define NO_PRINT_EVENTS
#endif

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
            World() : _entities(), _subscribers(), _clock(), _engine(Engine::EngineClass::getEngine()) {}

            /**
             * @brief Destroy the World object.
             * @note This will also destroy all entities and global entities within the world.
             */
            ~World()
            {
                _systems.clear();
                _entities.clear();
                for (auto &sub : _subscribers) {
                    for (auto &pair : sub.second) {
                        delete pair.second;
                    }
                }
            }

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

                entity->setId(id);
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

            /**
             * @brief get the first entity that have a set of given components.
             *
             * @tparam Types The component types to filter entities.
             * @return Entity * A pointer to the entity.
             */
            template <typename... Types> Entity *getEntityWithComponents()
            {
                std::vector<Entity *> entities = getEntitiesWithComponents<Types...>();

                if (entities.empty()) return nullptr;

                return entities[0];
            }

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

#ifndef NO_PRINT_EVENTS
                std::cout << "[" << duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count()
                          << "]\tBroadcasting event of type " << ECS_TYPEID(T) << std::endl;
#endif

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

            /**
             * @brief Tick the world.
             * @note This function will call the tick function of all the systems in the world.
             * @warning This function should only be called by the Engine.
             * @see Engine::EngineClass
             * @see ECS::BaseSystem
             */
            void tick()
            {
                BaseSystem *renderer;

                for (auto &system : _systems) {
                    if (system.first == "Renderer") {
                        renderer = system.second.get();
                        continue;
                    }
                    system.second->tick();
                }
                renderer->tick();
            }

            /*===================//
            //  Getters/Setters  //
            //===================*/

            /**
             * @brief Get the systems of the world.
             *
             * @return std::unordered_map<std::string, std::unique_ptr<BaseSystem>> A reference to Systems
             * unordered_map.
             */
            std::unordered_map<std::string, std::unique_ptr<BaseSystem>> &getSystems()
            {
                return _systems;
            }

            /**
             * @brief Get the entities of the world.
             *
             * @return std::unordered_map<std::string, std::unique_ptr<BaseSystem>> A reference to Entities
             * unordered_map.
             */
            std::unordered_map<id_t, std::unique_ptr<Entity>> &getEntities()
            {
                return _entities;
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

            /*==============//
            //  Attributes  //
            //==============*/

            std::unordered_map<id_t, std::unique_ptr<Entity>>                           _entities;
            std::unordered_map<type_t, std::unordered_map<id_t, BaseEventSubscriber *>> _subscribers;
            std::unordered_map<std::string, std::unique_ptr<BaseSystem>>                _systems;
            Clock                                                                       _clock;
            Engine::EngineClass                                                        &_engine;
    };
} // namespace ECS
