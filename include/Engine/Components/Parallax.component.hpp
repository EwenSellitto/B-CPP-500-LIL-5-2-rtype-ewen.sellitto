// ParallaxComponent.hpp

#pragma once
#include "ECS/Components.hpp"

enum class ParallaxLayer {
    FarBackground,
    MidBackground,
    NearBackground
};

namespace Engine::Components
{
    struct ParallaxComponent : public ECS::BaseComponent {
            ParallaxLayer layer;
            float         speed;
            sf::Vector2f  offset;
            bool          first;

            ParallaxComponent(ParallaxLayer layer, float speed) : layer(layer), speed(speed), offset(0, 0) {}

            ~ParallaxComponent() override = default;

            std::vector<char> serialize(void) override {
                return std::vector<char>();
            }
    };
} // namespace Engine::Components