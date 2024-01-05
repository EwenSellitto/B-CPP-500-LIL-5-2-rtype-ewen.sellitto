/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Renderable.component.hpp
*/

#pragma once

#include <functional>
#include <string>
#include <vector>
#include <sstream>

#include "ECS/Components.hpp"

enum class ButtonType {
    Simple
};

namespace Engine::Components
{
    struct ButtonComponent : public ECS::BaseComponent {
            std::string           text;
            std::function<void()> onClick;
            bool                  isHovered = false;
            bool                  isClicked = false;

            ButtonComponent(const std::string &text, std::function<void()> onClick) : text(text), onClick(onClick) {}

            ~ButtonComponent() override = default;

            std::vector<char> serialize(void) override
            {
                return std::vector<char>();
            }
    };
} // namespace Engine::Components
