/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Drawable.component.hpp
*/

#pragma once

#include "ECS/Components.hpp"
#include "SFML/Graphics/Drawable.hpp"

class DrawableComponent : public ECS::BaseComponent
{
    public:
        DrawableComponent(sf::Drawable *drawable) : drawable(drawable){};

        sf::Drawable *drawable;
};
