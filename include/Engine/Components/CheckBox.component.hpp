#pragma once
#include <functional>
#include <string>

#include "ECS/Components.hpp"

namespace Engine::Components
{
    struct CheckBoxComponent : public ECS::BaseComponent {
            std::string           text;
            std::function<void()> clickOn;
            std::function<void()> clickOff;
            bool                  isActivated;
            bool                  status    = false;
            bool                  isClicked = false;

            CheckBoxComponent(const std::string &text, std::function<void()> clickOn, std::function<void()> clickOff,
                              bool isActivated = true)
                : text(text), clickOff(clickOff), clickOn(clickOn), isActivated(isActivated)
            {
            }
    };
} // namespace Engine::Components
