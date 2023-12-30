// GameWorld.hpp
#pragma once
#include "ECS/World.hpp"
#include "Engine/Engine.hpp"
#include "GameWorld/Entities.hpp"
#include "GameWorld/Subscribers.hpp"
#include "GameWorld/Systems.hpp"

namespace GameWorld
{
    inline void setup(Engine::EngineClass &engine)
    {
        auto world = std::make_shared<ECS::World>();

        // Setup view and create entities
        Entities::createViewEntity(world);
        Entities::createParallax(world);
        Entities::createPlayerEntities(world);

        // Add systems
        Systems::addRenderer(world);
        Systems::addPhysics(world);
        Systems::addPlayerMovement(world);
        Systems::addEnemySystem(world);
        Systems::addParallaxSystem(world);

        // Subscribe to events
        Subscribers::subscribeToEvents(world);

        // Set up the world in the engine
        engine.setStartWorld("game");
        engine.addWorldFactory("game", [world]() { return world; });
    }
} // namespace GameWorld
