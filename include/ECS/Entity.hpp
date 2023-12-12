/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Entity.hpp
*/

#pragma once

#include <sys/types.h>
#include <memory>
#include <unordered_map>

#include "Components.hpp"
#include "Utilities.hpp"

namespace ECS {

class World;

/**
 * @class Entity
 * @brief Represents an entity in an Entity-Component-System (ECS) architecture.
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
        explicit Entity(World &world) : _components(), _world(world){};

        /**
         * @brief Destroy the Entity object.
         * @note All components will be destroyed.
         * @note The Entity will be removed from the World.
         * @note The Entity will be destroyed when the World is destroyed.
         * @note The Entity will be removed from all the systems.
         * @warning Only destroy an Entity with a World.
         */
        ~Entity() { removeAllComponents(); };

        /**
         * @brief Add a component to the Entity.
         * @brief and deletes the sent references
         * @tparam T Type of the component.
         * @param component Component to add.
         * @throw std::runtime_error if the component already exists.
         * @warning Meant to be called by the user and the World.
         */
        template <typename T> void addComponent(const T component)
        {
            _components.insert(std::make_pair(ECS_TYPEID(T), std::make_shared<T>(component)));
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
        void removeAllComponents() { _components.clear(); }

        /**
         * @brief Get a component.
         * @tparam T Type of the component.
         * @return ComponentHandle<T> Handle to the component.
         * @throw std::out_of_range if the component does not exist.
         * @note You should not destroy the component.
         */
        template <typename T> ComponentHandle<T> getComponent()
        {
            auto baseComponentPtr                   = _components.at(ECS_TYPEID(T));
            std::shared_ptr<T> specificComponentPtr = std::dynamic_pointer_cast<T>(baseComponentPtr);
            return ComponentHandle<T>(specificComponentPtr);
        }

        /**
         * @brief Check if the Entity has a component of a specific type.
         * @tparam T Type of the component.
         * @return bool True if the component exists, false otherwise.
         */
        template <typename T> bool has() const { return _components.find(ECS_TYPEID(T)) != _components.end(); }

        /**
         * @brief Check if the Entity has a list of components.
         * @tparam T First component type to check.
         * @tparam Types Other component types to check.
         * @return bool True if all specified components exist, false otherwise.
         * @throw std::out_of_range if a component does not exist.
         */
        template <typename T, typename V, typename... Types> bool has() const { return has<T>() && has<V, Types...>(); }

    private:
        std::unordered_map<id_t, std::shared_ptr<BaseComponent>>
            _components; ///< Mapping of component type IDs to component pointers.
        World &_world;   ///< Reference to the World this Entity belongs to.
};

class GlobalEntity : public Entity
{
};
} // namespace ECS
