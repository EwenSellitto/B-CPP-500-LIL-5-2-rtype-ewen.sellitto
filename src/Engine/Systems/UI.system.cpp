/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Animation.system.cpp
*/

#include "Engine/Systems/UI.system.hpp"

#include "ECS/World.hpp"

#include "Engine/Engine.hpp"

#include <SFML/Window/Mouse.hpp>

using namespace Engine::System;

void UI::configure([[maybe_unused]] ECS::World &world)
{
    return;
}

void UI::unconfigure()
{
    return;
}

void UI::tick() {
    using namespace Engine::Components;

    sf::RenderWindow *window = &WINDOW;
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
    sf::Vector2f worldPos = window->mapPixelToCoords(mousePosition);

    auto &world = getWorld();

    world.each<ButtonComponent, RenderableComponent>(
        [&]([[maybe_unused]]ECS::Entity *entity,
            ECS::ComponentHandle<ButtonComponent> buttonComp,
            ECS::ComponentHandle<RenderableComponent> renderable) {
            
            updateButtonState(buttonComp, renderable, worldPos);
        }
    );
}

void UI::updateButtonState(ECS::ComponentHandle<Components::ButtonComponent> buttonComp,
                           ECS::ComponentHandle<Components::RenderableComponent> renderable,
                           const sf::Vector2f& worldPos) {

    sf::FloatRect buttonRect(renderable->sprite.getGlobalBounds());

    resetButtonVisual(renderable);

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

void UI::resetButtonVisual(ECS::ComponentHandle<Components::RenderableComponent> renderable) {
    renderable->sprite.setColor(sf::Color(255, 255, 255, 255));
    renderable->scale = {1, 1};
}

void UI::hoverEffect(ECS::ComponentHandle<Components::ButtonComponent> buttonComp,
                     ECS::ComponentHandle<Components::RenderableComponent> renderable) {
    buttonComp->isHovered = true;
    renderable->sprite.setColor(sf::Color(255, 255, 255, 200));
}

void UI::handleStartGame()
{
    Engine::EngineClass &engine = Engine::EngineClass::getEngine();
    engine.switchWorld("game");
}

void UI::handleClick(ECS::ComponentHandle<Components::ButtonComponent> buttonComp,
                     ECS::ComponentHandle<Components::RenderableComponent> renderable) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        renderable->scale = {0.9f, 0.9f};
        if (!buttonComp->isClicked) {
            buttonComp->isClicked = true;
        }
    } else if (buttonComp->isClicked) {
        buttonComp->onClick();
        buttonComp->isClicked = false;

        if (buttonComp->text == "Start Game")
            handleStartGame();
    }
}

