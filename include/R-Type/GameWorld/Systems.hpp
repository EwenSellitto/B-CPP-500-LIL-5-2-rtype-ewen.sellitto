// Systems.hpp
#pragma once
#include "ECS/World.hpp"
#include "Engine/Systems/Animation.system.hpp"
#include "Engine/Systems/Parallax.system.hpp"
#include "Engine/Systems/Physics.system.hpp"
#include "Engine/Systems/Renderer.system.hpp"
#include "Engine/Systems/UI.system.hpp"
#include "Engine/Systems/WorldMove.system.hpp"
#include "R-Type/Systems/Bullets.system.hpp"
#include "R-Type/Systems/Enemy.system.hpp"
#include "R-Type/Systems/MovePlayer.system.hpp"

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

    inline void addUISystem(std::shared_ptr<ECS::World> &world)
    {
        world->addSystem<Engine::System::UI>("UISystem");
    }

    inline void addBulletSystem(std::shared_ptr<ECS::World> &world)
    {
        world->addSystem<Engine::System::Bullets>("BulletsSystem");
    }

    inline void addWorldMoveSystem(std::shared_ptr<ECS::World> &world)
    {
        world->addSystem<Engine::System::WorldMoveSystem>("WorldMoveSystem");
    }

    inline void addAnimationSystem(std::shared_ptr<ECS::World> &world)
    {
        world->addSystem<Engine::System::AnimationSystem>("AnimationSystem");
    }
} // namespace Systems
