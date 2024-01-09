/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Renderer.systems.cpp
*/

#include "Engine/Systems/Renderer.system.hpp"

#include <map>

#include "ECS/Components.hpp"
#include "ECS/Entity.hpp"
#include "Engine/Components/Drawable.component.hpp"
#include "Engine/Components/LayeredRenderable.component.hpp"
#include "Engine/Components/Position.component.hpp"
#include "Engine/Components/Renderable.component.hpp"
#include "Engine/Components/Text.component.hpp"
#include "Engine/Components/View.component.hpp"
#include "Engine/Engine.hpp"

using namespace Engine::System;

void Renderer::configure([[maybe_unused]] ECS::World &world) {}

void Renderer::unconfigure() {}

static void updateSprite(ECS::ComponentHandle<Engine::Components::RenderableComponent> renderable,
                         ECS::ComponentHandle<Engine::Components::PositionComponent>   positionComponent)
{
    renderable->sprite.setPosition(positionComponent->x, positionComponent->y);
    renderable->sprite.setRotation(renderable->rotation);
    renderable->sprite.setScale(renderable->scale);
    renderable->size = {static_cast<std::size_t>(renderable->sprite.getTexture()->getSize().x * renderable->scale.x),
                        static_cast<std::size_t>(renderable->sprite.getTexture()->getSize().y * renderable->scale.y)};
}

void Renderer::tick()
{
    using namespace Engine::Components;

    ECS::World                                                                  &world = getWorld();
    std::map<int, std::vector<ECS::ComponentHandle<RenderableComponent>>>        components{};
    std::map<int, std::vector<ECS::ComponentHandle<LayeredRenderableComponent>>> layeredComponents{};
    std::map<int, bool>                                                          keys{};
    sf::RenderWindow                                                            *window = &WINDOW;
    std::unordered_map<ECS::Entity *, ECS::ComponentHandle<ViewComponent>>       ViewEntities;

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
        if (!renderableComp->isDisplayed) return;
        if (entity->has<PositionComponent>()) {
            auto positionComponent = entity->getComponent<PositionComponent>();
            updateSprite(renderableComp, positionComponent);
        }
        components[renderableComp->priority].push_back(renderableComp);
        keys[renderableComp->priority] = true;
    });

    world.each<LayeredRenderableComponent>(
        [&](ECS::Entity *entity, ECS::ComponentHandle<LayeredRenderableComponent> layeredRenderableComp) {
            if (layeredRenderableComp->isDisplayed) return;
            if (entity->has<PositionComponent>()) {
                auto positionComponent = entity->getComponent<PositionComponent>();
                for (auto &renderable : layeredRenderableComp->renderable) {
                    updateSprite(ECS::ComponentHandle(renderable), positionComponent);
                }
            }
            layeredComponents[layeredRenderableComp->priority].push_back(layeredRenderableComp);
            keys[layeredRenderableComp->priority] = true;
        });

    window->clear(sf::Color::Black);

    for (auto key : keys) {
        int iter = key.first;
        if (components.find(iter) != components.end()) {
            for (auto &renderableComp : components[iter]) {
                window->draw(renderableComp->sprite);
            }
        }
        if (layeredComponents.find(iter) != layeredComponents.end()) {
            for (auto &renderableComp : layeredComponents[iter]) {
                for (auto &renderable : renderableComp->renderable) {
                    window->draw(renderable->sprite);
                }
            }
        }
    }

    world.each<TextComponent>([&](ECS::Entity *entity, ECS::ComponentHandle<TextComponent> handle) {
        if (entity->has<TextComponent>() && handle->isDisplay) {
            window->draw(handle->text);
        }
    });

#ifndef NOT_SHOW_HITBOX
    for (auto drawable : WORLD.getEntitiesWithComponents<DrawableComponent>()) {
        window->draw(*drawable->getComponent<DrawableComponent>()->drawable);
    }
#endif

    window->display();
}
