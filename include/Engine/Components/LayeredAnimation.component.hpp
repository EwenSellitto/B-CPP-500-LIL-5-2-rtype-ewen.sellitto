/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** LayeredAnimation.component.hpp
*/

#pragma once

#include <vector>

#include "ECS/Components.hpp"
#include "Engine/Components/Animation.component.hpp"

namespace Engine::Components
{
    class LayeredAnimationComponent : public ECS::BaseComponent
    {
        public:
            LayeredAnimationComponent()           = default;
            ~LayeredAnimationComponent() override = default;

            /**
             * @brief Construct a new Layered Animation Component object
             *
             * @param first
             * @param rest
             * @note the order of the animations is the order of the parameters and is linked with the layered render
             * component order
             */
            template <typename... Animations>
            LayeredAnimationComponent(AnimationComponent *first, Animations... rest)
                : animation{std::shared_ptr<AnimationComponent>(first), std::shared_ptr<AnimationComponent>(rest)...},
                  layers(0)
            {
                layers = animation.size();
            }

            std::vector<char> serialize() override
            {
                return {};
            }

            ECS::BaseComponent *deserialize([[maybe_unused]] const std::vector<char> vec,
                                            [[maybe_unused]] ECS::BaseComponent     *component) final
            {
                return component;
            }

            ECS::ComponentHandle<AnimationComponent> at(int index)
            {
                return ECS::ComponentHandle<AnimationComponent>(animation[index]);
            }

            ComponentType getType() override
            {
                return ComponentType::NoneComponent;
            }

            std::vector<std::shared_ptr<AnimationComponent>> animation;
            int                                              layers;
    };

} // namespace Engine::Components
