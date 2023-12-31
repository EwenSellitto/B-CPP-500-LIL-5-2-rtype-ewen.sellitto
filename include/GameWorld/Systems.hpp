// Systems.hpp
#pragma once
#include "ECS/World.hpp"
#include "Engine/Systems/Enemy.system.hpp"
#include "Engine/Systems/MovePlayer.system.hpp"
#include "Engine/Systems/Parallax.system.hpp"
#include "Engine/Systems/Physics.system.hpp"
#include "Engine/Systems/Renderer.system.hpp"
#include "Engine/Systems/UI.system.hpp"
#include "Engine/Systems/Bullets.system.hpp"
#include "Engine/Systems/WorldMove.system.hpp"

namespace Systems
{
    inline void addRenderer(std::shared_ptr<ECS::World> &world)
    {
        world->addSystem<Engine::System::Renderer>("Renderer");
    }

    inline void addPhysics(std::shared_ptr<ECS::World> &world)
    {
        world->addSystem<Engine::System::Physics>("Physics");
    }

    inline void addPlayerMovement(std::shared_ptr<ECS::World> &world)
    {
        world->addSystem<Engine::System::MovePlayer>("MovePlayer");
    }

    inline void addEnemySystem(std::shared_ptr<ECS::World> &world)
    {
        world->addSystem<Engine::System::EnemySystem>("EnemySystem");
    }

    inline void addParallaxSystem(std::shared_ptr<ECS::World> &world)
    {
        world->addSystem<Engine::System::ParallaxSystem>("ParallaxSystem");
    }

    void addUISystem(std::shared_ptr<ECS::World> &world) {
        world->addSystem<Engine::System::UI>("UISystem");
    }

    void addBulletSystem(std::shared_ptr<ECS::World> &world) {
        world->addSystem<Engine::System::Bullets>("BulletsSystem");
    }

    void addWorldMoveSystem(std::shared_ptr<ECS::World> &world) {
        world->addSystem<Engine::System::WorldMoveSystem>("WorldMoveSystem");
    }
}
