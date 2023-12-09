/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Components.hpp
*/

#pragma once

namespace ECS {
class World;
class Entity;

class BaseComponent
{
    public:
        virtual ~BaseComponent() = 0;
};

template <typename T> class ComponentHandle
{
    public:
        ComponentHandle() : _component(nullptr){};
        ComponentHandle(BaseComponent *component) : _component(component){};

        ~ComponentHandle() = default;

        T *get() { return *static_cast<T *>(_component); }

        T *operator*() { return get(); }

        T *operator->() { return &get(); }

        bool operator==(const ComponentHandle<T> &other) { return _component == other._component; }
        bool operator==(bool other) { return isValid() == other; }

        bool operator!=(const ComponentHandle<T> &other) { return _component != other._component; }
        bool operator!=(bool other) { return isValid() != other; }

        bool isValid() { return _component != nullptr; }

    private:
        BaseComponent *_component;
};
} // namespace ECS
