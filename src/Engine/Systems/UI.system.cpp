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

    // Réinitialiser l'état visuel du bouton
    resetButtonVisual(renderable);

    // Mise à jour de l'état du bouton en fonction de la position de la souris
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
    renderable->sprite.setColor(sf::Color(255, 255, 255, 200)); // Effet visuel pour le survol
}

void UI::handleClick(ECS::ComponentHandle<Components::ButtonComponent> buttonComp,
                     ECS::ComponentHandle<Components::RenderableComponent> renderable) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        renderable->scale = {0.9f, 0.9f};
        if (!buttonComp->isClicked) {
            buttonComp->isClicked = true;
        }
    } else if (buttonComp->isClicked) {
        buttonComp->onClick(); // Déclencher l'action si le bouton est relâché dessus
        buttonComp->isClicked = false;
    }
}

