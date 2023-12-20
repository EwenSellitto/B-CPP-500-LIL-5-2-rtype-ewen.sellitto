/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main
*/

#ifndef R_TYPE_HPP
#define R_TYPE_HPP

#include <memory>
#include <thread>

#include "ECS/Components.hpp"

struct PositionComponent : public ECS::BaseComponent {
    public:
        PositionComponent() : x(0), y(0){};
        explicit PositionComponent(int x, int y) : x(x), y(y){};
        ~PositionComponent() override = default;

        int x;
        int y;
};

#endif // R_TYPE_HPP
