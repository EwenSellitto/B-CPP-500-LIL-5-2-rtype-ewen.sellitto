/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Renderer.systems.cpp
*/

#include "Engine/Systems/Renderer.system.hpp"

#include <map>

#include "ECS/Entity.hpp"
#include "Engine/Components/Position.component.hpp"
#include "Engine/Components/Renderable.component.hpp"
#include "Engine/Components/View.component.hpp"
#include "Engine/Engine.hpp"

using namespace Engine::System;

void Renderer::configure([[maybe_unused]] ECS::World &world) {}

void Renderer::unconfigure() {}

void Renderer::tick()
{
    using namespace Engine::Components;

    ECS::World                                                            &world = getWorld();
    std::map<int, std::vector<ECS::ComponentHandle<RenderableComponent>>>  components{};
    sf::RenderWindow                                                      *window = &WINDOW;
    std::unordered_map<ECS::Entity *, ECS::ComponentHandle<ViewComponent>> ViewEntities;

    ViewEntities = world.get<ViewComponent>();
    if (ViewEntities.empty()) {
        std::cerr << "ViewComponent missing, declare one" << std::endl;
        exit(84);
    } else {
        auto                                it            = ViewEntities.begin();
        ECS::ComponentHandle<ViewComponent> viewComponent = it->second;
        window->setView(viewComponent->view);
    }
    world.each<RenderableComponent>([&](ECS::Entity *entity, ECS::ComponentHandle<RenderableComponent> renderableComp) {
        if (entity->has<PositionComponent>()) {
            auto positionComponent = entity->getComponent<PositionComponent>();
            renderableComp->sprite.setPosition(positionComponent->x, positionComponent->y);
            renderableComp->sprite.setRotation(renderableComp->rotation);
            renderableComp->sprite.setScale(renderableComp->scale);
            renderableComp->size = {
                static_cast<std::size_t>(renderableComp->sprite.getTexture()->getSize().x * renderableComp->scale.x),
                static_cast<std::size_t>(renderableComp->sprite.getTexture()->getSize().y * renderableComp->scale.y)};
        }
        components[renderableComp->priority].push_back(renderableComp);
    });

    window->clear(sf::Color::Black);
    for (auto &priorityGroup : components) {
        for (auto &renderableComp : priorityGroup.second) {
            if (!renderableComp->isDisplayed) continue;
            window->draw(renderableComp->sprite);
        }
    }
    window->display();
}
