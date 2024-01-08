#pragma once
#include <functional>
#include <string>

#include "ECS/Components.hpp"

namespace Engine::Components
{
    struct CursorComponent : public ECS::BaseComponent {
            std::function<void()> onChange;
            bool                  isClicked = false;

            CursorComponent(std::function<void()> onChange) : onChange(onChange) {}
    };
} // namespace Engine::Components
