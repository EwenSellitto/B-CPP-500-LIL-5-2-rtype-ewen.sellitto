#pragma once
#include <functional>
#include <string>

#include "ECS/Components.hpp"

namespace Engine::Components
{
    struct TextInputComponent : public ECS::BaseComponent {
            std::string           text;
            std::function<void()> onChange;
            bool                  isClicked = false;

            TextInputComponent(std::string defaultValue, std::function<void()> onChange)
                : text(defaultValue), onChange(onChange)
            {
            }
    };
} // namespace Engine::Components
