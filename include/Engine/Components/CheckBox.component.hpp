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
            CheckBoxComponent()           = default;
            ~CheckBoxComponent() override = default;

            std::vector<char> serialize() override
            {
                std::ostringstream oss(std::ios::binary);

                const std::string &str = oss.str();
                return {str.begin(), str.end()};
            }

            ECS::BaseComponent *deserialize(std::vector<char> vec, ECS::BaseComponent *component) override
            {
                return component;
            }

            ComponentType getType() override
            {
                return ComponentType::NoneComponent;
            }
    };
} // namespace Engine::Components
