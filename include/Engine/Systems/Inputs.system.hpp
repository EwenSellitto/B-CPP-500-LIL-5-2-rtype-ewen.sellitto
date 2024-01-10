// InputsSystem.hpp

#pragma once
#include "ECS/System.hpp"
#include "ECS/World.hpp"

namespace Engine::System
{
    class InputsSystem : public ECS::BaseSystem
    {
        public:
            InputsSystem(ECS::World &world) : ECS::BaseSystem(world) {}

            void configure(ECS::World &world) override;

            void unconfigure() override;

            void tick() override;

            void changeText(std::string &text);

            void removeText();

            void handleSend(std::vector<std::string> args);
    };
} // namespace Engine::System
