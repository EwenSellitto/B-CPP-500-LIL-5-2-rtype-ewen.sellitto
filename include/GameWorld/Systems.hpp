// Systems.hpp
#pragma once
#include "ECS/World.hpp"
#include "Engine/Systems/Renderer.system.hpp"
#include "Engine/Systems/Physics.system.hpp"
#include "Engine/Systems/MovePlayer.system.hpp"
#include "Engine/Systems/Enemy.system.hpp"
#include "Engine/Systems/Parallax.system.hpp"

namespace Systems {
    void addRenderer(std::shared_ptr<ECS::World> &world) {
        world->addSystem<Engine::System::Renderer>("Renderer");
    }

    void addPhysics(std::shared_ptr<ECS::World> &world) {
        world->addSystem<Engine::System::Physics>("Physics");
    }

    void addPlayerMovement(std::shared_ptr<ECS::World> &world) {
        world->addSystem<Engine::System::MovePlayer>("MovePlayer");
    }

    void addEnemySystem(std::shared_ptr<ECS::World> &world) {
        world->addSystem<Engine::System::EnemySystem>("EnemySystem");
    }

    void addParallaxSystem(std::shared_ptr<ECS::World> &world) {
        world->addSystem<Engine::System::ParallaxSystem>("ParallaxSystem");
    }
}
