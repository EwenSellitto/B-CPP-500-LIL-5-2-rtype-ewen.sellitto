/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Animation.system.cpp
*/

#include "Engine/Systems/UI.system.hpp"

#include <SFML/Window/Mouse.hpp>

#include "ECS/World.hpp"
#include "Engine/Engine.hpp"

using namespace Engine::System;

void UI::configure([[maybe_unused]] ECS::World &world)
{
    return;
}

void UI::unconfigure()
{
    return;
}

void UI::tick()
{
    using namespace Engine::Components;

    sf::RenderWindow *window        = &WINDOW;
    sf::Vector2i      mousePosition = sf::Mouse::getPosition(*window);
    sf::Vector2f      worldPos      = window->mapPixelToCoords(mousePosition);

    auto &world = getWorld();
    // std::cout << mousePosition.x << " " << mousePosition.y << std::endl;
    world.each<ButtonComponent, RenderableComponent>([&]([[maybe_unused]] ECS::Entity             *entity,
                                                         ECS::ComponentHandle<ButtonComponent>     buttonComp,
                                                         ECS::ComponentHandle<RenderableComponent> renderable) {
        updateButtonState(buttonComp, renderable, worldPos);
    });
    world.each<CursorComponent, PositionComponent, RenderableComponent>(
        [&]([[maybe_unused]] ECS::Entity *entity, ECS::ComponentHandle<CursorComponent> cursorComp,
            ECS::ComponentHandle<PositionComponent> position, ECS::ComponentHandle<RenderableComponent> renderable) {
            updateCursorState(cursorComp, renderable, position, mousePosition, worldPos);
        });
}

void UI::updateButtonState(ECS::ComponentHandle<Components::ButtonComponent>     buttonComp,
                           ECS::ComponentHandle<Components::RenderableComponent> renderable,
                           const sf::Vector2f                                   &worldPos)
{

    sf::FloatRect buttonRect(renderable->sprite.getGlobalBounds());

    resetButtonVisual(renderable);
    if (!buttonComp->isActivated) return;
    if (buttonRect.contains(worldPos)) {
        hoverEffect(buttonComp, renderable);
        handleClick(buttonComp, renderable);
    } else {
        buttonComp->isHovered = false;
        if (buttonComp->isClicked) {
            buttonComp->isClicked = false;
        }
    }
}

void UI::updateCursorState(ECS::ComponentHandle<Components::CursorComponent>     cursorComp,
                           ECS::ComponentHandle<Components::RenderableComponent> renderable,
                           ECS::ComponentHandle<Components::PositionComponent> position, sf::Vector2i mousePosition,
                           const sf::Vector2f &worldPos)
{

    sf::FloatRect buttonRect(renderable->sprite.getGlobalBounds());

    resetButtonVisual(renderable);

    if (buttonRect.contains(worldPos))
        handleChange(cursorComp, position, mousePosition, renderable);
    else if (cursorComp->isClicked)
        cursorComp->isClicked = false;
}

void UI::resetButtonVisual(ECS::ComponentHandle<Components::RenderableComponent> renderable)
{
    renderable->sprite.setColor(sf::Color(255, 255, 255, 255));
    renderable->scale = renderable->savedScale;
}

void UI::hoverEffect(ECS::ComponentHandle<Components::ButtonComponent>     buttonComp,
                     ECS::ComponentHandle<Components::RenderableComponent> renderable)
{
    buttonComp->isHovered = true;
    renderable->sprite.setColor(sf::Color(255, 255, 255, 200));
}

void UI::handleQuitGame()
{
    Engine::EngineClass &engine = Engine::EngineClass::getEngine();
    engine.window.close();
}

void UI::handleStartGame()
{
    Engine::EngineClass &engine = Engine::EngineClass::getEngine();
    engine.switchWorld("game");
}

void UI::handleClick(ECS::ComponentHandle<Components::ButtonComponent>     buttonComp,
                     ECS::ComponentHandle<Components::RenderableComponent> renderable)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        renderable->scale = {static_cast<float>(renderable->scale.x * 0.9),
                             static_cast<float>(renderable->scale.y * 0.9)};
        if (!buttonComp->isClicked) {
            buttonComp->isClicked = true;
        }
    } else if (buttonComp->isClicked) {
        buttonComp->onClick();
        buttonComp->isClicked = false;
    }
}

void UI::handleChange(ECS::ComponentHandle<Components::CursorComponent>   cursorComp,
                      ECS::ComponentHandle<Components::PositionComponent> position, sf::Vector2i mousePosition,
                      ECS::ComponentHandle<Components::RenderableComponent> renderable)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (position->x > 250 && position->x < 490) cursorComp->onChange();
        position->x = mousePosition.x;
    }
}
