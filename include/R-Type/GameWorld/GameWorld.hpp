/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** GameWorld.hpp
*/

#pragma once

#include "ECS/World.hpp"
#include "Engine/Engine.hpp"
#include "Entities.hpp"
#include "Subscribers.hpp"
#include "Systems.hpp"

namespace GameWorld
{
    inline ECS::World *createGameWorld()
    {
        auto world = new ECS::World();

        // Setup view and create entities
        Entities::createViewEntity(world);
        Entities::createParallax(world);
        Entities::createOptionsEntities(world);
        Entities::createScoreEntities(world);
        // Entities::createChangeSceneButton(world, "./assets/menu/button_normal/normal_off.png", "menu", {150, 150},
        //                                   {2, 2}, 4);

        // Add systems
        Systems::addPhysics(world);
        Systems::addPlayerMovement(world);
        Systems::addEnemySystem(world);
        Systems::addUISystem(world);
        Systems::addScoreSystem(world);
        Systems::addParallaxSystem(world);
        Systems::addBulletSystem(world);
        Systems::addWorldMoveSystem(world);
        Systems::addAnimationSystem(world);
        Systems::addDeathAnimationSystem(world);
        Systems::addHealthSystem(world);
        Systems::addBoosterSystem(world);

        // Subscribe to events
        Subscribers::subscribeToEvents(world);

        if (NETWORK.getIsServer()) {
            for (auto &player : NETWORK.getWaitingRoom().getPlayers()) {
                Entities::createPlayerEntities(world, player->nbPlayer);
            }
            Entities::createEnemyQueue(world);
            Entities::createWorldMoveProgress(world);
        }

        return world;
    }

    // inline std::shared_ptr<ECS::World> createMenuWorld(Engine::EngineClass &engine)
    inline ECS::World *createMenuWorld()
    {
        auto world = new ECS::World();

        Entities::createViewEntity(world);
        Entities::createButtonEntities(world);
        Entities::createOptionsEntities(world);
        Entities::createParallax(world);
        Systems::addUISystem(world);

        Systems::addParallaxSystem(world);

        // Disclaimer: this hasn't been done by me, but trying to make it pretty it crashes, as I think when we switch
        // world while being in one doing a function, it crashes, so we should keep a shared_ptr of the world
        // while we're in it, and remove it safely when we've truly exited the world
        // engine.addWorldFactory("menu", [world]() { return world; });

        return world;
    }

    inline ECS::World *joinRoomWorld()
    {
        auto world = new ECS::World();

        Entities::createViewEntity(world);
        Entities::createInputsEntitiesForJoin(world);
        Entities::createParallax(world);

        Systems::addUISystem(world);
        Systems::addInputsSystem(world);
        Systems::addParallaxSystem(world);

        Subscribers::subscribeToEventsInputs(world);
        return world;
    }

    inline ECS::World *createRoomWorld()
    {
        auto world = new ECS::World();

        Entities::createViewEntity(world);
        Entities::createInputsEntitiesForCreate(world);
        Entities::createParallax(world);

        Systems::addUISystem(world);
        Systems::addInputsSystem(world);
        Systems::addParallaxSystem(world);

        Subscribers::subscribeToEventsInputs(world);
        return world;
    }
    inline ECS::World *createWaitingHost()
    {
        auto world = new ECS::World();

        Entities::createViewEntity(world);
        Entities::createParallax(world);
        Entities::createWaitingHostEntities(world);

        Systems::addUISystem(world);
        Systems::addParallaxSystem(world);

        return world;
    }

    inline ECS::World *createWaitingClient()
    {
        auto world = new ECS::World();

        Entities::createViewEntity(world);
        Entities::createParallax(world);
        Entities::createWaitingClientEntities(world);

        Systems::addUISystem(world);
        Systems::addParallaxSystem(world);

        return world;
    }

    inline ECS::World *createGameOver()
    {
        auto world = new ECS::World();

        Entities::createViewEntity(world);
        Entities::createParallax(world);
        Entities::createGameOverEntities(world);

        Systems::addUISystem(world);
        Systems::addParallaxSystem(world);

        return world;
    }
} // namespace GameWorld
