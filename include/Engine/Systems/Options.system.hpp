// ParallaxSystem.hpp

#pragma once
#include "ECS/System.hpp"
#include "ECS/World.hpp"

namespace Engine::System
{
    class OptionsSystem : public ECS::BaseSystem
    {
        public:
            OptionsSystem(ECS::World &world) : ECS::BaseSystem(world) {}

            void configure(ECS::World &world) override;

            void unconfigure() override;

            void tick() override;

            void openOptions();

            void closeOptions();
    };
} // namespace Engine::System
