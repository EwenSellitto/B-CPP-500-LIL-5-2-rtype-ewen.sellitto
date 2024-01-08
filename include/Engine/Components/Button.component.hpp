/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Renderable.component.hpp
*/

#pragma once

#include <functional>
#include <string>
#include <utility>
#include <vector>
#include <sstream>

#include "ECS/Components.hpp"
#include "public/ComponentsType.hpp"

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

            ButtonComponent(std::string text, std::function<void()> onClick) : text(std::move(text)), onClick(onClick) {}

            ~ButtonComponent() override = default;

            std::vector<char> serialize() override
            {
                return {};
            }

            ECS::BaseComponent *deserialize(const std::vector<char> vec, ECS::BaseComponent *component) final
            {
                return nullptr;
            }

            ComponentType getType() override
            {
                return ComponentType::NoneComponent;
            }
    };
} // namespace Engine::Components
