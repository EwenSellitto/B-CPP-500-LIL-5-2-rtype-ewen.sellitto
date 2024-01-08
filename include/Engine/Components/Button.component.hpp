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
            bool                  isActivated;
            bool                  isHovered = false;
            bool                  isClicked = false;

            ButtonComponent(const std::string &text, std::function<void()> onClick, bool isActivated = true)
                : text(text), onClick(onClick), isActivated(isActivated)
            {
            }
    };
} // namespace Engine::Components
