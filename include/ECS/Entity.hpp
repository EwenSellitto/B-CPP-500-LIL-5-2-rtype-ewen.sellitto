/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Entity.hpp
*/

#pragma once

#include <ctime>
#include <memory>
#include <sys/types.h>
#include <unordered_map>
#include <vector>

#include "Clock.hpp"
#include "Components.hpp"
#include "Utilities.hpp"

namespace ECS
{

    class World;

    /**
     * @class Entity
     * @brief Represents an entity in an Entity-Component-System (ECS) architecture.
     * @note you should create a child class that create instance of the needed components (just overload the
     * constructor)
     */
    class Entity
    {
            friend class World;

        public:
            /**
             * @brief Construct a new Entity object.
             * @param world Reference to the World to which this Entity belongs.
             * @note The Entity will be added to the World.
             * @note The Entity will be destroyed when the World is destroyed.
             * @warning Only create an Entity with a World.
             */
            explicit Entity() : _components(), _clock(){};

            /**
             * @brief Destroy the Entity object.
             * @note All components will be destroyed.
             * @note The Entity will be removed from  the World.
             * @note The Entity will be destroyed when the World is destroyed.
             * @note The Entity will be removed from all the systems.
             * @warning Only destroy an Entity with a World.
             */
            ~Entity()
            {
                removeAllComponents();
            };

            /**
             * @brief Add a component to the Entity.
             * @brief and deletes the sent references
             * @tparam T Type of the component.
             * @param component Component to add, passed as an rvalue.
             * @throw std::runtime_error if the component already exists.
             * @warning Meant to be called by the user and the World.
             */
            template <typename T> void addComponent(T *component)
            {
                _components.emplace(ECS_TYPEID(T), std::shared_ptr<T>(component));
            }

            /**
             * @brief Remove a component and destroy it.
             * @tparam T Type of the component.
             * @throw std::out_of_range if the component does not exist.
             * @note This function will destroy the component.
             */
            template <typename T> void removeComponent()
            {
                auto index = ECS_TYPEID(T);
                auto it    = _components.find(index);
                if (it != _components.end()) {
                    _components.erase(it);
                }
            }

            /**
             * @brief Remove all components.
             * @throw std::out_of_range if a component does not exist.
             * @note This function will destroy the components.
             */
            void removeAllComponents()
            {
                _components.clear();
            }

            /**
             * @brief Get a component.
             * @tparam T Type of the component.
             * @return ComponentHandle<T> Handle to the component.
             * @throw std::out_of_range if the component does not exist.
             * @note You should not destroy the component.
             */
            template <typename T> ComponentHandle<T> getComponent()
            {
                auto               baseComponentPtr     = _components.at(ECS_TYPEID(T));
                std::shared_ptr<T> specificComponentPtr = std::dynamic_pointer_cast<T>(baseComponentPtr);
                return ComponentHandle<T>(specificComponentPtr);
            }

            /**
             * @brief Check if the Entity has a component of a specific type.
             * @tparam T Type of the component.
             * @return bool True if the component exists, false otherwise.
             */
            template <typename T> bool has() const
            {
                if (_components.empty()) return false;
                return _components.find(ECS_TYPEID(T)) != _components.end();
            }

            /**
             * @brief Check if the Entity has a list of components.
             * @tparam T First component type to check.
             * @tparam Types Other component types to check.
             * @return bool True if all specified components exist, false otherwise.
             * @throw std::out_of_range if a component does not exist.
             */
            template <typename T, typename V, typename... Types> bool has() const
            {
                return has<T>() && has<V, Types...>();
            }

            /**
             * @brief Get the time elapsed since the last call to this function.
             * @return std::clock_t The time elapsed since the last call to this function.
             */
            std::clock_t getElapsedTime()
            {
                return _clock.getElapsedTime();
            }

        private:
            std::unordered_map<id_t, std::shared_ptr<BaseComponent>> _components;
            Clock                                                    _clock;
    };

    class GlobalEntity : public Entity
    {
        public:
            GlobalEntity(World *world) : Entity(), _worlds()
            {
                _worlds.push_back(world);
            }
            ~GlobalEntity() {}

        private:
            std::vector<World *> _worlds;
    };

} // namespace ECS
