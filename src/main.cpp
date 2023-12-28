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

std::shared_ptr<ECS::World> createWorld()
{
    using namespace Engine::Components;

    std::shared_ptr<ECS::World> world = std::make_shared<ECS::World>();
    world->createEntity<PositionComponent, RenderableComponent, AnimationComponent>(
        PositionComponent(0, 0), RenderableComponent("../assets/MainShip/MainShip-Base-Fullhealth.png", 0, 0, 1),
        AnimationComponent());
    return world;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv, [[maybe_unused]] char **env)
{
    Engine::EngineClass &engine = Engine::EngineClass::getEngine();
    engine.addWorldFactory("default", createWorld);
    return 0;
}
