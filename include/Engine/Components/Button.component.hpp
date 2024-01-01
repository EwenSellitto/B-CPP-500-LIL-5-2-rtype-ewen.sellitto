#pragma once
#include <functional>
#include <string>

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
    };
} // namespace Engine::Components
