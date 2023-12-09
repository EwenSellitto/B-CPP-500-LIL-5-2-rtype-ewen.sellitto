/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Utilities.hpp
*/

#pragma once

#include <typeinfo>

#define ECS_TYPEID(T) typeid(T).hash_code()

namespace ECS {
typedef std::size_t id_t;
typedef std::size_t type_t;

class Utils
{
    public:
        template <typename T> static std::size_t typeId() { return typeid(T).hash_code(); }
};
} // namespace ECS
