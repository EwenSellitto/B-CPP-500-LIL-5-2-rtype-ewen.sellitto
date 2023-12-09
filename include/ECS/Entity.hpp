/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Entity.hpp
*/

#pragma once

#include "Components.hpp"
#include "Utilities.hpp"
#include <unordered_map>

namespace ECS {
class World;

class Entity
{
        friend class World;

    public:
        /// \brief Construct a new Entity object
        /// \param world World to which the entity belongs
        /// \note The entity will be added to the world
        /// \note The entity will be destroyed when the world is destroyed
        /// \warning Only create an entity with a world
        Entity(World &world) : _world(world), _components(){};

        /// \brief Destroy the Entity object
        /// \note All the components will be destroyed
        /// \note The entity will be removed from the world
        /// \note The entity will be destroyed when the world is destroyed
        /// \note The entity will be removed from all the systems
        /// \warning Only destroy an entity with a world
        ~Entity() { removeAllComponents(); };

        /// \brief Add a component to the entity
        /// \tparam T Component type
        /// \param component Component to add
        /// \throw std::runtime_error if component already exists
        /// \warting Meant to be called by the user and the world
        template <typename T> void addComponent(const T &component)
        {
            _components.insert(std::make_pair(ECS_TYPEID(T), component));
        }

        /// \brief Remove a component and destroy it
        /// \tparam T Component type
        /// \throw std::out_of_range if component does not exist
        /// \note This function will destroy the component
        template <typename T> void removeComponent()
        {
            auto index = ECS_TYPEID(T);
            auto it    = _components.find(index);
            if (it != _components.end()) {
                delete it->second;
                _components.erase(it);
            }
        }

        /// \brief Remove all the components
        /// \throw std::out_of_range if component does not exist
        /// \note This function will destroy the components
        void removeAllComponents()
        {
            for (auto pair : _components) {
                delete pair.second;
            }

            _components.clear();
        }

        /// \brief Get a component
        /// \tparam T Component type
        /// \return ComponentHandle<T>
        /// \throw std::out_of_range if component does not exist
        /// \note You should not destroy the component
        template <typename T> T &getComponent() { return *static_cast<T *>(_components.at(ECS_TYPEID(T))); }

        /// \brief Get a component handle
        /// \tparam T
        /// \return ComponentHandle<T>
        /// \throw std::out_of_range if component does not exist
        template <typename T> bool has() { return _components.find(ECS_TYPEID(T)) != _components.end(); }

        /// \brief Check if entity has a list of components
        /// \tparam T
        /// \tparam Types
        /// \return bool
        /// \throw std::out_of_range if component does not exist
        template <typename T, typename V, typename... Types> bool has() { return has<T>() && has<V, Types...>(); }

    private:
        std::unordered_map<size_t, BaseComponent *> _components;
        World &_world;
};
} // namespace ECS
