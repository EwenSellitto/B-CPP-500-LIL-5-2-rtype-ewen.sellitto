// GameWorld.hpp
#pragma once
#include "ECS/World.hpp"
#include "Engine/Engine.hpp"
#include "GameWorld/Entities.hpp"
#include "GameWorld/Subscribers.hpp"
#include "GameWorld/Systems.hpp"

namespace GameWorld
{
    inline void createGameWorld(Engine::EngineClass &engine)
    {
        auto world = std::make_shared<ECS::World>();

        // Setup view and create entities
        Entities::createViewEntity(world);
        Entities::createParallax(world);
        Entities::createPlayerEntities(world);
        Entities::createEnemyQueue(world);
        Entities::createWorldMoveProgress(world);

        // Add systems
        Systems::addPhysics(world);
        Systems::addPlayerMovement(world);
        Systems::addEnemySystem(world);
        Systems::addParallaxSystem(world);
        Systems::addBulletSystem(world);
        Systems::addRenderer(world);

        // Subscribe to events
        Subscribers::subscribeToEvents(world);

        // Set up the world in the engine
        engine.addWorldFactory("game", [world]() { return world; });
    }

    std::shared_ptr<ECS::World> createMenuWorld(Engine::EngineClass &engine) {
        auto world = std::make_shared<ECS::World>();

        Entities::createViewEntity(world);
        Entities::createButtonEntities(world);

        Systems::addRenderer(world);
        Systems::addUISystem(world);

        engine.setStartWorld("menu");
        engine.addWorldFactory("menu", [world]() { return world; });

        return world;
    }
}
