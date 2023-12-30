// Entities.hpp
#pragma once
#include "ECS/World.hpp"
#include "Engine/Components/Renderable.component.hpp"
#include "Engine/Components/Position.component.hpp"
#include "Engine/Components/Collision.component.hpp"
#include "Engine/Components/Type.component.hpp"
#include "Engine/Components/View.component.hpp"
#include "Engine/Components/Parallax.component.hpp"

namespace Entities {
    void createViewEntity(std::shared_ptr<ECS::World> &world) {
        world->createEntity(new Engine::Components::ViewComponent());
    }

    void createPlayerEntities(std::shared_ptr<ECS::World> &world) {
        id_t ship_id = world->createEntity(
            new Engine::Components::PositionComponent(0, 0),
            new Engine::Components::RenderableComponent("./assets/MainShip/MainShip-Base-Fullhealth.png", 0, 0, 1),
            new Engine::Components::CollisionComponent(),
            new Engine::Components::TypeComponent(Engine::Components::TypeComponent::player)
        );

    }

    void createBackground(std::shared_ptr<ECS::World> world, const std::string &texturePath, ParallaxLayer layer,
    float speed, bool first, int priority)
    {

        using namespace Engine::Components;
        sf::Vector2f windowSize = {0, 0};

        world->each<ViewComponent>(
            [&windowSize]([[maybe_unused]] ECS::Entity *entity, ECS::ComponentHandle<ViewComponent> viewComp) {
                windowSize = viewComp->view.getSize();
            });

        auto  renderable = new RenderableComponent(texturePath, {0, 0}, priority);
        float scaleRatio = windowSize.y / renderable->texture.getSize().y;

        renderable->scale           = {scaleRatio, scaleRatio};
        sf::Vector2<float> trueSize = {static_cast<float>(renderable->size.x * scaleRatio),
                                    static_cast<float>(renderable->size.y * scaleRatio)};
        if (first) {
            renderable->position = {0, 0};
            world->createEntity(new PositionComponent(0, 0), renderable, new ParallaxComponent(layer, speed));
        } else {
            renderable->position = {trueSize.x, 0};
            world->createEntity(new PositionComponent(trueSize.x, 0), renderable, new ParallaxComponent(layer, speed));
        }
    }

    void createParallax(std::shared_ptr<ECS::World> &world) {
        createBackground(world, "./assets/Environnement/Starrybackground-Layer01-Void.png", ParallaxLayer::FarBackground, 1, true, -5);
        createBackground(world, "./assets/Environnement/Starrybackground-Layer01-Void.png", ParallaxLayer::FarBackground, 1, false, -5);
        createBackground(world, "./assets/Environnement/Starrybackground-Layer02-Stars.png", ParallaxLayer::MidBackground, 2, true, -4);
        createBackground(world, "./assets/Environnement/Starrybackground-Layer02-Stars.png", ParallaxLayer::MidBackground, 2, false, -4);
        createBackground(world, "./assets/Environnement/Starrybackground-LayerX-BigStar2.png", ParallaxLayer::NearBackground, 4, true, -3);
        createBackground(world, "./assets/Environnement/Starrybackground-LayerX-BigStar2.png", ParallaxLayer::NearBackground, 4, false, -3);
    }
}
