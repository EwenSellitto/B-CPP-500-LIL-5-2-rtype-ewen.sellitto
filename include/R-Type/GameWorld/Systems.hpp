// Systems.hpp
#pragma once
#include "ECS/World.hpp"
#include "Engine/Systems/Animation.system.hpp"
#include "Engine/Systems/Parallax.system.hpp"
#include "Engine/Systems/Physics.system.hpp"
#include "Engine/Systems/Renderer.system.hpp"
#include "Engine/Systems/Score.system.hpp"
#include "Engine/Systems/UI.system.hpp"
#include "Engine/Systems/WorldMove.system.hpp"
#include "R-Type/Systems/Booster.system.hpp"
#include "R-Type/Systems/Bullets.system.hpp"
#include "R-Type/Systems/DeathAnimation.system.hpp"
#include "R-Type/Systems/Enemy.system.hpp"
#include "R-Type/Systems/Health.system.hpp"
#include "R-Type/Systems/MovePlayer.system.hpp"

namespace Systems
{
    inline void addRenderer(ECS::World *world)
    {
        world->addSystem<Engine::System::Renderer>("Renderer");
    }

    inline void addPhysics(ECS::World *world)
    {
        world->addSystem<Engine::System::Physics>("Physics");
    }

    inline void addPlayerMovement(ECS::World *world)
    {
        world->addSystem<Engine::System::MovePlayer>("MovePlayer");
    }

    inline void addEnemySystem(ECS::World *world)
    {
        world->addSystem<Engine::System::EnemySystem>("EnemySystem");
    }

    inline void addParallaxSystem(ECS::World *world)
    {
        world->addSystem<Engine::System::ParallaxSystem>("ParallaxSystem");
    }

    inline void addUISystem(ECS::World *world)
    {
        world->addSystem<Engine::System::UI>("UISystem");
    }

    inline void addScoreSystem(ECS::World *world)
    {
        world->addSystem<Engine::System::ScoreSystem>("ScoreSystem");
    }

    inline void addInputsSystem(ECS::World *world)
    {
        world->addSystem<Engine::System::InputsSystem>("InputsSystem");
    }

    inline void addBulletSystem(ECS::World *world)
    {
        world->addSystem<Engine::System::Bullets>("BulletsSystem");
    }

    inline void addWorldMoveSystem(ECS::World *world)
    {
        world->addSystem<Engine::System::WorldMoveSystem>("WorldMoveSystem");
    }

    inline void addAnimationSystem(ECS::World *world)
    {
        world->addSystem<Engine::System::AnimationSystem>("AnimationSystem");
    }

    inline void addDeathAnimationSystem(ECS::World *world)
    {
        world->addSystem<Engine::System::DeathAnimationSystem>("DeathAnimationSystem");
    }

    inline void addHealthSystem(ECS::World *world)
    {
        world->addSystem<Rtype::Systems::HealthSystem>("HealthSystem");
    }

    inline void addBoosterSystem(ECS::World *world)
    {
        world->addSystem<Rtype::System::BoosterSystem>("BoosterSystem");
    }
} // namespace Systems
