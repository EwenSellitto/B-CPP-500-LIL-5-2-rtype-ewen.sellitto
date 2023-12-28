/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** main.cpp
*/

#include "Engine/Engine.hpp"
#include "ECS/World.hpp"
#include "Engine/Components/Sprite.component.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv, [[maybe_unused]] char **env)
{
    Engine::EngineClass &engine = Engine::EngineClass::getEngine();
    engine.createEmptyWorld("default");
    ECS::World &world = engine.world();
    SpriteData data;
    auto entityWithSprite = world.createEntityWithSprite(data, "Nairan-TorpedoShip-Shield");
    engine.run();
    return 0;
}
