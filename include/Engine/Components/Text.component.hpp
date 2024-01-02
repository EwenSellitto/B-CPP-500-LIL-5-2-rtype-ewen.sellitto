#pragma once
#include <functional>
#include <string>

#include "ECS/Components.hpp"

namespace Engine::Components
{
    struct TextComponent : public ECS::BaseComponent {
            std::string text;

            TextComponent(const std::string &text) : text(text) {}
    };
} // namespace Engine::Components
