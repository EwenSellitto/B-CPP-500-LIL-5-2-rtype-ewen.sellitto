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

    std::shared_ptr<ECS::World> createMenuWorld(Engine::EngineClass &engine) {
        auto world = std::make_shared<ECS::World>();

        // Ajouter des boutons au monde
        Entities::createViewEntity(world);
        Entities::createButtonEntities(world);

        // ... ajouter plus de boutons si nécessaire ...

        // Ajouter des systèmes au monde
        Systems::addRenderer(world);
        Systems::addUISystem(world);

        engine.setStartWorld("game");
        engine.addWorldFactory("game", [world]() { return world; });

        return world;
    }
}
