/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** main.cpp
*/

#include <memory>

#include "ECS/World.hpp"
#include "Engine/Components/Animation.component.hpp"
#include "Engine/Components/Position.compnent.hpp"
#include "Engine/Components/Renderable.component.hpp"
#include "Engine/Engine.hpp"
#include "Engine/Systems/Animation.system.hpp"
#include "Engine/Systems/Renderer.system.hpp"

std::shared_ptr<ECS::World> createWorld()
{
    using namespace Engine::Components;

    std::shared_ptr<ECS::World> world = std::make_shared<ECS::World>();

    world->createEntity(new PositionComponent(0, 0),
                        new RenderableComponent("./assets/MainShip/MainShip-Base-Fullhealth.png", 1));

    world->createEntity(new PositionComponent(200, 200),
                        new RenderableComponent("./assets/Nairan/Nairan-Battlecruiser-Destruction.png", 1, 90),
                        new AnimationComponent(0, 0, 128, 128, 100, 18));

    world->createEntity(new PositionComponent(400, 200),
                        new RenderableComponent("./assets/Nairan/Nairan-Battlecruiser-Weapons.png", 1),
                        new AnimationComponent(0, 0, 128, 128, 100, 9));

    std::cout << "Creating first world" << std::endl;
    world->addSystem<Engine::System::AnimationSystem>("AnimationSystem");
    world->addSystem<Engine::System::Renderer>("Renderer");
    return world;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv, [[maybe_unused]] char **env)
{
    Engine::EngineClass &engine = Engine::EngineClass::getEngine();
    try {
        engine.addWorldFactory("default", createWorld);
        engine.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    return 0;
}
