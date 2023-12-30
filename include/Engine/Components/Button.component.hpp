#pragma once
#include "ECS/Components.hpp"
#include <functional>
#include <string>

enum class ButtonType {
    Simple
};

namespace Engine::Components {
    struct ButtonComponent : public ECS::BaseComponent {
        std::string text;
        std::function<void()> onClick;
        bool isHovered = false;
        bool isClicked = false;

        ButtonComponent(const std::string& text, std::function<void()> onClick)
            : text(text), onClick(onClick) {}
    };
}
