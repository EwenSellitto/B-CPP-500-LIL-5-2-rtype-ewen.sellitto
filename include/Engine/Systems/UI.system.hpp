/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** UISystem
*/

#pragma once

#include "ECS/Components.hpp"
#include "ECS/System.hpp"
#include "ECS/World.hpp"
#include "Engine/Components/Button.component.hpp"
#include "Engine/Components/Cursor.component.hpp"
#include "Engine/Components/Position.component.hpp"
#include "Engine/Components/Renderable.component.hpp"

namespace Engine::System
{
    class UI : public ECS::BaseSystem
    {
        public:
            UI(ECS::World &world) : ECS::BaseSystem(world){};
            UI(ECS::World &world, ECS::id_t ids...) : ECS::BaseSystem(world, ids) {}
            ~UI() override = default;

            void configure(ECS::World &world) override;

            void unconfigure() override;

            void tick() override;

            void handleStartGame();

            void handleQuitGame();

        private:
            void updateCursorState(ECS::ComponentHandle<Components::CursorComponent>     cursorComp,
                                   ECS::ComponentHandle<Components::RenderableComponent> renderable,
                                   ECS::ComponentHandle<Components::PositionComponent>   position,
                                   sf::Vector2i mousePosition, const sf::Vector2f &worldPos);
            void updateButtonState(ECS::ComponentHandle<Components::ButtonComponent>     buttonComp,
                                   ECS::ComponentHandle<Components::RenderableComponent> renderable,
                                   const sf::Vector2f                                   &worldPos);
            void resetButtonVisual(ECS::ComponentHandle<Components::RenderableComponent> renderable);
            void hoverEffect(ECS::ComponentHandle<Components::ButtonComponent>     buttonComp,
                             ECS::ComponentHandle<Components::RenderableComponent> renderable);
            void handleClick(ECS::ComponentHandle<Components::ButtonComponent>     buttonComp,
                             ECS::ComponentHandle<Components::RenderableComponent> renderable);
            void handleChange(ECS::ComponentHandle<Components::CursorComponent>   cursorComp,
                              ECS::ComponentHandle<Components::PositionComponent> position, sf::Vector2i mousePosition,
                              ECS::ComponentHandle<Components::RenderableComponent> renderable);
    };
} // namespace Engine::System
