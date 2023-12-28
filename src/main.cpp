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
#include "Engine/Engine.hpp"
#include "Engine/Systems/Renderer.system.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window/Event.hpp"

std::shared_ptr<ECS::World> createWorld()
{
    using namespace Engine::Components;

    std::shared_ptr<ECS::World> world = std::make_shared<ECS::World>();
    world->createEntity(new PositionComponent(0, 0),
                        new RenderableComponent("./assets/MainShip/MainShip-Base-Fullhealth.png", 10, 10, 1));
    // AnimationComponent(0, 0, 32, 32, 100));
    std::cout << "Creating first world" << std::endl;
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
