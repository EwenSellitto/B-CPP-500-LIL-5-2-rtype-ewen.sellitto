/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** main.cpp
*/

#include <memory>

#include "ECS/World.hpp"
#include "Engine/Components/Position.compnent.hpp"
#include "Engine/Components/Renderable.component.hpp"
#include "Engine/Components/Moving.component.hpp"
#include "Engine/Components/View.component.hpp"
#include "Engine/Engine.hpp"
#include "Engine/Systems/Renderer.system.hpp"
#include "Engine/Systems/Physics.system.hpp"

std::shared_ptr<ECS::World> createWorldGame()
{
    using namespace Engine::Components;

    std::shared_ptr<ECS::World> world = std::make_shared<ECS::World>();
    world->createEntity(new ViewComponent());
    // View entity
    id_t ship_id = world->createEntity(new PositionComponent(0, 0),
                        new RenderableComponent("./assets/MainShip/MainShip-Base-Fullhealth.png", 10, 10, 1));
    ECS::Entity &ship = world->getMutEntity(ship_id);
    ECS::ComponentHandle<RenderableComponent> shipRenderableComp(ship.getComponent<RenderableComponent>());
    ship.addComponent(new MovingComponent(shipRenderableComp->position, 3000, {300, 0}));

    std::cout << "Creating first world" << std::endl;
    world->addSystem<Engine::System::Renderer>("Renderer");
    world->addSystem<Engine::System::Physics>("Physics");
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
