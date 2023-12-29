// ParallaxSystem.hpp

#pragma once
#include "ECS/System.hpp"
#include "ECS/World.hpp"
#include "Engine/Components/Parallax.component.hpp"
#include "Engine/Components/Position.component.hpp"

namespace Engine::System {
    class ParallaxSystem : public ECS::BaseSystem {
        public:
            ParallaxSystem(ECS::World &world) : ECS::BaseSystem(world) {}

            void configure(ECS::World &world) override;

            void unconfigure() override;

            void tick() override;
    };
}
