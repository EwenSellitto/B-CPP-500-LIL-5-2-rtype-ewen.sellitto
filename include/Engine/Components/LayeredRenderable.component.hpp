/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** LayeredRenderable.component.hpp
*/

#pragma once

#include "ECS/Components.hpp"
#include "Engine/Components/Renderable.component.hpp"

namespace Engine::Components
{
    struct LayeredRenderableComponent : ECS::BaseComponent {
            LayeredRenderableComponent(int priority, RenderableComponent *first)
                : renderable{std::shared_ptr<RenderableComponent>(first)}, layers(0), priority(priority)
            {
                layers = renderable.size();
            }
            template <typename... Renderables>
            LayeredRenderableComponent(int priority, RenderableComponent *first, Renderables... rest)
                : renderable{std::shared_ptr<RenderableComponent>(first),
                             std::shared_ptr<RenderableComponent>(rest)...},
                  layers(0), priority(priority)
            {
                layers = renderable.size();
            }
            ~LayeredRenderableComponent() override = default;

            ECS::ComponentHandle<RenderableComponent> at(int index)
            {
                return ECS::ComponentHandle<RenderableComponent>(renderable[index]);
            }

            std::vector<std::shared_ptr<RenderableComponent>> renderable;
            int                                               layers;
            int                                               priority;
            bool                                              isDisplayed = true;
    };

} // namespace Engine::Components
