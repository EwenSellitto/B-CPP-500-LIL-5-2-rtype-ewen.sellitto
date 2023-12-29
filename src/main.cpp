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
#include "Engine/Components/Moving.component.hpp"
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
#include "Engine/Systems/Physics.system.hpp"
#include "Engine/Systems/Renderer.system.hpp"

class PlayerMovePressedSubscriber : public virtual ECS::EventSubscriber<KeyPressedEvent>
{
    public:
        PlayerMovePressedSubscriber()           = default;
        ~PlayerMovePressedSubscriber() override = default;
        void receiveEvent(const std::string &name, const KeyPressedEvent &data) override
        {
            if (!(data.keyEvent.code == sf::Keyboard::Z || data.keyEvent.code == sf::Keyboard::Q ||
                  data.keyEvent.code == sf::Keyboard::S || data.keyEvent.code == sf::Keyboard::D))
                return;
            Engine::System::MovePlayer *movePlayerSystem = dynamic_cast<Engine::System::MovePlayer *>(
                Engine::EngineClass::getEngine().world().getSystems()["PlayerMover"].get());
            if (!movePlayerSystem) return;
            movePlayerSystem->addMovePlayer(data.keyEvent);
        }
};

class PlayerMoveReleasedSubscriber : public virtual ECS::EventSubscriber<KeyReleasedEvent>
{
    public:
        PlayerMoveReleasedSubscriber()           = default;
        ~PlayerMoveReleasedSubscriber() override = default;
        void receiveEvent(const std::string &name, const KeyReleasedEvent &data) override
        {
            if (!(data.keyEvent.code == sf::Keyboard::Z || data.keyEvent.code == sf::Keyboard::Q ||
                  data.keyEvent.code == sf::Keyboard::S || data.keyEvent.code == sf::Keyboard::D))
                return;
            Engine::System::MovePlayer *movePlayerSystem = dynamic_cast<Engine::System::MovePlayer *>(
                Engine::EngineClass::getEngine().world().getSystems()["PlayerMover"].get());
            if (!movePlayerSystem) return;
            movePlayerSystem->stopMovePlayer(data.keyEvent);
        }
};

class CollisionEventSubscriber : public virtual ECS::EventSubscriber<CollisionEvent>
{
    public:
        CollisionEventSubscriber()           = default;
        ~CollisionEventSubscriber() override = default;
        void receiveEvent(const std::string &name, const CollisionEvent &data) override
        {
            using namespace Engine::Components;

            data.movingEntity->removeComponent<MovingComponent>();
        }
};

std::shared_ptr<ECS::World> createWorldGame()
{
    using namespace Engine::Components;

    std::shared_ptr<ECS::World> world = std::make_shared<ECS::World>();
    world->createEntity(new ViewComponent());
    // View entity
    id_t ship_id = world->createEntity(
        new PositionComponent(0, 0), new RenderableComponent("./assets/MainShip/MainShip-Base-Fullhealth.png", 0, 0, 1),
        new CollisionComponent(), new TypeComponent(Engine::Components::TypeComponent::player));
    id_t ship_id_two =
        world->createEntity(new PositionComponent(200, 0),
                            new RenderableComponent("./assets/MainShip/MainShip-Base-Fullhealth.png", 200, 0, 1),
                            new CollisionComponent(), new TypeComponent(Engine::Components::TypeComponent::player));
    ECS::Entity                            &ship = world->getMutEntity(ship_id);
    ECS::ComponentHandle<PositionComponent> shipRenderableComp(ship.getComponent<PositionComponent>());

    ship.addComponent(new MovingComponent(
        {static_cast<float>(shipRenderableComp->x), static_cast<float>(shipRenderableComp->y)}, 1000 * 100, {0, 0}));

    std::cout << "Creating first world" << std::endl;
    world->addSystem<Engine::System::Renderer>("Renderer");
    world->addSystem<Engine::System::Physics>("Physics");
    world->addSystem<Engine::System::MovePlayer>("PlayerMover");
    world->addSystem<Engine::System::EnemySystem>("EnemySystem");

    Engine::System::MovePlayer *movePlayerSystem =
        dynamic_cast<Engine::System::MovePlayer *>(world->getSystems()["PlayerMover"].get());
    if (movePlayerSystem) {
        movePlayerSystem->setCurrentPlayer(&ship);
        movePlayerSystem->setPlayerSpeed(50);
    }
    auto *sub  = new PlayerMovePressedSubscriber();
    auto *sub1 = new PlayerMoveReleasedSubscriber();
    auto *sub2 = new CollisionEventSubscriber();
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
