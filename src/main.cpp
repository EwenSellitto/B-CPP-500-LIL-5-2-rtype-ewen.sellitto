/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** main.cpp
*/

#include <SFML/Window/Event.hpp>
#include <memory>

#include "ECS/World.hpp"
#include "Engine/Components/Collision.component.hpp"
#include "Engine/Components/ExcludeCollision.component.hpp"
#include "Engine/Components/Moving.component.hpp"
#include "Engine/Components/Parallax.component.hpp"
#include "Engine/Components/Position.component.hpp"
#include "Engine/Components/Renderable.component.hpp"
#include "Engine/Components/Type.component.hpp"
#include "Engine/Components/View.component.hpp"
#include "Engine/Engine.hpp"
#include "Engine/Events/Collision.event.hpp"
#include "Engine/Events/KeyPressed.event.hpp"
#include "Engine/Events/KeyReleased.event.hpp"
#include "Engine/Systems/Enemy.system.hpp"
#include "Engine/Systems/MovePlayer.system.hpp"
#include "Engine/Systems/Parallax.system.hpp"
#include "Engine/Systems/Physics.system.hpp"
#include "Engine/Systems/Renderer.system.hpp"
#include "R-Type/Subscribers/Collision.subscriber.hpp"
#include "R-Type/Subscribers/PlayerMove.subscriber.hpp"

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

void createParallax(std::shared_ptr<ECS::World> world)
{
    createBackground(world, "./assets/Environnement/Starrybackground-Layer01-Void.png", ParallaxLayer::FarBackground, 1,
                     true, -5);
    createBackground(world, "./assets/Environnement/Starrybackground-Layer01-Void.png", ParallaxLayer::FarBackground, 1,
                     false, -5);
    createBackground(world, "./assets/Environnement/Starrybackground-Layer02-Stars.png", ParallaxLayer::MidBackground,
                     2, true, -4);
    createBackground(world, "./assets/Environnement/Starrybackground-Layer02-Stars.png", ParallaxLayer::MidBackground,
                     2, false, -4);
    createBackground(world, "./assets/Environnement/Starrybackground-LayerX-BigStar2.png",
                     ParallaxLayer::NearBackground, 4, true, -3);
    createBackground(world, "./assets/Environnement/Starrybackground-LayerX-BigStar2.png",
                     ParallaxLayer::NearBackground, 4, false, -3);
}

std::shared_ptr<ECS::World> createWorldGame()
{
    using namespace Engine::Components;

    std::shared_ptr<ECS::World> world = std::make_shared<ECS::World>();
    world->createEntity(new ViewComponent());
    // View entity
    createParallax(world);

    id_t ship_id = world->createEntity(
        new PositionComponent(0, 0),
        new RenderableComponent("./assets/MainShip/MainShip-Base-Fullhealth.png", 0, 0, 1, 90),
        new CollisionComponent(-37, 9, 26, 30), new TypeComponent(Engine::Components::TypeComponent::player),
        new ExcludeCollisionComponent(1));

    id_t ship_id_two = world->createEntity(
        new PositionComponent(200, 0),
        new RenderableComponent("./assets/MainShip/MainShip-Base-Fullhealth.png", 200, 0, 1),
        new CollisionComponent(9, 11, 30, 26), new TypeComponent(Engine::Components::TypeComponent::player),
        new ExcludeCollisionComponent(0));

    ECS::Entity                            &ship = world->getMutEntity(ship_id);
    ECS::ComponentHandle<PositionComponent> shipRenderableComp(ship.getComponent<PositionComponent>());

    ship.addComponent(new MovingComponent(
        {static_cast<float>(shipRenderableComp->x), static_cast<float>(shipRenderableComp->y)}, 1000 * 100, {0, 0}));

    std::cout << "Creating first world" << std::endl;
    world->addSystem<Engine::System::Renderer>("Renderer");
    world->addSystem<Engine::System::Physics>("Physics");
    world->addSystem<Engine::System::MovePlayer>("PlayerMover");
    world->addSystem<Engine::System::EnemySystem>("EnemySystem");
    world->addSystem<Engine::System::ParallaxSystem>("ParallaxSystem");

    Engine::System::MovePlayer *movePlayerSystem =
        dynamic_cast<Engine::System::MovePlayer *>(world->getSystems()["PlayerMover"].get());
    if (movePlayerSystem) {
        movePlayerSystem->setCurrentPlayer(&ship);
        movePlayerSystem->setPlayerSpeed(50);
    }
    auto *sub  = new Rtype::Subscriber::PlayerMovePressedSubscriber();
    auto *sub1 = new Rtype::Subscriber::PlayerMoveReleasedSubscriber();
    auto *sub2 = new Rtype::Subscriber::CollisionEventSubscriber();
    world->subscribe<KeyPressedEvent>(sub);
    world->subscribe<KeyReleasedEvent>(sub1);
    world->subscribe<CollisionEvent>(sub2);

    return world;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv, [[maybe_unused]] char **env)
{
    Engine::EngineClass &engine = Engine::EngineClass::getEngine();
    try {
        engine.setStartWorld("game");
        engine.addWorldFactory("game", createWorldGame);
        engine.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    return 0;
}
